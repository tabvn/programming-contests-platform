import React from 'react'
import styled from 'styled-components'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import { Link } from 'react-router-dom'
import Layout from './layout'
import { loadProblems } from './redux/actions'
import { history } from './history'

const Container = styled.div`
    margin: 0 auto;
    border: 1px solid #f8f9fa;
`

class Problems extends React.Component {

  componentWillMount () {
    if(!this.props.user){
      history.push('/login')
    }else{
      this.props.loadProblems()
    }

  }

  render () {

    const {data} = this.props

    return (
      <Layout>

        <Container>
          <table>
            <thead>
            <tr>
              <th>Name</th>

            </tr>
            </thead>
            <tbody>
            {
              data.map((p, k) => {
                return (
                  <tr key={k}>
                    <td><Link to={`/problems/${p.name}`}>{p.name}</Link></td>
                  </tr>
                )
              })

            }
            </tbody>
          </table>

        </Container>

      </Layout>
    )
  }
}

const mapStateToProps = (state, props) => ({
  data: state.problem,
  user: state.app.user,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({
  loadProblems
}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(Problems)