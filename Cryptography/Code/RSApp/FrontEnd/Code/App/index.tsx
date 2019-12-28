import React, { FunctionComponent } from "react"
import ReactDOM from "react-dom"

import GenerateKeys from "./GenerateKeys"
import Header from "./Header"
import Buttons from "./Buttons"
import RSA from "./RSA"
import Footer from "./Footer"

const App: FunctionComponent = () => {
  return (
    <>
      <Header />

      <main className="container" style={{ minHeight: "90vh" }}>
        <section style={{ padding: "3rem", paddingLeft: "0rem" }}>
          <h2>RSA Options</h2>
          <p>Click on the button to display the respective content.</p>
        </section>

        <Buttons />

        <GenerateKeys />

        <RSA mode={"Encrypt"} />
        <RSA mode={"Decrypt"} />
        <RSA mode={"Hash"} />
        <RSA mode={"Compare"} />

        <img
          src="Distribution/RSA.gif"
          style={{
            margin: "6rem auto 6rem auto",
            display: "block",
            maxWidth: "25rem",
            overflow: "scroll",
          }}
        />
      </main>

      <Footer />
    </>
  )
}

const DOMNode = document.getElementById("ReactApp")
ReactDOM.render(<App />, DOMNode)
