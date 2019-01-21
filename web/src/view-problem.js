import React from 'react'
import Submit from './submit'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import Layout from './layout'
import { solveProblem } from './redux/actions'
import { history } from './history'

class ViewProblem extends React.Component {

  render () {

    const name = this.props.match.params.id

    let problem = this.props.problems.find((p) => p.name === name)

    return (
      <Layout>
        {problem ? <div>

          <h1>{problem.name}</h1>
          <p>Max Score: {problem.maxScore}</p>
          {problem.timeLimit ? <p>Time limit per test: {problem.timeLimit}</p> : null}
          {problem.memoryLimit ? <p>Memory limit: {problem.memoryLimit}</p> : null}
          {problem.description ? <div className={'problem-description'}>{problem.description}</div> : null}
          {
            problem.hasPdf ? <object width="100%" height="500px" type="application/pdf"
                                     data={`/api/pdf/${problem.name}?#zoom=100&scrollbar=0&toolbar=0&navpanes=1`}>
              <p>PDF cannot be displayed.</p>
            </object> : null
          }

          <h2>Solve this problem</h2>
          <Submit onSubmit={(code) => {
            this.props.solveProblem(name, code).then(() => {
              history.push('/submissions')
            })
          }} problem={problem}/>
        </div> : 'Problem not found'}
      </Layout>
    )
  }
}

const mapStateToProps = (state, props) => ({
  problems: state.problem,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({
  solveProblem
}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(ViewProblem)