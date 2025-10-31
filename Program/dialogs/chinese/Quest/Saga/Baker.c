// 雷蒙德.贝克 - 圣约翰的刽子手及潜在军官
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
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "谢谢你, 船长! 我甚至无法想象没有你我会怎么样... ";
			link.l1 = "我能想象。 你会饿死, 或者被多米尼加的野蛮人吃掉。 但你有机会报答我。 ";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "我能帮你什么, 船长? ";
			link.l1 = "我想了解一个人。 可以说是我们的共同朋友, 实际上是你非常亲近的朋友。 我是说屠夫船长。 对, 就是你二十年前绞死的那个。 主啊, 你为什么脸色这么苍白? 想喝口朗姆酒吗? ";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "你... 是他派来的吗? ";
			link.l1 = "胡说! 他都死了我怎么会被‘他’派来! 比起屠夫本人, 我对他留下的东西更感兴趣。 信件。 文件之类的。 也许你在他口袋里发现了什么... 等等! 我不明白。 你真的认为屠夫还活着吗? 是你亲自处决了他! ";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "该死! 你什么都不知道。 这意味着你不像我想的那样是屠夫派来的... ";
			link.l1 = "嗯, 嗯。 这越来越有趣了。 看来亨利害怕屠夫是有充分理由的, 所以才会心脏病发作去世... 屠夫还活着吗? ";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "他还活着, 船长... 而且他们在找我。 ";
			link.l1 = "雷蒙德, 他们说你不是个傻瓜。 别跟我玩花样。 你在这里很安全, 没有任何威胁。 告诉我你知道的一切, 我会想办法帮你。 也许我们有共同的敌人。 先从屠夫开始吧。 ";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "他还活着, 但现在换了个名字! 处决当晚, 他的人来拜访了我。 杰克曼和另一个有奇怪绰号的人。 我记得好像是‘溺水者’。 ";
			link.l1 = "刽子手。 亨利刽子手。 ";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "对! 他们给了我一个简单的交易 —要么痛苦地死去, 要么救他们的船长。 所以我不得不用业余时间制作的特殊设备伪造了处决。 你看, 这种皮带和夹子的构造可以分配身体的重量。 \n我只需要把它和绳圈里的秘密钩子连接起来。 不过‘尸体’得好好扮演角色。 不得不说劳伦斯的表演非常逼真, 他做得很对, 只是拒绝尿裤子, 因为... ";
			link.l1 = "你刚才叫屠夫‘劳伦斯’? ";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "那是他的真名。 我告诉过你他叫劳伦斯.贝尔特罗普。 自从一年前他回到加勒比海, 我就一直坐立不安。 当我发现一些坏人在找我时... \n我甚至给当局写了一份忏悔书, 以防万一。 我一直带在身上, 因为不敢交出去。 他们可能会认为我是自愿帮凶。 请让我留在你的船员中。 我发誓, 我是个优秀的医生, 可以帮你很多忙。 ";
			link.l1 = "好的。 那屠夫... 呃, 贝尔特罗普的个人物品呢? 他和托马斯.贝尔特罗普有关系吗? ";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "不知道。 贝尔特罗普本人没留下什么特别的东西。 但我会把我所有的都给你, 你可以随意处理。 所有相关文件都在我的包里。 我以防万一保存了所有东西, 一直带在身边。 \n看... 这是屠夫船长的传说, 这是我的忏悔书... 这些是属于约书亚.利德比特的东西... ";
			link.l1 = "等等! 利德比特? 那是谁? ";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "哦! 他是个很特别的人。 是他亲自追捕屠夫。 人们记得他是‘蒙面人’。 屠夫被处决后不久他就被谋杀了。 有人用鲨鱼牙割开了他的喉咙! 一刀就完事了。 他活着的时候一定受了很多苦。 \n如果你见过他面具下的脸, 那简直就是一团肉! 他死的时候口袋里有这页日记。 一定是杰西卡.罗斯的笔迹。 故事很诡异! 读一下, 会让事情更清楚。 \n这就是那颗牙齿本身。 你能看到字母吗? S.D... 。 不管是什么意思。 还有一些血迹。 ";
			link.l1 = "够了! 我需要仔细阅读所有内容并思考。 在我处理这一切之前, 你将是我的乘客或船医。 你可以放心, 雷蒙德, 在我的船上你很安全。 ";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // 贝克的证词
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// 加入军官
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; // 不要试图离开
			npchar.CompanionDisable = true; // 不能加入伙伴
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> --------------------------------- —军官模块 ------------------------------------------
		case "Baker_officer":
			dialog.text = "什么事, 船长? ";
			Link.l1 = "听我的命令! ";
            Link.l1.go = "stay_follow";
			
			////////////////////////军需官///////////////////////////////////////////////////////////
           	// boal 船舶报告
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "雷蒙德, 给我一份完整的船舶报告。 ";
			    Link.l11.go = "QMASTER_1";

			    // 战舰。 自动购买货物
				Link.l12 = "我希望你每次靠港时购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "没什么。 解散! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// 军需官响应 ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "得了吧, 船长, 我是医生, 不是事务长。 虽然过去我做过不同的工作... 没关系。 我真的不做会计, 抱歉。 ";
			Link.l1 = "好吧, 就这样。 你是我的医生 —正如你加入船员时我们约定的。 ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "船长, 说实话, 我在贸易方面没什么经验。 从没讨价还价过, 也没跟踪过价格标签。 另外... 如果你不介意, 我宁愿待在船上。 有些商人可能会认出我, 然后很快就会有蒙面人出现。 ";
			link.l1 = "所以, 你会继续活在过去的恐惧中... 好吧, 放心, 我自己来做。 ";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "命令? ";
            Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟着我, 跟上! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "为你的火器更换弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
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
            dialog.Text = "部署已变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "部署已变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
        break;
	//< —--------------------------------- —军官模块 ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}