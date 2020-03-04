using System;
using System.Windows.Forms;
using RDR2;
using RDR2.UI;
using RDR2.Native;
using RDR2.Math;
using System.IO;
using RDR2.NaturalMotion;

namespace TieYourLasso
{
    public class Client : Script
    {
        private Rope rope;
        private bool winding = false;
        private bool unwinding = false;
        private Entity entity1;
        private Entity entity2;
        private Ped ped;
        private float length;
        private DateTime time;
        private bool startedAnim = false;

        public Client()
        {
            //KeyDown += OnKeyDown;
            //KeyUp += OnKeyUp;
            //Tick += OnTick;

            //Interval = 1;
        }

        private void OnTick(object sender, EventArgs e)
        {
            try
            {
                if (ped != null && ped.Exists() && ped.Health > 0)
                {
                    if (time != null && !startedAnim && this.time.AddSeconds(2) <= DateTime.Now)
                    {
                        //ped.Task.ClearAllImmediately();
                        //ped.Euphoria.StopAllBehaviours.Start();
                    }

                    var pedFeet = Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, ped.Handle, 14201);
                    //if (pedFeet.Z >= World.GetGroundHeight(ped.Position) + 1.2f)
                    if (ped.HeightAboveGround > 0.4f)
                    {
                        
                        log(pedFeet + " world: " + World.GetGroundHeight(ped.Position));
                        if (!startedAnim)
                        {
                            ped.Task.PlayAnimation("script_re@public_hanging@female", "struggle_idle_female");
                            ped.AlwaysKeepTask = true;
                            startedAnim = true;
                        }
                        RDR2.UI.Screen.ShowSubtitle("hanged");
                        Script.Wait(40);
                        Function.Call(Hash._SET_ENTITY_HEALTH, ped.Handle, Math.Max(ped.Health - 1, 0));
                    } 
                    else
                    {
                        startedAnim = false;
                    }
                }
            }
            catch (Exception ex)
            {
                log(e.ToString());
            }
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            //if (e.KeyCode == Keys.F10)
            //{
            //    var pos = entity2.Position;
            //    var newPos = new Vector3(pos.X, pos.Y, pos.Z + 0.1f);
            //    this.entity2.Position = newPos;
            //}
        }

