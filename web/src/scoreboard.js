import React, {Component} from 'react'

export default class Scoreboard extends Component{

  getScore(problem, problems) {


    let score = '';

    for(let p in problems){
      if(problems[p].name === problem){
        score = problems[p].score;
        break;
      }

    }
    return score;
  }
  render () {
    const {data, problems} = this.props;

    return (
      <table className="table">
        <thead>
        <tr>
          <th scope="col">#</th>
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
              <td>{item.id}</td>
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
    )
  }
}