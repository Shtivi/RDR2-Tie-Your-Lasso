using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso.Scenarios
{
    public interface IScenario
    {
        void Start();
        void Update();

        bool IsFinished { get; }
    }
}
