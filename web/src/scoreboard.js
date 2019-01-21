import React, { Component } from 'react'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import Layout from './layout'
import { loadScoreboard } from './redux/actions'
import { history } from './history'

class Scoreboard extends Component {

  componentWillMount () {
    if (!this.props.user) {
      history.push('/login')
    } else {
      this.props.loadScoreboard()
    }

  }

  getScore (problem, problems) {
    let score = ''

    for (let p in problems) {
      if (problems[p].name === problem) {
        score = problems[p].score
        break
      }

    }
    return score
  }

  render () {

    const {data, problems} = this.props

    return (
      <Layout>
        <table className="table">
          <thead>
          <tr>
            <th scope="col">User ID</th>
            <th scope="col">Name</th>
            {problems.map((p, index) => {
              return <th key={index}>{p.name}</th>
            })}
            <th>Total Score</th>
          </tr>
          </thead>
          <tbody>
          {data.map((item, k) => {

            return (
              <tr key={k}>
                <td>{item.userId}</td>
                <td>{item.name}</td>
                {
                  problems.map((p, key) => {
                    return <td key={key}>{this.getScore(p.name, item.problems)}</td>
                  })
                }
                <td>{item.total}</td>
              </tr>
            )

          })}
          </tbody>
        </table>
      </Layout>
    )
  }
}

const mapStateToProps = (state, props) => ({
  data: state.scoreboard,
  problems: state.problem,
  user: state.app.user,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({
  loadScoreboard
}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(Scoreboard)