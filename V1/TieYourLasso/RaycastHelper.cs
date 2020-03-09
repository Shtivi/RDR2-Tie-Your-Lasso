using RDR2;
using RDR2.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso
{
    public class RaycastHelper
    {
        /// <summary>
        /// Find a position on the map suits for attaching a rope to hang a ped from the player position and upwards.
        /// </summary>
        /// <returns>A position if found, if not found returns Vector3.Zero</returns>
        public Vector3 FindHangingSpot()
        {
            return FindHangingSpot(Game.Player.Character.Position, Game.Player.Character.UpVector);
        }

        /// <summary>
        /// Find a position on the map suits for attaching a rope to hang a ped.
        /// Given a specific position to begin with and towards a specific direction.
        /// </summary>
        /// <param name="startPosition">The position to start look at</param>
        /// <param name="direction">The direction to look at</param>
        /// <returns>A position if found, if not found returns Vector3.Zero</returns>
        public Vector3 FindHangingSpot(Vector3 startPosition, Vector3 direction)
        {
            var raycast = World.Raycast(startPosition, direction, 5f, IntersectOptions.Map);

            if (!raycast.DitHit)
            {
                Logger.Log("didnt hit");
                return Vector3.Zero;
            }

            var distance = raycast.HitPosition.DistanceTo(startPosition);
            if (distance < 1.8f || distance > 5)
            {
                Logger.Log("hit with wrong distance" + distance);
                return Vector3.Zero;
            }

            Logger.Log("hit!" + distance);
            return raycast.HitPosition;
        }
    }
}
