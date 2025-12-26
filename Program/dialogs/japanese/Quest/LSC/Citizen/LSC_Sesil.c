// Сесил Галард - бабулька
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "俺はお前と話したくねえ。お前は何の理由もなく平和な民間人を襲って、わざと争いを起こすじゃねえか。消え失せろ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "何か用かい、若いの？";
				link.l1 = TimeGreeting()+"。自己紹介をさせてもらおう―― "+GetFullName(pchar)+"。私は新参者だ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何かご用かい？";
				link.l1 = LinkRandPhrase("やあ、セシル。最近面白い噂でも聞いたかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか、ちょっと気になってな。\nまたな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "あ、ああ、正義の島とその住人たちを知ろうとしているのか？";
			link.l1 = "まさしくでございますか、奥様？";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "アラール。セシル・アラール。";
			link.l1 = "はじめまして、ハラール夫人！お会いできて光栄です。";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "俺も同じだよ……で、どうやってここに来たんだい、若いの？最近、難破した船なんて覚えがねえが……";
			link.l1 = "俺はスペイン領本土からバーク船で航海してきたんだが、嵐に流されてここに来ちまった…船は島のすぐ近くで沈んじまったんだ。";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "その場合、無事に正義の島までたどり着けたなんて、本当に運が良かったな。嵐はこの島自体にはめったに来ねえが、 周囲の海では突然現れて、どんな頑丈な船でも容赦なく叩きのめすんだ！\nだから、自分は運が良かったと思って、この場所に慣れるんだな。気を悪くさせたくはねえが、ここに来るのは簡単でも、 島を出るのはほとんど不可能だ。過去十年の間に、脱出して生き延びた奴は一人もいねえんだよ。";
			link.l1 = "申し訳ないが、俺はそう簡単に絶望なんかしねえよ。お会いできて嬉しかったぜ、ハラール夫人。また会おうな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "「はい、若者かい？」";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "「それで、どうやってここに来たんですの、奥様？」";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "ここに長いこと住んでいるんだろう？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "この島の住人たちについて何か教えてくれないか？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "ここに住んでいる中で一番面白い奴らは誰だ？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "あれはずいぶん昔のことだから、どうやってそうなったのかほとんど覚えていないんだ。遭難したのは確かだけど、 細かいことは……（肩をすくめる）";
			link.l1 = "ふうん。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "小さい頃からよ。時々、まるでここで生まれたんじゃないかって思うこともある……でも、それは違うの。もちろんね。だけど、きっと私はここで死ぬことになるわ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "あまり言えることはないな、若いの……正義の島にはいろんな奴がいる。白人、黒人、インディアン、逃げてきた奴隷、貴族、国の罪人、水夫……昔はもっとたくさんいたもんだ。みんな自分の物語と癖を持ってる。ここにいられることを喜ぶ奴もいれば、 出ていくことばかり夢見る奴もいる。\nそれに、ナーワルとリバドスという氏族がいて、海賊たちがその均衡を保ってる。この島では、 他のどこにもいないような人間の混ざり合いが見られるし、それなりに平和と調和も保たれてるんだ……";
			link.l1 = "「興味深いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "シュミット旦那、ナーヴァルの機械職人……サンチョ・カルペンテロ、ここの酒場のバーテン……そして今はシャーク・ドドソン提督と、その友人レイトン・デクスターもいるんだ。\nだがな、本当に自分でこういう連中に会ってみるべきだぜ。正義の島の俺たちがどれだけ面白い話を持ってるか、 あんたには想像もつかねえだろうよ。";
			link.l1 = "考えておくよ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("ああ、泥棒！そこで止まれ！", "年寄りの女の背後を狙って盗みを働くとは？よくもそんなことができるな！", "俺の宝箱を荒らすつもりか？そうはさせねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "年寄りの女の背後を狙って盗みを働くとは？よくもそんなことを！！";
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
			dialog.text = LinkRandPhrase("武器をしまいなさい、若いの。見てると落ち着かないんだよ。", "知ってるか、この島で武器を振り回す奴にはろくなことが起きねえんだ。しまっとけ。", "若いの、剣を納めなさい。年寄りの女を怖がらせてどうするのよ！");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ああ。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまいな、若造。そいつを見ると落ち着かねえんだ。", "なあ、この島で武器を振り回してると、ろくなことにならねえぜ。しまっとけ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "ああ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまいなさい、若者。そんなものを持たれると落ち着かないよ。", "若い人、剣を納めておくれ。年寄りの女を死ぬほど怖がらせるつもりかい！");
				link.l1 = RandPhraseSimple("すまねえ。", "俺はしまっておくぜ。");
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
