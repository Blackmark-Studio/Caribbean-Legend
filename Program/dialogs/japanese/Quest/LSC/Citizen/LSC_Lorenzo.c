// Лоренцо Сольдерра - испанский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "お前みたいな盗賊に言うことは何もねえ。消え失せろ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ふむ、フランス人か？俺たちに話すことなんてねえと思うが。";
				link.l1 = "面白いな、どうして駄目なんだ？この島じゃ国同士の憎しみなんて何の役にも立たないと思うが……";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"「おう、何か用か？」";
				link.l1 = LinkRandPhrase("せめて最近のニュースくらい教えてくれないか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "様子を見に来ただけだ。じゃあな、ロレンツォ。";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "そうは思わん。俺は士官であり紳士だ。エル・エスコリアルの敵とは、ヨーロッパでもカリブでも、この島でも、 どこであろうと馴れ合うつもりはない。自分の道を行け、旦那！";
			link.l1 = "ふうっ。ご自由に……";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
		case "meeting_no":
			dialog.text = "はっきり言ったはずだぜ。俺は自国の敵とは馴れ合わねえ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いているぞ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("「フランスの泥棒め！俺が思い知らせてやるぜ！」", "くそ野郎！俺の背中を向けてる隙に俺の物を盗るとは！？ぶっ殺してやる！", "俺の物を盗もうってのか？いいぜ。ちょうど剣の稽古がしたかったんだ、憎たらしいフランス野郎！");
			link.l1 = "偉そうな旦那！覚悟しろ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "なにっ！？俺の宝箱をあさろうってのか？そうはさせねえぞ！";
			link.l1 = "「愚かな娘め！」";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("フランス野郎、武器はしまっておけよ。じゃねえと、使わせてやることになるぜ……", "その武器で俺を試したいなら、勇気があるってことだな…そうじゃねえなら、しまいな。", "剣を持っていても、お前が高貴でも美形でもねえよ、フランス野郎。しまいな。");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ああ、いいぜ。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "フランス野郎、武器はしまっておけよ、さもねえと使わせてやるかもしれねえぞ……", "その武器で俺を試してみるか？勇気があるならな……そうじゃねえなら、しまいな。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "そんなことしなくていい……しまっておくよ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "フランス野郎、武器はしまっとけよ。じゃねえと、使わせてやるかもしれねえぞ……", "その武器で俺を試してみるか？勇気があるならな……そうじゃねえなら、しまいな。");
				link.l1 = RandPhraseSimple("そんなことしなくていい、俺が片付けるから。", "俺はそれを片付けるぜ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
