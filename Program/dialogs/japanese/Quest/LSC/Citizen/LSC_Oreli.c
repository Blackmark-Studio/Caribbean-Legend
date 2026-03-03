// Орели Бертин - просто жительница
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
				dialog.text = "俺に構うな、旦那。誰かを傷つけただろう！どっか行け！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう、旦那。";
				link.l1 = TimeGreeting()+"。私の名は "+GetFullName(pchar)+"、俺はここに来たばかりだから、島の連中と知り合いになってるところさ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("ごきげんよう、ベルティーヌ夫人。正義の島では何か新しいことがありましたか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか気になっただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "なるほど。私はオレリー・ベルティーヌ。どうやってここに来たの？";
			link.l1 = "伝説の正義の島を一度見てみたかった、ってところさ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "つまり、自分の意思でここへ来るような物好きの一人ってわけか……まあ、これからたっぷりと島を見て回って、“正義”を存分に味わう時間はあるだろうよ。";
			link.l1 = "その皮肉な言い方からすると、この島の正義のやり方に何か問題が見えるのか？";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "いや、大丈夫だよ――ただ、なぜか最近は食べ物にまで海賊どもへ金を払わなきゃならなくなったんだ。 少し前までは誰でもタダで食えたのによ。しかも、 あいつらのクラン同士の争いがこの正義の島の俺たちの区域に持ち込まれると、 撃たれたり刺されたりしないように船の中に閉じこもってろってさ。\nつまり、あいつらは俺たちの縄張りで好き勝手やれるのに、こっちは向こうの区域で同じことはできねえってわけだ。 でもまあ、いいさ、俺は何の不満もない……全然な……";
			link.l1 = "なるほど……まあ、お会いできて嬉しかったです。それでは、しばらくお別れですね、ベルティーヌ夫人！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "さあ、はっきり言ってくれ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "ここに長く住んでいるのか？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島で何か面白いことはあるか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「この島のクランについて、どう思う？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "海賊たちがあなたを困らせているのか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "とても長い間だ。年数なんてもう数えなくなった……たぶん十七年……いや、十八年か……それとも二十年か？今は何年なんだ？";
			link.l1 = "じゃあ、あんたは古株か？";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "こういうことさ：俺はいまだに覚えてるぜ、キューバから来たバッカニアたちがここで取引してた頃をよ。それに、 一番賢くて向こう見ずなナーワルどもが、本土まで航海して、 沈没船の積み荷から引き上げた品と食い物を交換してたんだ。\nだが今じゃ、正義の島しか知らねえ連中がたくさんいる。ここで生まれたからな。そいつらは古株ってだけじゃなく、 もう立派な島の生まれさ。";
			link.l1 = "面白いな！";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "もちろんさ。正義の島は面白い場所だぜ。自分の目で見て回るといい、沈没船の周りを泳いだり、酒場や店、 それに教会にも行ってみな。\nだがな、その新鮮さも一週間もすれば色あせちまうって約束するぜ。";
			link.l1 = "……わかった……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "何を言ってほしいんだ？俺はあいつらを避けるようにしてるんだ。 少なくともナーワルたちは島のために多少は役立ってる――あいつらの中には腕のいい職人もいるしな――だがリバドスはただの野蛮人で異教徒だ。\nあいつらは何百年も前の祖先と同じようにアフリカの掟で生きてる。まるで獣だ。唯一覚えたのは火器の使い方くらいさ。 リバドスは儀式で人肉を食うって噂もあるぜ！";
			link.l1 = "なんて悪夢だ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "自分たちの食料を自分たちに売りつけるところは気に入らねえが、あいつらは市民には決して危害を加えねえ。むしろ、 クランどもを従わせて、絶え間ない戦争を止めてくれたんだ。\n昔、一人の市民が騒ぎを起こしたことがあった――剣を振り回すのが好きなやつでな。地元の連中二人を傷つけた。 海賊どもはそいつをタルタロスに数週間ぶち込んだんだが、今じゃすっかり大人しくなっちまった。 あまり見かけなくなったが――今じゃ外輪がそいつの新しい住処さ……";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("何をしてやがる、泥棒め！？", "俺が背を向けた途端に俺の箱をあさるのか！？", "俺の箱をあさってやがるな？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "この盗人め！こんなことをしたらタルタロスで朽ち果てるぞ！";
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
			dialog.text = LinkRandPhrase("武器をしまってください、旦那。落ち着かないんだ。", "ここではな、刃物を振り回すのは許されねえんだ。しまいな。", "剣を持ってうろついていたら、海賊どもはきっといい顔しないぜ。俺だって、正直あんまり嬉しくねえしな…");
			link.l1 = LinkRandPhrase("「いいだろう。」", "「いいだろう。」", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまってください、旦那。落ち着かないんだ。", "ここではな、刃物を振り回して歩くのは許されねえんだ。しまいな。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "「いいだろう。」", "おっしゃる通りだ……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまってください、旦那。落ち着かないんだ。", "剣を手に持ってうろついていたら、海賊どもはきっといい顔しないだろうな。俺だって、 正直あまり気分がいいもんじゃねえ……");
				link.l1 = RandPhraseSimple("了解だ。", "俺がそれを持っていく。");
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
