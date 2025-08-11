#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    string sLoc;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    
    bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
    bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

    switch(Dialog.CurrentNode)
    {
        case "First time":
            if (LAi_grp_playeralarm > 0)
            {
                dialog.text = NPCharRepPhrase(pchar,
                    LinkRandPhrase("镇上已经拉响警报了。 所有人都在找你! 如果我是你, 就不会在这里久留。 ", "整个卫兵队都在城里搜捕你。 我不是傻瓜, 不会和你说话的! ", "快跑, 伙计, 趁士兵们还没把你剁成碎肉... "),
                    LinkRandPhrase("你需要什么, 恶棍? ! 镇上的卫兵已经在追你了。 你跑不远的, 海盗! ", "肮脏的杀手, 滚出我的房子! 卫兵!! ", "我不怕你, 狗东西! 绞刑架在召唤你, 你跑不远的... "));
                link.l1 = NPCharRepPhrase(pchar,
                    RandPhraseSimple("呵, 我不担心警报... ", "他们没机会抓住我。 "),
                    RandPhraseSimple("闭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 不然我就把你该死的舌头割下来。 ", "呵, " + GetWorkTypeOfMan(npchar, "") + ", 你也想追捕海盗? 听着, 伙计, 保持冷静, 你或许还能活下来... "));
                link.l1.go = "exit";
                break;
            }
            if (npchar.quest.meeting == "0")
            {
                dialog.text = TimeGreeting() + "! 欢迎, " + GetAddress_Form(NPChar) + "来到洛斯-特克斯矿场酒馆。 食物。 饮料和姑娘, 全部价格实惠! 我叫" + GetFullName(npchar) + ", 随时为您服务。 ";
                Link.l1 = "让我看看... 我是" +GetFullName(pchar)+ "。 很高兴见到你, " + npchar.name+ "。 ";
                Link.l1.go = "meeting";
                npchar.quest.meeting = "1";
            }
            else
            {
                dialog.text = "啊哈, 这不是我的老熟人, " +GetFullName(pchar)+ "船长嘛! 很高兴见到你, 老兄! 要朗姆酒, 还是姑娘? ";
                if (makeint(pchar.money) >= 5)
                {
                    link.l1 = "给我倒点朗姆酒, " + npchar.name+ "。 ";
                    link.l1.go = "drink";
                }
                link.l2 = "我想睡一会儿。 你有空闲的房间吗? ";
                link.l2.go = "room";
                link.l3 = LinkRandPhrase("你有什么最新消息吗? ", "这地方有什么新鲜事? ", "陆地上的生活过得怎么样? ");
                link.l3.go = "rumours_tavern";
                link.l4 = "不, 我什么都不需要, " + npchar.name+ "。 我只是顺道来跟你打个招呼。 ";
                link.l4.go = "exit";
            }
            NextDiag.TempNode = "First time";
        break;
        
        case "meeting":
            dialog.text = "哦, 我太高兴了! 在我们这个城市, 新面孔可不多见。 我给你倒点朗姆酒, 我们聊聊天怎么样... ";
            link.l1 = "这是我第一次来这里, 我想多了解一下这个定居点。 ";
            link.l1.go = "info";
            if (makeint(pchar.money) >= 5)
            {
                link.l2 = "给我倒点朗姆酒, " + npchar.name+ "。 ";
                link.l2.go = "drink";
            }
            link.l3 = "我想睡一会儿。 你有空闲的房间吗? ";
            link.l3.go = "room";
        break;
        
        case "info":
            dialog.text = "没什么有趣的事可讲。 每天都是一样的事情: 无聊。 阳光和尘土。 这里只住着士兵。 黑人和印第安人。 你可能还会遇到一些冒险家和渴望黄金的强盗。 \n有时, 像你这样的绅士。 船长会来我们这里, 用奴隶换锭子, 买贵金属。 我们的商人是个很有趣的人, 他不仅卖金块和银块, 还卖半宝石。 \n他声称有特殊知识的人可能会发现这些小石子非常有用。 所以去我们的商店看看吧。 矿本身位于山的更深处。 如果你愿意, 你可以去那里, 但我建议你不要让卫兵不高兴。 \n不要和囚犯说话, 上帝保佑你别偷窃。 不管怎样, 这个定居点最好的地方就是我的酒馆, 是在这个燃烧的地狱中休息的最好地方! ";
            link.l1 = "谢谢你的信息! ";            
            link.l1.go = "exit";
        break;
        
        case "drink":
            if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
            {
                dialog.text = "船长, 我认为你最好停下来。 上帝保佑你在酒精的影响下别惹事。 我们这里对此非常严格。 即使是你的权威也帮不了你。 ";
                link.l1 = "嗯... 我想你是对的 —我已经喝够了。 谢谢你的关心! ";            
                link.l1.go = "exit";
            }
            else
            {
                AddMoneyToCharacter(pchar, -5);
                if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
                {
                    if (CheckAttribute(pchar, "questTemp.Rum"))
                    {
                        pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
                    }
                    else pchar.questTemp.Rum = 1;
                }
                else 
                {
                    if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
                }                
                WaitDate("",0,0,0, 0, 30);
                
                dialog.text = "不客气, 船长。 一品脱我最好的牙买加黑朗姆酒只要五比索! ";
                link.l1 = RandPhraseSimple(LinkRandPhrase("好的, 为你的健康和你酒馆的繁荣干杯, 伙计! ", "好的, 为海上的人们干杯! ", "好的, 为你城镇的福祉干杯! "), LinkRandPhrase("好的, 为生产的风, 为一阵幸运, 让我们都生活得更轻松和富有! ", "好的, 为所有事情都一帆风顺干杯! ", "好的, 为幸福。 幸运。 快乐和姑娘们干杯! "));        
                link.l1.go = "drink_1";
            }
        break;
        
        case "drink_1":
            DialogExit();
            LAi_Fade("", "");
            if (CheckAttribute(pchar, "questTemp.Rum"))
            {
                DeleteAttribute(pchar, "chr_ai.drunk");
                if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
                else
                {
                    LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
                    Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
                }
            }
        break;
        
        case "room":
            if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
            {
                dialog.text = "先生, 你已经付了房间和姑娘的钱。 上楼去吧, 她已经等你一会儿了。 ";
                link.l1 = "好的。 ";
                link.l1.go = "exit";
                break;
            }
            dialog.text = "我们有。 你打算住多久? ";
            if(!isDay())
            {
                link.l1 = "到早上。 ";
                link.l1.go = "room_day";
            }
            else
            {
                link.l1 = "到晚上。 ";
                link.l1.go = "room_night";
                link.l2 = "到第二天早上。 ";
                link.l2.go = "room_day_next";
            }
        break;

        case "room_day":
            dialog.text = "那要十比索。 你想要房间里再配个姑娘吗? 姑娘只要一千比索。 ";
            if (makeint(pchar.money) >= 10)
            {
                link.l1 = "不, 我不需要姑娘。 给你, 这是房钱。 ";
                link.l1.go = "room_day_wait";
            }
            if (makeint(pchar.money) >= 1010)
            {
                if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
                {
                    link.l2 = "好的, 我要房间和姑娘。 给你钱。 ";
                    link.l2.go = "room_girl";
                    sTotalTemp = "wait_day";
                }
            }
            link.l3 = "唉, 我住不起这个房间。 ";
            link.l3.go = "exit";
        break;

        case "room_day_next":
            dialog.text = "那要十比索。 你想要房间里再配个姑娘吗? 姑娘只要一千比索。 ";
            if (makeint(pchar.money) >= 10)
            {
                link.l1 = "不, 我不需要姑娘。 给你, 这是房钱。 ";
                link.l1.go = "room_day_wait_next";
            }
            if (makeint(pchar.money) >= 1010)
            {
                if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
                {
                    link.l2 = "好的。 我们要房间和姑娘。 给你钱。 ";
                    link.l2.go = "room_girl";
                    sTotalTemp = "wait_day";
                }
            }
            link.l3 = "唉, 我住不起这个房间。 ";
            link.l3.go = "exit";
        break;

        case "room_night":
            dialog.text = "那要十比索。 你想要房间里再配个姑娘吗? 姑娘只要一千比索。 ";
            if (makeint(pchar.money) >= 10)
            {
                link.l1 = "不, 我不需要姑娘。 给你, 这是房钱。 ";
                link.l1.go = "room_night_wait";
            }
            if (makeint(pchar.money) >= 1010)
            {
                if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
                {
                    link.l2 = "好的。 我们要房间和姑娘。 给你钱。 ";
                    link.l2.go = "room_girl";
                    sTotalTemp = "wait_night";
                }
            }
            link.l3 = "唉, 我住不起这个房间。 ";
            link.l3.go = "exit";
        break;

        case "room_night_wait":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
            AddMoneyToCharacter(pchar, -10);
            AddDialogExitQuest("sleep_in_tavern");
            TavernWaitDate("wait_night");
        break;

        case "room_day_wait":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
            AddMoneyToCharacter(pchar, -10);
            AddDialogExitQuest("sleep_in_tavern");
            TavernWaitDate("wait_day");
        break;

        case "room_day_wait_next":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
            AddMoneyToCharacter(pchar, -20);
            AddDialogExitQuest("sleep_in_tavern");
            TavernWaitDate("wait_day");
        break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "请上楼吧, 先生。 姑娘正在等您。 祝您愉快! ";
			link.l1 = "谢谢, 伙计... ";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //关闭酒馆
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //打开房间
			bDisableFastReload = true;//关闭传送
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "嘿, 白人老爷。 别那样看着" + npchar.name+ ", " + npchar.name+ "知道怎么做得比妓院的白种女人还要好。 啊, 先生您真英俊... 保证, 这个印第安女人会爱您很久。 ";
			link.l1 = "听起来不错, 让我看看你最棒的印第安魅力。 我不需要祈雨舞就能让你湿透... ";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== 白昼抢劫, 试图潜入宝箱 =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("光天化日之下抢劫!!! 这里发生了什么? ! 等等, 等等, 伙计... ", "嘿, 你在那里干什么? ! 想抢劫我? 现在你死定了... ", "等等, 你到底在干什么? 原来你是个小偷! 这就是你的末日, 混蛋... ");
			link.l1 = LinkRandPhrase("魔鬼! ", "操! ", "啊, shit");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); //用脚逃跑
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); //对不死的梅拉不起作用 :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); //幻影士兵
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
