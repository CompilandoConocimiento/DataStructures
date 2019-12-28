import React, { FunctionComponent } from "react"
import { saveFile } from "./Helpers"

const getKeys = async () => {
  const url = "/get_keys"
  const response = await fetch(url)
  const keys = await response.json()

  const { n, publicKey, privateKey } = keys
  const publicData = `{"n": "${n}", "public": "${publicKey}"}`
  const privateData = `{"n": "${n}", "private": "${privateKey}"}`

  saveFile("public.keys", publicData)
  saveFile("private.keys", privateData)
}

const GenerateKeys: FunctionComponent = () => {
  return (
    <section id="Key" className="collapse">
      When you click on the button "Generate Keys" you will obtain two 'txt' archives.
      <br />
      One Public Key and One Private Key.
      <br />
      <br />
      <button onClick={getKeys} type="button" className="btn btn-success">
        {" "}
        Generate Keys
      </button>
    </section>
  )
}

export default GenerateKeys
