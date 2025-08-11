// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要啥? ";
			link.l1 = "没有, 什么都没有。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "欢迎您来到殖民地, 先生! 请允许我自我介绍: "+GetFullName(npchar)+"。你是从老家来的? ";
			link.l1 = "日安, 先生。鄙人名叫"+GetFullName(pchar)+"。是的, 我刚下船。";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "看到一位绅士, 我觉得应该帮把手。 新世界有自己的规则, 不懂规则可能会付出代价。 上流社会的人应该互相扶持。 这里有很多无赖, 为了几个硬币就会出卖你\n"+
			"我可以带您四处看看, 介绍一下基础设施吗? ";
			link.l1 = "您太客气了, 先生! 我很乐意。 ";
			link.l1.go = "guide_2";
			link.l2 = "谢谢您, 先生, 但我想自己探索。 ";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "如您所愿, 先生。无论如何, 很高兴见到您。像您这样高贵的绅士在这里可不常见。祝您一切顺利! ";
			link.l1 = "也祝你一切顺利, "+GetFullName(npchar)+"! ";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "太好了! 加勒比城镇布局都差不多。 了解圣皮埃尔, 其他港口也就明白了。 ";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "酒馆—港口的中心地带。能找床位、喝朗姆酒、打听八卦, 还能雇水手或军官。你可以打牌、接活儿, 或者和走私贩、藏宝图商人打交道。";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "市场。 需要补给吗? 铁匠有刀剑。 盔甲和炮弹; 草药女售卖药剂。 吉普赛人和修士交易护身符, 旧货商为会手工制作的人提供零碎物品。 ";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "妓院。没什么比和技艺高超的姑娘共度时光更能提振精神了。如果你精力不济, 就进去转转, 出来保准焕然一新。";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "银行。可以借钱、投资, 也能把比索换成达布隆, 这里还是卖珠宝的最佳地点。";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "监狱。 里面没多少真正的恶棍 —大多是流浪者。 想从他们那里接工作? 和指挥官谈谈; 给点小费就能打开牢房。 ";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "总督府。商人和船长们都来这里谈正经生意。务必与总督保持友好—他的一句话就能决定这个国家如何对待你。";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "我耽误你时间了吗, 朋友? ";
			link.l1 = "先生, 我是来找我哥哥的。听说他在圣皮埃尔, 是个有头有脸的人物—总督肯定认识他……";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "啊, 明白了。我们的总督是Jacques Dyel du Parquet。我相信他很快就会接见您。";
			link.l1 = "我还能问谁? 我可不想立刻去打扰总督大人。";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "如果你哥哥在Martinique很有名, 去问问镇上的人—总有人知道。他叫什么名字? ";
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "我听说过这个名字, 虽然咱们没见过。你可以打听一下—或者直接去找总督。祝你好运, 先生。咱们以后再聊! ";
			link.l1 = "谢谢你, "+GetFullName(npchar)+"! ";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "啊, 又是你! 听说你闯进了骑士团的堡垒, 看来你现在可是在上流圈子混呢。你找到你哥哥了吗? ";
			link.l1 = "算是……找到了。";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "请原谅, 不过我听不出你这回答里有多少喜悦……";
			link.l1 = "没错。我本来希望能搭下艘船回家, 可命运偏偏捉弄我。现在被困在这儿—谁知道要多久—更糟的是, 还得学着当个水手。";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "我并不意外。你乘坐Ulysses号的消息已经传开了。别灰心—拥有一艘船和船长的头衔可不是小事。你打算买艘船, 对吧? ";
			link.l1 = "是啊—该死—老子得去。但老子连船坞在哪儿都不知道, 更别说怎么开船、怎么弄钱了。啥都不懂! ";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "钱是没有, 不过其他方面我都乐意效劳。我们要继续参观吗? ";
			link.l1 = "你说得对—知识就是力量。";
			link.l1.go = "guide_25";
			link.l2 = "谢谢您, 先生, 接下来我自己可以应付。";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
            dialog.text = "乐意效劳。 想筹集资金, 和镇上的关键人物谈谈 —也许是商店商人\n" + "祝您好运, "+pchar.name+" —勇敢些, 您会成功的。";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "那就跟我来! 首先—得说说船的事。";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "船厂。在这里可以买船或修船。大多是小型船体, 不过偶尔也能遇到好货。还有火炮和花哨的帆。";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "码头—通往大海的大门。等你有了自己的船, 船就会在这里等你。现在嘛, 先雇个领航员、管账的和炮手吧—有了他们, 出海的日子会轻松不少。";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "港口事务所。把你的船停在这儿, 或者接点正经活—运货、护航、送信。活儿干得越多, 报酬越高。";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "商店。船长们来这儿买粮食、朗姆酒、药品、火药和弹药。要是缺货, 就去酒馆找走私贩。没有个靠谱的管货官, 做买卖只会浪费时间和钱。";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "通往荒野的大门。虽危险, 却能通往要塞、寻宝, 或穿越到其他定居点。";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "不是每个殖民地都欢迎陌生人。如果你不想等到天黑, 就在海上换面旗子, 然后靠潜行混进去—或者花钱买个贸易许可证。";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "你听好了, 伙计。想找点乐子吗? 城门外来场练习决斗如何。";
			link.l1 = "当然! 听起来再好不过了。";
			link.l1.go = "guide_47";
			link.l2 = "谢谢您, 先生, 接下来就交给我吧。";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "朋友, 看你这身手, 想必不是头一次玩剑吧? ";
			link.l1 = "哈! 老子都经历过一次登船战了, 甚至还—";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "太好了。我们走吧? ";
			link.l1 = "来跳一曲吧! ";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "你……你确实懂得如何握剑。干得漂亮, 先生。你还需要多加练习, 但你有成为真正剑术大师的潜力。";
			link.l1 = "多谢。那么接下来呢? ";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "你还说要多练习? 你是认真的? 自从老子踏进这个鬼地方, 你就一直用这种高高在上的口气, 老子早就受够了! ";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "好多了! 你看, 只要专心就行。你还需要多练练, 总有一天会成为像样的剑客。";
			link.l1 = "多谢。那么接下来呢? ";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "我赢了, 先生。动作快点, 挡住我的突刺, 再往后跳。要不要再来一局? ";
			link.l1 = "好! 毫不留情, 先生!";
			link.l1.go = "guide_56";
			link.l2 = "不行, 老子受够了。咱们把这课上完吧。现在怎么办? ";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "我又赢了, "+pchar.name+"! 别丢了你的主动权。接住我的攻击, 虚晃一下。如果看到我要狠劈了—赶紧闪开或者格挡, 别光顾着防守。再来! ";
			link.l1 = "来吧, 先生, 这次我一定要好好教训你! ";
			link.l1.go = "guide_56";
			link.l2 = "不行, 老子受够了。咱们把这课上完吧。接下来干啥? ";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "你还有很多要学的, "+pchar.name+"。别担心, 你还有大把时间磨练你的剑术。但要小心, 没学会怎么拿武器前, 别冒险。";
			link.l1 = "我会考虑的, 先生, 不过我得说, 你实在太走运了! 这鬼天气……老子就是因为太热才没把你揍趴下。见鬼, 咱们的击剑课就到这儿吧。现在怎么办? ";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "现在该说再见了, 先生。能为您效劳是我的荣幸。希望我的讲解和训练对您有所帮助, 将来能派上用场。或许有一天我们还能再见。\n至于您需要的钱—去和咱们城里的重要人物聊聊吧。把我今天带您去过的所有地方都走一遍, 和那里的主人谈谈。多打听打听。去丛林和要塞转转。找份正经差事, 或者……唔, 我可不是神父也不是法官, 您也可以去别人家里看看, 瞧瞧那些没锁的箱子里有什么小玩意儿。只要趁他们不注意的时候动手, 否则巡逻的卫兵可不会放过您。\n祝您好运, "+pchar.name+", 我有种强烈的预感, 您体内蕴藏着真正伟大的火花。尽力把它燃成熊熊烈焰吧! ";
			link.l1 = "多谢, 先生。荣幸之至。愿上帝保佑您一路顺风! ";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "闭嘴, 先生! 我再也不会容忍你的无礼。不过, 我理解你初来乍到的反应, 这次就原谅你的失态了。但以后注意你的言辞。告辞了, de Maure先生。";
			link.l1 = "无意冒犯, Valinnie先生。如果咱们现在在卢浮宫, 你可得注意你的语气! 现在该给你这个乡下佬上最后一课了。准备好挨打吧! ";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}