        private void OnKeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                if (e.KeyCode == Keys.F5)
                {
                    var player = Game.Player.Character;
                    //var ped = player;
                    var startPos = player.Position;
                    log("start pos " + startPos.ToString());
                    var result = World.Raycast(startPos, player.UpVector, 10, IntersectOptions.Map);

                    if (result.DitHit)
                    {
                        var dist = result.HitPosition.DistanceTo(startPos);
                        log(result.DitHit + " " + result.DitHitEntity + " " + result.HitPosition.ToString() + " " + dist);

                        if (dist > 10)
                        {
                            log("wrong distance");
                            return;
                        }

                        if (result.DitHitEntity)
                        {
                            log(result.HitEntity.EntityType.ToString());
                        }

                        var prop = CreateProp("p_shotGlass01x", result.HitPosition, false);
                        prop.FreezePosition = true;

                        var position = player.Position;
                        position.Z += 0.05f;
                        var ped = World.CreatePed((PedHash)ePedHash.A_F_M_LowerSDTownfolk_01, position);                        
                        Function.Call(Hash.SET_ENABLE_HANDCUFFS, ped.Handle, 1);

                        var neck = Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, ped.Handle, 14284);
                        var neckOffset = ped.GetOffsetFromWorldCoords(neck);

                        var len = neck.DistanceTo(prop.Position);
                        rope = CreateRope(result.HitPosition, Vector3.Zero, len, len, true);

                        var offset = prop.GetOffsetFromWorldCoords(neck);
                        var neckBoneIdx = Function.Call<int>(Hash.GET_PED_BONE_INDEX, ped.Handle, 14284);
                        log("ped pos " + ped.Position.ToString());
                        log("neck bone coords: " + neck.ToString());
                        log("offset: " + neckOffset.ToString());


                        //ped.AttachTo(prop, neckBoneIdx, offset, Vector3.Zero);
                        //Function.Call(Hash._SET_ENTITY_HEALTH, ped.Handle, 0);
                        //Function.Call(Hash.ATTACH_ENTITY_TO_ENTITY_PHYSICALLY, prop.Handle, ped.Handle, -1, Function.Call<int>(Hash.GET_PED_BONE_INDEX, ped.Handle, 14284), 0.02f, -0.11f, 0f, 0f, 0f, 0f, 183f, 88.5f, 97f, -1f, 0, 1, 0, 0, 0, 1, 1065353216, 1065353216);
                        //Function.Call(Hash.ATTACH_ENTITY_TO_ENTITY, ped.Handle, prop.Handle, 0, offset.X, offset.Y, offset.Z, 0, 0, 0, true, true, false, false, 2, 1);
                        //ped.AttachTo(prop, 0, offset, Vector3.Zero);

                        //Function.Call(Hash.ATTACH_ENTITY_TO_ENTITY_PHYSICALLY, prop.Handle, ped.Handle, -1, neckBoneIdx, 0, -0, 0f, 0f, 0f, 0f, 183f, 88.5f, 97f, -1f, false, true, false, true, 2);
                        //Function.Call(Hash.ATTACH_ENTITY_TO_ENTITY_PHYSICALLY, ped.Handle, prop.Handle, neckBoneIdx, -1, 0, 0, 0f, 0f, 0f, 0f, offset.X, offset.Y, offset.Z, -1f, 0, 0, 0, 0, 2);
                        //ped.Position = new Vector3(position.X, position.Y, position.Z + 0.5f);
                        //Function.Call(Hash._SET_ENTITY_HEALTH, ped.Handle, 0);
                        //log(Function.Call<int>(Hash.GET_ROPE_VERTEX_COUNT).ToString());
                        //log(Function.Call<Vector3>(Hash.GET_ROPE_LAST_VERTEX_COORD).ToString());

                        //var neckprop = CreateProp("p_shotGlass01x", neck, true, false);
                        //neckprop.AttachTo(ped, neckBoneIdx, neckOffset, Vector3.Zero);\
                        //ped.AttachTo(neckprop, neckBoneIdx, Vector3.Zero, neckOffset);
                        //neckprop.AttachTo(prop, -1, offset, Vector3.Zero);
                        //rope.AttachEntities(prop, Vector3.Zero, ped, neckOffset, len);
                        rope.AttachEntities(prop, Vector3.Zero, ped, neckOffset, len);


                        entity1 = prop;
                        entity2 = ped;
                        length = len;
                    }
                }
                else if (e.KeyCode == Keys.F3)
                {
                    if (ped != null)
                    {
                        Function.Call(Hash._SET_ENTITY_HEALTH, ped.Handle, 0);
                    }
                }
                else if (e.KeyCode == Keys.F7)
                {

                    this.time = DateTime.Now;
                    var player = Game.Player.Character;
                    var pos1 = player.Position + player.ForwardVector;
                    var pos2 = player.Position + player.ForwardVector * 4;

                    //var prop = CreateProp("p_detonator01x", pos1);
                    ped = World.CreatePed((PedHash)ePedHash.A_F_M_LowerSDTownfolk_01, pos2);
                    //ped.Task.PlayAnimation("script_re@public_hanging@female", "struggle_idle_female");
                    //World.ShootBullet(pos1, ped.Position, player, new Model(2055893578), 1);
                }


                else if (e.KeyCode == Keys.F2)
                {
                    this.time = DateTime.Now;
                    var player = Game.Player.Character;
                    var firstPosition = player.Position + player.ForwardVector * 3;

                    firstPosition = new Vector3(firstPosition.X, firstPosition.Y, World.GetGroundHeight(firstPosition) + 3f);
                    var prop2 = CreateProp("p_detonator01x", firstPosition);
                    prop2.FreezePosition = true;

                    var chair = CreateProp("p_chair25x", new Vector3(firstPosition.X, firstPosition.Y, World.GetGroundHeight(firstPosition)));
                    var secPos = new Vector3(firstPosition.X, firstPosition.Y, World.GetGroundHeight(firstPosition));
                    ped = World.CreatePed((PedHash)ePedHash.A_F_M_LowerSDTownfolk_01, secPos);
                    var neckIdx = Function.Call<int>(Hash.GET_PED_BONE_INDEX, ped.Handle, 14284);

                    //Wait(100);
                    //var horse = World.CreatePed((PedHash)ePedHash.A_C_Horse_Andalusian_RoseGray, secPos);
                    //horse.Position = ped.Position;
                    //Function.Call(Hash._SET_PED_ON_MOUNT, ped.Handle, horse.Handle, 0, true);


                    var neckCoords = ped.GetOffsetFromWorldCoords(Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, ped.Handle, 14284));


                    var len = Function.Call<Vector3>(Hash.GET_PED_BONE_COORDS, ped.Handle, 14284).DistanceTo(prop2.Position) - 0.4f;

                    //int ropeId = Function.Call<int>(Hash.ADD_ROPE, firstPosition.X, firstPosition.Y, firstPosition.Z, 0.0f, 0.0f, 0.0f, 1.0f, 14, 1.0f, 1.0f, 1.0f, 0, 1, true, 1.25f, false, 0, 0);
                    //Function.Call(Hash._0x462FF2A432733A44, ropeId, ped.Handle, prop2.Handle, 0f, 0f, 0f, 0f, 0f, 0.0f, "SKEL_R_Finger12", 0);
                    //Function.Call(Hash.ACTIVATE_PHYSICS, ropeId);
                    //Function.Call(Hash._0x3C6490D940FF5D0B, ropeId, 0, 0, 7f, 0);
                    //int ropeId = Function.Call<int>(Hash.ADD_ROPE, firstPosition.X, firstPosition.Y, firstPosition.Z, 0.0f, 0.0f, 0.0f, len, 14, len * 2, len, 1.0f, 0, 1, true, 1.25f, false, 0, 0);


                    //Function.Call(Hash.ATTACH_ENTITY_TO_ENTITY_PHYSICALLY, prop1.Handle, ped.Handle, -1, neckIdx, 0.02f, -0.11f, 0f, 0f, 0f, 0f, 183f, 88.5f, 97f, -1f, 0, 1, 0, 0, 0, 1, 1065353216, 1065353216);

                    prop2.FreezePosition = true;
                    int ropeId = Function.Call<int>(Hash.ADD_ROPE, firstPosition.X, firstPosition.Y, firstPosition.Z, 0.0f, 0.0f, 0.0f, len, 14, len , len, 1.0f, 0, 1, true, 1.25f, false, 0, 0);
                    Function.Call(Hash._0x462FF2A432733A44, ropeId, ped.Handle, prop2.Handle, 0f, 0f, 0f, 0f, 0f, 0.0f, "SKEL_NECK0", 0);
                    Function.Call(Hash.ACTIVATE_PHYSICS, ropeId);
                    Function.Call(Hash._0x3C6490D940FF5D0B, ropeId, 0, 0, len, 0);

                    Function.Call(Hash.SET_ENABLE_HANDCUFFS, ped.Handle, 1);


                    //Wait(1000);
                    //Function.Call(Hash._REMOVE_PED_FROM_MOUNT, ped.Handle);
                    //Function.Call(Hash.TASK_ANIMAL_FLEE, horse.Handle);

                    entity1 = ped;
                    entity2 = prop2;
                    length = len;
                    this.rope = new Rope(ropeId);
                }

                else if (e.KeyCode == Keys.F9)
                {

                    var player = Game.Player.Character;
                    var pos1 = player.Position + player.ForwardVector;
                    var pos2 = player.Position + player.ForwardVector * 4;

                    var ped1 = World.CreatePed((PedHash)ePedHash.A_F_M_LowerSDTownfolk_01, pos1);
                    var ped2 = World.CreatePed((PedHash)ePedHash.A_F_M_LowerSDTownfolk_01, pos2);

                    ped1.GiveWeapon(WeaponHash.Lasso, 100, true, false);
                    Function.Call(Hash.TASK_LASSO_PED, ped1.Handle, ped2.Handle);
                    
                }
                else if (e.KeyCode == Keys.F10)
                {
                    //RDR2.UI.Screen.ShowSubtitle("hello world ~INPUT_CONTEXT~");
                    
                    //new RDR2.UI.TextElement("hello world ~INPUT_CONTEXT~", new System.Drawing.PointF(), 1, System.Drawing.Color.Black, Alignment.Center, false, false, 0f);
                    if (entity2 != null)
                    {
                        entity2.Position = entity2.Position + entity2.UpVector * 0.1f;
                    }
                }


            }
            catch (Exception ex)
            {
                log(ex.ToString());
            }
        }


        private Prop CreateProp(string model, Vector3 position, bool dynamic = true)
        {
            var prop = new Prop(Function.Call<int>(Hash.CREATE_OBJECT, new Model(model), position.X, position.Y, position.Z, false, false, dynamic));
            //Function.Call(Hash.SET_ENTITY_COLLISION, prop.Handle, collisionk, true);

            return prop;

        }

        private Rope CreateRope(Vector3 position, Vector3 rotation, float length, float minLength, bool breakable)
        {
            int handle = Function.Call<int>(Hash.ADD_ROPE, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, length, 1, length, 0, 0f, true, true, false, 5f, breakable);
            return new Rope(handle);
        }

        private void Attach(Rope rope, Entity ent1, Entity ent2, float len)
        {
            Function.Call(Hash.ATTACH_ENTITIES_TO_ROPE, rope.Handle, ent1.Handle, ent2.Handle, 0, 0, 0, 0, 0, 0, len, true, false);
        }

        private void log(string msg)
        {
            var logfile = this.BaseDirectory + "/Lasso.txt";
            File.AppendAllText(logfile, msg + "\n");
        }
    }
}
