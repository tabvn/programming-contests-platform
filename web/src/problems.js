import React from 'react'
import styled from 'styled-components'


const Container = styled.div`
    margin: 0 auto;
    border: 1px solid #f8f9fa;
`

const Link = styled.div`
  cursor: pointer;
  
`
export default class Problems extends React.Component {

  render () {
    const {problems} = this.props

    return (
      <Container>
        <table>
          <thead>
          <tr>
            <th>Name</th>

          </tr>
          </thead>
          <tbody>
          {
            problems.map((p, k) => {
              return (
                <tr key={k}>
                  <td><Link onClick={() => {
                    if (this.props.onSelect) {
                      this.props.onSelect(p)
                    }
                  }}>{p.name}</Link></td>
                </tr>
              )
            })

          }
          </tbody>
        </table>

      </Container>
    )
  }
}