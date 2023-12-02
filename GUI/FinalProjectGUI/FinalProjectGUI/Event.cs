using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinalProjectGUI
{
    internal class Event
    {
        private DateTime? scheduledTime;
        private string? location;
        private List<string> presenters = new List<string>();
        private int? eventCost;
        private int? expectedAttendance;
        Event()
        {

        }
    }
}
