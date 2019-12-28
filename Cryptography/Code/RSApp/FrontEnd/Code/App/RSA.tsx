import React, { FunctionComponent as FC, useState } from "react"
import { saveFile } from "./Helpers"
import SHA256 from "crypto-js/sha256"

// eslint-disable-next-line
type fn = any

const FormInput: FC<{
  onChange: fn
  onClick?: fn
  name: string
  mode?: "Encrypt" | "Decrypt" | "Hash" | "Compare"
  loading?: boolean
}> = props => {
  return (
    <div className="input-group mb-3 input-group-sm" style={{ width: "400px", height: "35px" }}>
      <div className="input-group-prepend" style={{ height: "35px" }}>
        <span className="input-group-text">{props.name}</span>
      </div>

      <input
        type="file"
        style={{ height: "35px" }}
        className="form-control"
        onChange={props.onChange}
      />

      {props.onClick && (
        <div className="input-group-append">
          <button
            className="btn btn-success"
            onClick={props.onClick}
            disabled={props.loading === true}
          >
            {props.loading && (
              <span
                className="spinner-grow spinner-grow-sm"
                role="status"
                aria-hidden="true"
              ></span>
            )}
            {props.mode}
          </button>
        </div>
      )}
    </div>
  )
}

const headers = { Accept: "application/json", "Content-Type": "application/json" }

const RSA: FC<{ mode: "Encrypt" | "Decrypt" | "Hash" | "Compare" }> = ({ mode }) => {
  const [keys, changeKeys] = useState<null | Record<string, string>>(null)
  const [name, changeName] = useState<null | string>(null)
  const [text, changeText] = useState<null | string>(null)
  const [compareText, changeCompareText] = useState<null | string>(null)
  const [isLoading, changeLoading] = useState(false)

  const getText = async (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files && event.target.files[0]
    if (!file) return

    // @ts-ignore
    const textValue = await file.text()
    changeText(textValue)
    changeName(file.name.split(".", 1)[0])
  }

  const getTextCompare = async (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files && event.target.files[0]
    if (!file) return

    // @ts-ignore
    const textValue = await file.text()
    changeCompareText(textValue)
  }

  const getKeys = async (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files && event.target.files[0]
    if (!file) return

    // @ts-ignore
    const text = await file.text()
    try {
      changeKeys(JSON.parse(text))
    } catch (error) {
      alert("This is not a valid key file")
    }
  }

  const callToCipher = async () => {
    changeLoading(true)
    const url = "/RSA"
    const body = JSON.stringify({ ...keys, text, mode })

    const response = await fetch(url, { headers, method: "POST", body })
    const keysResponse = await response.json()

    console.log(keysResponse)

    if (keysResponse.error) {
      let messageError = ""
      switch (mode) {
        case "Encrypt":
          messageError = "Error with the message to encrypt"
          break
        case "Decrypt":
          messageError = "Error with the cipher message, corrupted"
          break
        case "Hash":
          messageError = "Error with the message to sign"
          break
        case "Compare":
          messageError = "Error sign was not verified"
          break
      }
      alert("Error: " + messageError)
      changeLoading(false)
      return
    }

    const message = keysResponse["message"]

    if (message != "") changeLoading(false)

    switch (mode) {
      case "Encrypt":
        saveFile(`${name}.cipher`, JSON.stringify(message))
        break
      case "Decrypt":
        saveFile(`${name}.txt`, message)
        break
      case "Hash":
        saveFile(`${name}.sign`, JSON.stringify(message))
        break
      case "Compare":
        if (SHA256(compareText).toString() == message) alert("Correct signature")
        else alert("No valid signature")
    }
  }

  return (
    <section id={mode} className="collapse">
      <div style={{ marginBottom: "3rem" }}>
        {mode !== "Hash" && (
          <span>For {mode.toLowerCase()} you need to insert a key and the text.</span>
        )}
        {mode === "Hash" && (
          <span>
            Hash Function it's used to confirm the authenticity of the message. Put the plain text
            and compare with the archive Sign.txt. If it's the same text, it's authentic.
          </span>
        )}
        {mode === "Compare" && (
          <span>Compare the plaintext with the decrypt hash to authetificate the sender</span>
        )}
      </div>

      <FormInput onChange={getText} name={mode === "Compare" ? "Signature" : "Text"} />
      <FormInput
        onChange={getKeys}
        name="Keys"
        mode={mode}
        loading={isLoading}
        {...{ onClick: mode !== "Compare" ? callToCipher : undefined }}
      />

      {mode === "Compare" && (
        <FormInput onChange={getTextCompare} onClick={callToCipher} name="Text" mode={mode} />
      )}
    </section>
  )
}

export default RSA
