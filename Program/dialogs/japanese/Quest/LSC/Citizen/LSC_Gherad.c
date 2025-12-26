// Гхерад Смиитс - матрос
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
				dialog.text = "消え失せろ、相棒。俺は無実の民間人を襲うような奴とは話さねえ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "やあ、相棒、ははっ！ここで何してるんだ？";
				link.l1 = TimeGreeting()+"。ごきげんよう！まだお会いしたことがないと思います。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「やあ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用かい？";
				link.l1 = LinkRandPhrase("おう！何か新しい話はあるか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか気になってな。じゃあ、またな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "ああ、まだ会ったことはなかったよな。でも今はもう知り合いだ！俺の名はヘラルト・スメーツ、 ロッテルダム出身の水夫だ。あんた、見たところ四分士って感じじゃねえか…？\n";
			link.l1 = "そんなところだ。俺の名前は "+GetFullName(pchar)+"。お会いできて嬉しいよ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "実のところ、あんたは船主か会計係に見えるな……間違いなく教養のある男だ。会えて嬉しいぜ！どうやってここに来たんだ？";
			link.l1 = "メキシコ湾を探検することにしたんだ。キューバのバッカニアたちが、このあたりに未踏の島があるって話しててな、 それが本当かどうか自分の目で確かめたかったんだよ。";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "お前が唯一の生き残りか？船はどこで沈んだんだ、外輪か？";
			link.l1 = "確かに俺だけだ。そして俺のバルク船はこの南の海の底さ。外輪にすら届かなかったんだ。";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "ああ。まあ、ここに閉じ込められちまったんだし、サンチョのところに行ってラム酒でももらってこいよ。 悲しみを酒で流すのが、ここでの暮らしの第一歩だぜ、へへ。";
			link.l1 = "ありがとう……じゃあ、またな！";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("よう、スミーツ、何か新しい話はあるか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "ああ、相棒。何でも聞いてくれ！";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "教えてくれ、どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "島を出て、昔の生活に戻りたいのか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「ここの氏族たちに悩まされてるのか？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島はどうやってできたんだ？何か心当たりはあるか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はありません。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "俺はあの偉そうなアボットと一緒にここへ来たんだ。あいつの船で働いてたんだぜ。ああいう奴は船に乗っちゃいけねえ、 絶対に不運を呼ぶからな。悪魔があいつを俺たちのオンボロ船に送り込んだに違いねえよ。\nジャマイカからベリーズまでの航海、楽勝だと思ってた。でも運命は俺たちを見放した。ボースンは海に落ちるし、 航海士は道を誤るし、忌々しいスペイン野郎どもに襲われて、嵐にバラバラにされた。で、気がつきゃここさ。";
			link.l1 = "「なんてこった！」";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "昔はそうだったが…正直に言うとな、相棒、今はわからねえ。ここでの暮らしは悪くねえんだ。ラムやワインはたっぷりあるし、飯もうまい――量は多くねえが、虫食いのビスケットよりはずっとマシさ。\nここにはいい奴らがいて、飲んでしゃべって楽しいぜ。俺はここが気に入ってる。だからな…どうだろうな…いや、やっぱり出て行きたくねえな。昔はいつも腹を立てて腹を空かせてた――今のこの腹を見てみろよ、ははっ！";
			link.l1 = "よかったな！お前が嬉しいなら俺も嬉しいぜ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "いや、そんなことはねえ。ただ、あいつらの縄張りを荒らすなよ、それだけは絶対に許さねえんだ。\nナーワルの連中はいい奴らさ――ほとんどがここで生まれて、他の世界なんて知らねえ。\n腕の立つやつも多いぜ。たとえばユルゲン・シュミット、あいつは鍛冶の神様だ、 まるで生きたヘパイストスみてえなもんさ！";
			link.l1 = "「それは良かった。」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "嵐と暗礁さ、相棒。外側の輪っかは上下ともに船でできてるんだ。 船が嵐に巻き込まれて暗礁や外輪そのものに打ち上げられる。そうやって島が大きくなっていくのさ！\nただ、内側の船がなぜ水面に浮かんでるのかは俺にも分からねえ。たぶん俺たちの足元には浅瀬があって、 それが支えてるんだろうな。";
			link.l1 = "「面白い！」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("おいおい、泥棒め！俺から丸ごと盗れると思ったのか、ああ？", "背を向けたら、どうだ！汚ねえ泥棒が這い寄ってきやがる！", "おい！俺の海のチェストに手を出すんじゃねえ、相棒！");
			link.l1 = "「ああ、くそったれ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の宝箱をあさってるだと！？よくもそんなことをしやがったな！";
			link.l1 = "くそっ……";
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
			dialog.text = LinkRandPhrase("おい、相棒、剣をしまってくれねえか？落ち着かねえんだよ。", "刃物を振り回して走り回ってると誰かに見られるぜ。しまっとけ。", "剣を抜いて騎士気取りなんてやめとけ、まぬけにしか見えねえぞ。しまっとけよ……");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ご希望のままに……", "おっしゃる通り……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞けよ、ここじゃバカが武器振り回して歩くのは許さねえんだ。しまっとけ。", "俺はな、そんなに気軽に刃物を振り回す奴は好きじゃねえ。しまいな。");
				link.l1 = LinkRandPhrase("いいだろう。", "それならそれでいいさ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "おい、相棒、剣をしまってくれねえか？お前のせいで落ち着かねえんだよ。", "俺はあんなに気軽に刃物を振り回す奴が好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。", "俺がこれを持っていくぜ。");
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
