// Вильям Патерсон
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
			dialog.text = "你有啥事吗? ";
			link.l1 = "没有, 什么都没有。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "你好, 先生。该死, 原来惹出这儿一堆兵乱的就是你? ! ";
			link.l1 = TimeGreeting()+", 先生。没错, 是我的船靠岸的。到底怎么了? 你是谁? 我猜你是个英国佬? ";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "先生, 俺是个苏格兰人。英格兰海军的船长, William Paterson, 这位是俺的副手兼得力助手, Archibald Calhoun。事情是这样的, 丛林里有座西班牙人的要塞。俺的任务就是把那帮该死的杂种从要塞里赶出去, 他们把要塞建得离英格兰领地太近了, 简直找死。\n最近俺们试图强攻, 但那帮杂种死伤惨重还死撑着没让俺们得手。俺只好去找援军, 然后…… ";
			link.l1 = "现在已经不需要这样了。你的烂摊子我都收拾干净了, 丛林要塞已经空无一人。西班牙指挥官Diego de Montoya死了, 他的舰队也全军覆没。";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "这算什么私自执法? 你在英属领地上发动这种军事行动, 动机何在? ";
			link.l1 = "我得提醒你一下, Paterson船长, 这里可不是伯利兹。什么英属领地? 这一切闹剧都是Don Diego de Montoya自作主张袭击俺和俺的船才引起的。";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "咳咳…… 那Don Diego为啥要袭击你啊, 船长? ";
			link.l1 = "他和我有着多年的仇怨……  自从他率领的中队袭击了圣皮埃尔, 结果没多久就在老子的亲手参与下被全歼, 那天起就结下了梁子。";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "见鬼! 俺还指望那老家伙活着呢! 俺正想问问他, 为什么要在丛林里建军营。这事儿肯定不是没原因的…… ";
			link.l1 = "很抱歉, 他现在什么都不能告诉你。不过, 堡垒里可能还有受伤的驻军士兵。他们有可能会开口吗? ";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "士兵们…… 唉, 这些死脑筋的家伙有啥用! …… Don Diego的尸体呢? 他身上可能带着重要文件! ";
			link.l1 = "我把Don Diego扔在了军械堡的地上。如果你那么需要他, 就去那儿找吧。我看他也跑不了。";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "呃…… 谁让你多管闲事的…… 你已经够让我头疼了…… ";
			link.l1 = "船长, 我真不明白您为何要责备我。我已经替您完成了任务, 让自己的人上了战场, 连自己的命都豁出去了, 可您还是不满意。现在您只需要把任务完成的消息和您的所有事务报告给皇家港就行了。您的功劳我绝不会抢, 您尽管放心。";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "邀功? 你说什么荣耀? ! 你根本不懂…… 唉, 算了。告辞了, 先生。";
			link.l1 = "也祝你一切顺利! ";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "伙计, 传言没错, 你还真像猫一样有九条命! "+TimeGreeting()+", de Maure先生。您看起来气色不太好…… ";
			link.l1 = TimeGreeting()+", Paterson先生。不得不说, 你和你那位Archibald朋友演得真像, 老子还真被你们骗了, 去你们的! 老子一点苗头都没看出来…… ";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "嘿, 别在圣地门前口出狂言。你没料到吧? 受宠若惊啊—连群岛上最有名的阴谋家都被我耍了。日记的主意是不是很妙? \n我得把你引到这种没人注意的地方, 要是当众杀了你可就闹大了, 毕竟你可是Philippe de Poincy的密友, 对吧? 现在你就要悄无声息地消失了, 没人会知道发生了什么。";
			link.l1 = "所以, Calhoun跟我说的那些…… 全都是谎言? ";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "一点也不。俺确实是在这儿找到可怜的Archibald的。不过他可没写什么回忆录, 你在他房间里发现的那本日记, 是俺特意让他为你写的, 蒙森尼尔 de Maure。\n自从咱们在卡多切角见面后, 俺就一直盯着你。是你从don Diego的尸体上拿走了“两重现身”的地图吧? 别否认, 俺知道就是你。";
			link.l1 = "你也知道真理守护者? ";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "这问题真蠢。老子当然知道。老子还知道你身上带着酋长之爪。很快你就得把那些不属于你的东西还回来。";
			link.l1 = "很高兴你不像Don Diego那样婆婆妈妈。我欣赏坦率和直接。据我所知, 指路之箭—那个罗盘就在你手上? ";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "哈哈哈! 好吧, 老子就坦白到底…… 阁下, 你真以为老子像你和Don Diego那样蠢, 会随身带着那么贵重的东西? 那罗盘在牙买加, 甚至不在皇家港, 而是在一个谁都想不到的地方, 还锁得死死的。不过你也用不着知道这些了。";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "照我理解, Paterson先生, 您已经把我当死人埋了? 老子还敢说, 猫都还有一条命在呢! …… 我的副官们呢? ";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "照我所知, 你已经把我埋了, Paterson先生? 老子还敢说, 猫还有一条命呢! ";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "怎么, 船长, 担心你的女人了? 你那娘们儿正躺在那边灌木丛里, 脑门上开了个洞。她已经给你铺好路了, 你很快就会去陪她。啧啧, 这么漂亮的姑娘! 希望你至少上过她不止一次吧? ";
				link.l1 = "这狗娘养的! 你个王八蛋, 老子要让你付出代价! ";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "您的副官们已经为您铺好了路, de Maure先生。他们就躺在那边的灌木丛里。很快您也会去陪他们的。";
				link.l1 = "咱们走着瞧! ";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "我们会让这真成你的最后一次。";
			link.l1 = "那可未必! ";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "你真逗。一个人对抗一整队! 好了, 废话少说…… 举枪! 开火! ";
			link.l1 = "…… ";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
