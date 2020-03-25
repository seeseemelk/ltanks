pipeline {
  agent any
  stages {
    stage('Build Linux') {
      parallel {
        stage('Build Linux') {
          steps {
            sh 'TARGET=linux make all'
            archiveArtifacts(artifacts: 'ltanks.linux', onlyIfSuccessful: true)
          }
        }

        stage('Build DOS') {
          steps {
            sh 'TARGET=dos make all'
            archiveArtifacts(onlyIfSuccessful: true, artifacts: 'ltanks.exe')
          }
        }

      }
    }

  }
}