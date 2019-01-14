import React from 'react'
import Submit from './submit'

export default class ViewProblem extends React.Component {

  render () {
    const {problem} = this.props
    return (
      <div>
        <h1>{problem.name}</h1>
        <p>Max Score: {problem.maxScore}</p>
        {problem.timeLimit ? <p>Time limit per test: {problem.timeLimit}</p> : null}
        {problem.memoryLimit ? <p>Memory limit: {problem.memoryLimit}</p> : null}
        {problem.description ? <div className={'problem-description'}>{problem.description}</div> : null}

        <h2>Solve this problem</h2>
        <Submit onSubmit={(code) => {
          this.props.onSubmit({
            code: code,
            problem: problem.name,
          })
        }} problem={problem}/>
      </div>
    )
  }
}