// Лайонел Маскетт - мещанин
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
				dialog.text = "俺はお前と話したくねえ。お前は何の理由もなく穏やかな奴らを襲って、争いを煽るじゃねえか。どっか行け！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"……お前はここに来たばかりか？";
				link.l1 = TimeGreeting()+"。私の名は "+GetFullName(pchar)+" - そうだ、俺だ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+", "+TimeGreeting()+"。何か用か？";
				link.l1 = LinkRandPhrase("俺に面白い話でもあるのか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか様子を見に来ただけだ。じゃあな。";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "俺の名はライオネルだ。よろしくな。どうやってここに来たんだ？";
			link.l1 = "バーク船でな……ここに密輸業者の入り江があるって聞いて、探しに来たんだ……まあ、俺のバーク船は沈んじまって、今ここにいるってわけさ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "本当に人々はこの島を密輸業者の隠れ家だと思っているのか？";
			link.l1 = "正式には違う。大半の奴らはお前の存在すら信じちゃいねえんだ。";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "なぜ彼らがそうする必要があるんだ？ここはどの地図にも載ってねえ。ここからは出られないんだよ。\n地元の連中は、昔この島がキューバと交易してたって言うが、俺はそんなの覚えちゃいねえし、 もう八年近くここに住んでるんだぜ。";
			link.l1 = "なるほど。あなたと話せて楽しかったです。さようなら。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("俺に面白い話でもあるのか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いているぞ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "本土へ行って出ていきたいかい？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここ、正義の島で人々は何をしているんだ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "ここではどこで物を手に入れるんだ？食い物や服、酒なんかは？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "それは奇妙な話だな。このカリブで俺が知っているのは正義の島だけさ。イングランドでは運が悪くてな、 新世界行きの商船に乗ることにしたんだ。ベリーズで仕事を探すつもりだった――港長の事務員とか、そんな感じでな。だが、結局ベリーズには辿り着けなかった。\n俺は船乗りじゃないから詳しいことは分からないが、嵐が急にやってきて、俺たちは礁に打ち上げられたんだ。 あのひどい衝撃と叫び声は、一生忘れられねえ……\n誰かが「船体に穴が開いたぞ！」と叫んで、みんな海に飛び込んでいった。俺は……泳げねえから残った。皮肉なことに、それが命拾いになったんだ。船は持ちこたえて、夜明けには嵐も収まっていた。\n船を離れる前に食料を持ち出し、筏を作って、穏やかな海を漕いで外輪までたどり着いた。そうやって生き延びたんだ――乗組員の中で生き残ったのは俺だけさ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "ここに来て最初の二年間は、それが俺の夢だったんだ。でも今は……本当にこの島は他のどこよりも悪い場所なのか？緑の野原も木々もないが、壮大な海と星で満ちた夜空がある。 食べ物も十分だし、まともな服も着ている――イングランドで暮らしていた頃よりもずっといい。友達もたくさんできた……\nいや、旦那、俺はここを出たくない。外に俺に何がある？週に三百ペソで気難しい上司の下で机仕事か？嫌だね、旦那！ 俺が探していたものは全部ここで見つかった。他には何もいらないさ。";
			link.l1 = "そうか。よかったな！";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "好きなようにしているさ。ナーワルとリバドスは戦争をしている。海賊たちは食料を売る。 アクセル・ヨーストは沈没船の残骸を売買している。サンチョ・カルペンテロは酒を出して人々を楽しませる。 ジュリアン修道士は祈り、ミサを執り行い、薬を売っている。ローダーデールとソルデッラは互いに策を巡らせている。 アボットは日向で偉そうに歩くのが好きだ。ジリアンとタネケは本当の愛を夢見ているんだ……\n";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "難破船からだよ、旦那、難破船からさ。外輪の壊れた船を漁るのは、島民の大好きな暇つぶしなんだ。 あそこには何でもあるぜ――武器、薬、香辛料にラム酒までな。まだ誰も手を付けてない難破船も多いし、 潮の流れが新しい犠牲者を絶えず運んでくるんだ……";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("俺の物に触るんじゃねえ、泥棒め！", "ちょっと目を離した隙に俺を盗もうとするとはな！？思い知らせてやるぜ！", "俺の宝箱を荒らしやがって！？ただじゃ済まさねえぞ！");
			link.l1 = "黙れ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の物に無断で触るとは何様だ！誰か、助けてくれ！泥棒だ！";
			link.l1 = "黙れ！";
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
			dialog.text = LinkRandPhrase("武器をしまってくれ、友よ。そいつを見ると落ち着かねえんだ。", "ここではな、刃物を振り回すのは許されねえんだ。しまいな。", "聞けよ、正義の味方ぶって剣を振り回すな。そんなのはお前に似合わねえ、しまっとけ…");
			link.l1 = LinkRandPhrase("いいだろう。", "わかった。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞いてくれ、俺はこの島の住人だ。だから剣を下ろしてくれ。", "聞いてくれ、俺はこの島の住人だ。だから剣を下ろしてくれ。");
				link.l1 = LinkRandPhrase("いいだろう。", "ああ、いいぜ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "気をつけろよ、友よ。武器を持ってうろつかれると……俺は落ち着かねえんだ。", "武器を持ったままうろつく男は好きじゃないんだ。怖いからさ。");
				link.l1 = RandPhraseSimple("すまない。", "俺が片付けておくぜ。");
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
