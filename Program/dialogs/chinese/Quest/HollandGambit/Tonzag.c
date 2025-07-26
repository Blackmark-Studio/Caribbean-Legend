// 赫丘勒.通扎格, 又名"疤面"加斯顿
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индeкс в концe
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "你好, " +pchar.name+ "。 很高兴看到你还活着。 ";
				link.l1 = "加斯顿! 是你吗? ";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "问候你, " +pchar.name+ "。 我已经知道你的事迹了 --约翰把一切都告诉我了。 我甚至不知道该说什么。 我佩服你! ";
				link.l1 = "能听到你这样的赞扬, 我很荣幸, 赫丘勒! ";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "下午好。 你有什么事找我吗? ";
			link.l1 = "没有。 我搞错了。 抱歉。 再见。 ";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "你曾用那个名字认识我。 但我的真名是赫丘勒。 赫丘勒.通扎格。 ";
			link.l1 = "我的上帝! 我也很高兴见到你... 在激烈的战斗中我没认出你。 你来得正是时候。 ";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "在你离开后, 我得到消息说弗利特伍德加强了他房子的防护。 我认为这背后可能有陷阱。 我立即驾驶我的船'暮光号'起航前往安提瓜 --如你所见, 这是有充分理由的。 ";
			link.l1 = "没错。 我勉强解决了房子里的守卫, 但在街道上战斗时我已经筋疲力尽... ";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "这场战斗后, 弗利特伍德将一名荷兰间谍列入了通缉名单。 他们认为你是荷兰间谍。 他和荷兰人有深仇大恨。 最糟糕的是, 房子里有一个士兵幸存下来, 还记得你的脸。 不过, 现在这不是问题了。 我已经完成了你开始的事情。 这个士兵再也无法指认任何人了, 也没有人能认出他... ";
			link.l1 = "你杀了他? 我明白了... ";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "是的。 当你在约翰的房子里昏迷不醒时, 我打伤了弗利特伍德, 但那混蛋还是活了下来。 我弄瞎了他 --把胡椒撒进他的眼睛, 然后在他拔剑之前击中了他。 但那混蛋在制服下穿了锁子甲 --这救了他的命。 很聪明。 现在他在家卧床休息, 安保加强了。 他活下来真是不幸。 ";
			link.l1 = "那么, 你在安提瓜的主要任务是除掉弗利特伍德? ";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "总的来说, 是的。 不过现在看来不可能了 --房子总是锁着的, 有半打精选的卫兵全天候值班, 只允许他的亲信 --一个名叫查理的老炮手, 绰号'捏子'--进去见他。 ";
			link.l1 = "这已经很重要了... ";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "等一下... 你打算介入这件事吗? ";
			link.l1 = "为什么不呢? 你不需要帮助吗? 你救了我, 我想帮忙。 另外, 我还需要钱。 ";
			link.l1.go = "SJ_talk_6";
			// belamour传奇版 -->
			link.l2 = "为什么不呢? 你们是认真的人。 而认真的人付钱慷慨。 我只是在找工作。 ";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "相信我, 朋友, 你办不到。 你是个好人, 真正的人才, 你拿来的日志帮助我计划了对弗利特伍德的刺杀, 你在砍杀卫兵方面做得很好 --但你现在永远无法接近弗利特伍德。 就连我也毫无头绪。 ";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "我会考虑的。 我还有时间。 可惜我的船被扣押了, 我也没有船员。 ";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "我会考虑的。 我有时间和船。 ";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <—— 传奇版
			dialog.text = "相信我, 朋友, 你办不到。 你是个好人, 真正的人才, 你拿来的日志帮助我计划了对弗利特伍德的刺杀, 你在砍杀卫兵方面做得很好 --但你现在永远无法接近弗利特伍德。 就连我也毫无头绪。 ";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "我会考虑的。 我还有时间。 可惜我的船被扣押了, 我也没有船员。 ";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "我会考虑的。 我有时间和船。 ";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "别担心。 当你的旧船被扣押时, 我把你所有的军官和一些水手接到了我的'暮光号'上。 他们知道你还活着, 并同意继续服役。 作为对日志的奖励, 我把我的船'暮光号'交给你。 ";
			link.l1 = "谢谢你! 我会记住的! ";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "暮光号";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "是的, 我想为日志付钱给你。 15000比索 --不幸的是, 我现在没有更多了。 我们一天内会结清。 ";
			link.l1 = "不需要。 这足够了。 如果你没有及时赶到, 我反正也不需要钱了。 ";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "好了, " +pchar.name+ ", 我得走了。 我还不打算回布里奇敦。 如果你需要我 --问约翰。 祝你好运! ";
			link.l1 = "祝你好运, 赫丘勒! ";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "我想送给你这件盔甲, 以表彰你除掉弗利特伍德。 它会在未来的战斗中保护你。 现在我们去见约翰吧。 他想和你谈谈, 并给你提供... 一个有趣的差事。 ";
			link.l1 = "谢谢你的礼物。 好吧, 我们走... ";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");// 给物品
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "我也想和你谈谈, 船长。 我本来打算教你我的技艺, 但现在我发现应该是我向你学习。 雇佣我作为你船上的军官 --你不会后悔的。 ";
			link.l1 = "非常乐意, 赫丘勒! 欢迎加入船员! ";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "赫丘勒, 我无法想象自己成为你的上级。 谢谢你的提议, 但我就是无法把你当作我的下属。 ";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1":// 通扎格 - 加入军官
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP	   = 60.0; 
			npchar.Health.maxHP	= 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "如你所愿, " +pchar.name+ "。 再见。 也许我们会再见面。 很高兴与你合作。 ";
			link.l1 = "祝你好运, 朋友! ";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ---------------------------------—— 军官模块 ------------------------------------------
		case "tonzag_officer":
			dialog.text = "我在听你说, 船长。 你有什么事? ";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "赫丘勒, 我要去古老的印第安城市泰亚萨尔, 更不寻常的是, 我的路要经过一座传送雕像。 你愿意加入我吗? ";
				Link.l4.go = "tieyasal";
			}
			
			// boal 关于船的报告
           	// boal отчёт о кораблe
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
				Link.l11 = "赫丘勒, 给我一份完整的船只报告。 ";
				Link.l11.go = "QMASTER_1";
				
				// 战船。 自动购买货物
				Link.l12 = "我希望你每次靠岸时购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Я прибыл по вашeму распоряжeнию, капитан.";
				Link.l2 = "我需要给你下达一些命令。 ";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";
				break;
			}
			Link.l1 = "听我的命令! ";
            Link.l1.go = "stay_follow";
			link.l2 = "目前没什么事。 稍息! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		// 司库的回答 ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "船长, 抱歉, 但我不处理数字和计算。 问范.默登 --他对这种事情有诀窍, 不过我怀疑他不会有兴趣离开他的窝。 ";
			Link.l1 = "你说得对, 赫丘勒。 嗯, 得给我找个出纳员... ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "船长, 我在巴巴多斯当客栈老板时, 只购买朗姆酒和补给品。 而补给品, 我指的是合适的食物, 不是一些饼干和咸牛肉。 抱歉, 但这不是我的职责范围。 ";
			link.l1 = "也许我们应该把我的船变成酒馆... 开玩笑的, 赫丘勒。 不管怎样, 我自己来做。 ";
			link.l1.go = "exit";
		break;
		
		// 给同伴的指示 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "我在听你说。 ";
			Link.l1 = "这是关于登船的。 ";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "这是关于你的船的。 ";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "目前没什么。 ";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "你有什么愿望。 ";
			Link.l1 = "不要登敌船。 照顾好自己和船员。 ";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "我希望你登敌船。 ";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "你有什么愿望。 ";
			Link.l1 = "我希望你登船后不要把你的船换成另一艘。 它太有价值了。 ";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "当你登敌船时, 如果它们不错, 你可以自己拿下。 ";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "是, 是。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "遵命。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "是, 是。 ";
			Link.l1 = "会完成的。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "会完成的。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//  <========////////////////////////////////////////
		
		case "stay_follow":
			dialog.Text = "你有什么命令? ";
			Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
			Link.l2 = "跟着我, 别掉队! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "更换你的弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弹药类型选择: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
			dialog.Text = "是! ";
			Link.l1 = "稍息。 ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
			dialog.Text = "是! ";
			Link.l1 = "稍息。 ";
            Link.l1.go = "Exit";
        break;
	//<—— ---------------------------------—— 军官模块 ----------------------------------------
	
	// 在泰亚萨尔
		case "tieyasal":
			dialog.text = "你这个幸运的混蛋, 船长。 我很高兴在我。 你和约翰一起工作时加入了你。 如果我不支持你这次冒险, 就让鲨鱼吞了我! ";
			link.l1 = "谢谢你, 赫丘勒! 我很高兴我没有看错你。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "那么, 我们什么时候出发? ";
			link.l1 = "稍后。 现在我们应该为旅程做准备。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "没什么好消息, 船长。 如果这与我们的生意有关, 他们早就把我们放在刑具上了。 \n既然他们没有马上带我们去审讯, 事情显然不紧急。 \n要么是圈套, 要么是勒索。 \n他们会把我们在这里关几天, 不做任何解释。 然后他们会提出一个我们会接受的提议。 ";
			link.l1 = "个人经历? ";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "那么有没有办法让他们现在就提出这样的提议? ";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "当然。 格鲁奥曾经受一个死人的亲属委托, 让他免受特立尼达刽子手的最后折磨。 \n她付钱给指挥官, 获得了走进牢房的权利。 常见做法 --很多人付钱给士兵, 让他们有机会在没有证人的情况下折磨那些无法反抗的人。 \n那个人死得很安静, 没有痛苦。 干净利落的工作。 ";
			link.l1 = "格鲁奥? 那是谁? ";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "抱歉, 船长。 时机不对, 地点不对。 ";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "我们可以试试。 等喂食时间, 我和哨兵说几句话。 你看, 他们还没学会正确搜查。 嗯... ";
			link.l1 = "怎么了? ";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "奇怪的感觉, 船长。 我甚至会称之为预感。 抱歉, 我们稍后再谈。 ";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "我错过什么了吗, 船长? ";
			link.l1 = "哦, 没什么特别的, 只是海上的又一天。 看看, 你这个老魔鬼! 你给我在这里弄得一团糟。 ";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "血可以用冷水洗掉, 船长。 我们需要谈谈。 ";
			link.l1 = "你觉得? 首先活过今天再说。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "我也很高兴见到你, 伦巴。 船长, 我不打扰你了, 我们稍后再谈。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "嘿, 金吉。 船长, 我不打扰了, 我们稍后再谈。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "船长, 我不打扰你了, 我们稍后再谈。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "准备好听我说了吗, 船长? ";
			link.l1 = "是时候谈谈了, 赫丘勒。 我刚刚意识到我几乎不了解你。 ";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "那么是时候认识一下了。 我们跳过早年吧, 只是因为那里没什么可谈的 --胜利的士兵, 失败的士兵, 逃兵, 掠夺者... 你知道是怎么回事。 ";
			link.l1 = "实际上我不知道, 但到目前为止这听起来很普通。 ";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "在这样的军事生涯之后, 我的职业机会很少 --强盗, 吊死的人, 或者值得荷兰西印度公司的卫兵。 如你所知, 我选择了后者。 ";
			link.l1 = "你也从那里逃走了? ";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "相反, 我在那里取得了职业发展。 我收到了加入公司情报部门战斗部队的邀请, 在那里我遇到了我未来的妻子。 ";
			link.l1 = "好吧, 到目前为止故事还很平静... 尤其是如果你不多想荷兰人的手段。 ";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "诚实赚不到大钱, 你可以用各种方式对抗竞争。 是的, 我们通过特殊手段运作... ";
			link.l1 = "我想我知道你的意思... ";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "是的, 可能是任何事情: 从海盗行为到放火焚烧货物仓库。 最后, 这个计划被曝光, 我们被解散了... 当然是名义上的。 这就是联盟的诞生, 只有公司高层的选定领导人知道和控制。 对于一个值得一提的加勒比亡命之徒, 只有两个选择: 海盗或联盟。 而联盟通常支付得更好\n在很大程度上, 联盟仍然为荷兰人工作, 但也可以接受兼职订单... ";
			link.l1 = "事情开始清楚了... ";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "联盟是托尔图加那场闹剧的幕后黑手。 然后是登陆队... ";
			link.l1 = "我猜到了。 但为什么? ";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "因为没有人能活着离开联盟, 你不能带着我们在那里做的事情安然无恙, 船长。 我想退休, 所以我还是试了试。 如你所见, 不太成功。 ";
			link.l1 = "你是说你以前的同事花费巨大, 几乎扔掉了一百人, 烧毁了一艘船, 冒着他们的战船的风险只是为了... 因为擅离军队而杀了你? ";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "我在联盟里不止是个小角色, 船长。 我知道太多了。 不能让我走, 他们需要明确这一点, 这样就不会有人再想离开这个行业... 他们之前试图接近我... 很久以前... 他们杀了我的妻子, 毁了我的容貌, 尽管这让他们付出了沉重的代价。 这个故事没有幸福的结局, 船长。 只要下命令, 我就会离开船, 最后一次自己处理他们。 ";
			link.l1 = "别胡说八道, 赫丘勒... 卢卡斯.罗登堡在这一切中扮演了什么角色? 他一定参与了这些事情! 你的, 或者说他的'组织', 联盟... ";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "不同的机构, 船长。 诚然, 他们经常服从同一个人, 密切合作。 但罗登堡的特别特工进行精确有效的打击, 而联盟则进行大规模行动。 现在联盟变成了什么? 正如你所见, 组织已经不复存在: 我和你在一起, 约翰.默多克离开了, 隆威跑了, 范.伯格在海底, 罗登堡被处决了... 不过, 我欠那个已故的混蛋。 他在联盟中注意到了我, 当我试图离开时, 他把我从一些严重的麻烦中拉了出来, 让我做他的副手。 当然, 其他人不喜欢, 但没有人敢违抗他... 然后, 在已知的情况下, 他决定摆脱默多克和我, 但你介入了, 把我招入你的麾下\n于是我想,'这是我与过去决裂的第二次机会...'你胜过了罗登堡, 联盟失去了赞助人, 不再有危险... 但当然, 我错了... 老傻瓜... 但够了, 船长。 让我们想想接下来该做什么, 如果当然你真的不打算在第一个港口让我走。 ";
			link.l1 = "我不打算。 我想你有计划? ";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "实际上没什么特别的。 我们永远无法消灭他们所有人, 但我们可以给他们造成巨大损失, 让他们觉得继续追我... 我们不值得。 ";
			link.l1 = "我们怎么做? 他们有营地吗? ";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "一个大堡垒? 不太可能。 这对联盟来说太显眼太危险了。 我说的损失不是人员损失 --他们不在乎人, 但他们不会喜欢失去黄金。 公司的钱不再给他们了, 对吧? 我怀疑联盟找到了新的赞助人, 所以他们一定是从别的地方榨取黄金。 ";
			link.l1 = "那会是什么地方? ";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "我不知道, 船长。 ";
			link.l1 = "赫丘勒, 但你刚才说你被追捕正是因为你知道太多! ";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "让我想想... 也许联盟目前在对付西班牙人。 他们是首要的掠夺对象。 顺便说一句, 罗登堡总是和卡斯蒂利亚的肥猫们关系很好。 有时他会指示联盟的小子们为他们做各种工作, 并总是禁止对他们造成任何伤害, 顺便说一句, 小子们对此很不喜欢... ";
			link.l1 = "你说关系很好? 那你让我拖到你酒馆的那个绅士和他的手指呢? ";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "那是个特例, 兼职订单。 如果你感到内疚, 船长, 可以放心 --那个唐罪有应得... 但我在说别的: 在他们的雇主消失后, 联盟特工可能只是屈服于自己的欲望, 试图从西班牙馅饼中捞一块大的。 由于在罗登堡手下与西班牙人合作, 他们知道该去哪里拿什么。 ";
			link.l1 = "嗯... 你可能是对的。 但据我所知, 没有人真的闯入西班牙银行, 在海上对抗西班牙人 --那要看运气... 也许我们应该找一些西班牙企业? 工厂? ";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "合理的假设, 船长... 我们还有其他线索吗? ";
			link.l1 = "嗯... 今天攻击我们的船向南去了... ";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "它的船长不太可能再打扰我们了, 但他必须警告其他人事情没有按计划进行, 也许还会把人员运到另一个地方。 还有别的吗? ";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "是的, 我和托尔图加监狱长友好交谈过... 他提到了大陆。 ";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "没有, 没别的了。 ";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "太好了, 船长! 南方, 大陆, 西班牙人 --意味着我们很快就能找到他们。 我们起航吗? 谢谢你听我的故事。 ";
			link.l1 = "是啊, 我们最后进行了一次推心置腹的谈话... 我们起航吧! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "线索不多。 但对我们这样的人来说足够了。 我们向南走吗? 寻找一家西班牙商业企业? 谢谢你听我的故事。 ";
			link.l1 = "是啊, 我们最后进行了一次推心置腹的谈话... 我们起航吧! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "看, 船长。 他们就是这样运作的。 ";
			link.l1 = "你也这样工作过? ";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "我们走, 看看里面有什么。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "肮脏的交易, 船长。 我们清除了这个巢穴, 但这肯定不是最后一个... ";
			link.l1 = "那矿场呢, 赫丘勒? ! 外面所有的人? ! 他们也被'清除'了! 那个混蛋是什么意思? ";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "我们稍后再讨论这个, 船长。 他们的指挥官幸存下来; 我们需要审问他。 ";
			link.l1 = "如果他什么都不知道呢? ";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "他知道一些事情。 想想看 --他们在等我们, 运走了所有的黄金, 消灭了证人。 这意味着他们有计划。 我想在这里看看, 稍后我会亲自把那个混蛋带到船上。 你也应该留意一下; 也许他们太匆忙了, 错过了什么。 ";
			link.l1 = "好吧, 但当我们回到船上时, 有一场严肃的谈话要进行! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "好消息, 船长。 ";
			link.l1 = "我在我们的处境中看不到任何好消息, 赫丘勒。 我们走, 我们需要私下谈谈。 ";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "是这样吗, 嗯? 是, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "我看我们要有一场严肃的谈话了, 船长。 ";
			link.l1 = "是的, 而且我将是那个说话的人。 首先, 你不觉得这里有一个趋势吗? 无论我们走到哪里, 都有一堆尸体! 首先, 你被葡萄弹击中腹部, 第二天就有一百多人, 不管好坏, 死于... 我甚至不能称之为海战! 一个定居点几天前被摧毁, 今天我们在矿场屠杀了一群人, 为不断增长的尸体堆做出了贡献。 ";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "自然, 我担心明天尸体会变成山, 但真正让我害怕的是, 所有这些血都是因为一个人而流的。 而那个人在我的船员中占有重要地位! ";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "其次, 你骗了我, 赫丘勒。 没有逃离岗位者值得你以前的同事付出这么大的努力来除掉你。 我们的囚犯在矿场喊了什么? 叛徒? 贝洛港? 格鲁奥? 你做了什么, 赫丘勒, 这次我要真相。 ";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "真相? 真相是, 船长, 我确实擅离军队了, 和我的妻子格鲁奥一起。 唐扎格夫人不想离开联盟; 她热爱那种生活, 但她更爱我。 我们本应照顾一个西班牙idalgo, 但他提出了更好的条件。 这是我们的机会, 我们都同意为他服务。 当然, 联盟认为我们在一次任务中丧生, 并派了第二组人去贝洛港完成任务并寻求报复。 ";
			link.l1 = "你把他们都杀了? ";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "首先, 他们杀了格鲁奥, 毁了我的容貌。 那个绅士不想再和我有任何关系, 把我赶了出去。 就在那时罗登堡找到了我... ";
			link.l1 = "我现在该如何信任你? 你舍弃了军队, 舍弃了联盟, 杀了自己的伙伴! 当时机成熟时, 你也会背叛我吗? ";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "是的, 我擅离军队了, 我违反了合同, 我杀了几十个联盟成员。 但我已经吸取了教训, 船长。 此外, 死人不能背叛任何人, 而我已经死了很久了, 自从贝洛港之后。 也许这就是为什么现在很难杀死我。 ";
			link.l1 = "今天就到这里吧。 我觉得你还是没有告诉我一切。 ";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "我会自己处理囚犯, 或者你想加入? ";
			link.l1 = "我们走。 我自己审问他。 ";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "不, 这种事不适合我。 半小时后在我的船舱见! ";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "现在谁负责? 阿诺? ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "那个混蛋掌权了? 你很快就堕落成一群普通的强盗了... ";
			link.l1 = "奥斯汀是谁? ";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "奥斯汀的团伙以引诱自由船长进入荒野, 将他们砍碎, 并彻底剥夺他们的尸体上的任何钱财或饰品而闻名。 好生意, 而且不乏探险者, 所以没人介意。 但他们在一个船长那里遇到了麻烦, 所以他不得不带着他的船员加入公司。 我们把他拴在皮带上, 只在需要快速简单地解决问题时才放他出去。 ";
			link.l1 = "我怀疑我能和这样的人谈判。 ";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "那是肯定的。 如果他和他的人现在掌权, 联盟很快就会变成另一个团伙。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "我们进行了一次有趣的谈话。 ";
			link.l1 = "我想知道有多少是真的... 贝洛港的屠杀呢? 如果他没有撒谎, 这意味着上次你和我说话时, 你又一次从你杰出的传记中省略了几个重要的事实。 ";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "贝洛港很热, 船长。 我为我的生命而战, 为雇主的生命而战, 为我妻子的生命而战。 我没有时间数死者, 也没有时间为每个在街上错误时间出现的农民哀悼。 ";
			link.l1 = "按这个优先顺序? ";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "不, 当然不是。 她优先。 总是。 ";
			link.l1 = "你觉得呢? 我们该去加拉加斯吗? ";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "我个人不会去, 船长。 我也建议你不要去。 对联盟来说, 你不再是敌人, 至少在我为你服务期间, 他们对我不感兴趣。 此外, 我内心有这种不祥的感觉\n如果我们去那里会很糟糕。 非常糟糕。 这个故事没有幸福的结局。 但我会一直跟着你, 船长。 ";
			link.l1 = "我会考虑的。 ";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "顺便说一句, 你是对的 --他们没有很好地清理矿场。 看。 ";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "一本军官日志... 加密了, 但这是一个旧密码, 我知道\n似乎没什么有趣的。 这是我们囚犯的日志。 现在清楚了为什么他这么愿意说话。 看这里 --隐藏宝藏的迹象! 那个混蛋显然计划退休, 并准备随时溜走! ";
			link.l1 = "这个隐藏的地方在哪里? ";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "你知道那个岛, 船长。 在它的水域里, 你解决了范.伯德。 ";
			link.l1 = "好吧, 不远, 我们去看看。 至于加拉加斯, 我还没决定, 但我想我们有一个月的时间。 ";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "如你所愿, 船长。 我会一直跟着你。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "完成了, 船长。 奥斯汀目前在加拉加斯; 我想我们有一个月的时间。 ";
			link.l1 = "首先。 囚犯说了什么? 这个奥斯汀是谁? 我们为什么要去加拉加斯? ";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "奥斯汀的团伙以引诱自由船长进入荒野, 将他们砍碎, 并彻底剥夺他们的尸体上的任何钱财或饰品而闻名。 好生意, 而且不乏探险者, 所以没人介意。 但他们在一个船长那里遇到了麻烦, 所以他不得不带着他的船员加入公司。 我们把他拴在皮带上, 只在需要快速简单地解决问题时才放他出去。 ";
			link.l1 = "我怀疑我能和这样的人谈判。 ";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "那是肯定的。 如果他和他的人现在掌权, 联盟很快就会变成另一个团伙。 但我不会去加拉加斯, 船长。 ";
			link.l1 = "认真的? 你害怕了? ";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "不是这样的, 船长。 囚犯在伤重不治前透露, 你不再是联盟的敌人, 至少在我为你服务期间, 他们对我不感兴趣。 联盟似乎有了新的有影响力的赞助人, 命令放过我们\n而加拉加斯... 我内心有这种不祥的感觉... 如果我们去那里会很糟糕。 非常糟糕。 这个故事没有幸福的结局。 但我会一直跟着你, 船长。 ";
			link.l1 = "我会考虑的。 当然, 我想一劳永逸地解决这个故事, 但也许你是对的。 我怀疑在过去一周的事件之后, 他们不敢再接近我们了。 ";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "顺便说一句, 你是对的 --他们没有很好地清理矿场。 看。 ";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "一本军官日志... 加密了, 但这是一个旧密码, 我知道\n似乎没什么有趣的。 这是我们囚犯的日志。 看这里 --隐藏宝藏的迹象! 那个混蛋显然计划退休, 并准备随时溜走! ";
			link.l1 = "这个隐藏的地方在哪里? ";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "你知道那个岛, 船长。 在它的水域里, 你解决了范.伯德。 ";
			link.l1 = "好吧, 不远, 我们去看看。 至于加拉加斯, 我还没决定, 但我想我们有一个月的时间。 ";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "如你所愿, 船长。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "等等, 船长。 我一个人去那里。 ";
			link.l1 = "为什么? 现在感觉英勇了? 太晚了; 你制造了这个烂摊子, 但我们必须一起清理。 ";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "你不需要为我的错误付出代价, 船长。 你说得对 --无论我走到哪里, 人们都会死去, 无辜的血流成河。 如果我们一起进入那座教堂, 这将是另一个贝洛港, 我不想要那样。 ";
			link.l1 = "那里到底发生了什么? ";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "一场屠杀。 我想退休, 船长。 我想拿着黄金, 我的妻子, 回家到卡尔卡松。 我知道联盟会派更多的人来完成我的工作, 并从我新的赞助人那里拿到了一笔慷慨的预付款。 然后剩下的就是让城市卫兵对抗我以前的同伙和新雇主。 在所有的混乱中, 我要带着钱消失, 如果时间允许, 也许还会抢劫贝洛港的几个肥猫。 ";
			link.l1 = "好计划, 虽然我会用不同的方式做。 太多事情可能出错。 ";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "我自己也不是天使, 但你的方法甚至让我不寒而栗。 我很惊讶你还没有背叛我, 就像你背叛联盟。 那个绅士, 甚至你自己的妻子一样。 ";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "所有可能出错的事情都出错了。 向总督府发射三磅炮是一个错误。 它几乎没有伤到总督本人, 但我听说他美丽的女儿为了保命不得不双腿膝盖以下截肢。 反应是可怕的 --一场血洗; 很多人丧生, 船长。 现在你看到的是这些事件的最后一个活着的证人, 不久前, 你自己也砍倒了另一个。 ";
			link.l1 = "解释一下。 ";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "如果唐扎格夫人还活着, 我会毫不犹豫地背叛你, 船长。 我是一个活死人, 跟着你是因为我在这个世界上没有其他地方可去。 现在你看到的是这些事件的最后一个活着的证人, 不久前, 你自己也砍倒了另一个。 ";
			link.l1 = "解释一下。 ";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "原谅我, 船长, 在路上没有告诉你一切。 我们第一次见面时, 我以为你只是另一个像我一样的卑鄙小人。 你知道我做的第一件事是什么吗? 我派你去为我收拾残局 --去杀那个我一开始不想杀然后决定背叛的西班牙唐。 那个idalgo, 罗德里格斯... ";
			link.l1 = "你要他的手指做什么? ";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "那里没有诡计。 只是一个测试, 船长。 我们每年招募数十名像你这样的年轻无赖。 只有少数人通过了基本的诚实检查, 即使是他们也在第一次行动中死亡。 你本不应该在弗利特伍德日志的行动中幸存下来。 我本来打算简单地进入房子, 解决幸存者, 拿走日志。 ";
			link.l1 = "如果我没记错的话, 故事的发展略有不同。 ";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "确实如此, 船长。 我不知道是什么促使我帮助你, 但你如此热情地与狐狸战斗, 甚至让我也感染了, 即使只是短暂的。 最后, 在不知不觉中, 你救了我。 你不欠我什么, 船长。 我不会让你进去的。 这是我的事, 我的救赎。 ";
			link.l1 = "如你所愿, 赫丘勒。 失去这样的战士很痛苦, 但你很久以前就失去了自己, 你不值得更多的流血。 你也不欠我什么, 我希望你在那个小教堂里找到救赎。 ";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "说得好, 赫丘勒。 去地狱吧! 如果你没注意到, 你的问题最近变成了我的问题。 你是我的军官, 只有我会决定你是否值得宽恕。 所以你得和我们多待一段时间, 作为我船员的一部分, 用勇气赢得你的救赎! ";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "谢谢你所做的一切, 船长。 再见! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "是, 是, 船长! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "我这辈子见过很多混蛋, 船长, 但第一次我感到内心一阵恐惧。 你觉得: 如果一个较小的怪物杀死了一个较大的怪物, 这算救赎吗? ";
			link.l1 = "他们用水稀释朗姆酒吗? 等你想明白告诉我。 我们走, 我们在这里结束了。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}