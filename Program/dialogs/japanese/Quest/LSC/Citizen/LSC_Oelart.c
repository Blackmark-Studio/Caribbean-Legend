// Оеларт Котеел - канонир
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
				dialog.text = "俺の前から消えろ、旦那。無実の者を襲うような奴に話すことは何もねえ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう、旦那！この天気、どう思う？";
				link.l1 = TimeGreeting()+"…外洋での嵐以外なら、どんな天気でも好きだよ…";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"「おう、何か用か？」";
				link.l1 = LinkRandPhrase("ごきげんよう、旦那。最近のニュースは何かあるかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけさ。ごきげんよう、旦那！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "ハハッ！俺も同じ気持ちだぜ。あんたを見るのは初めてだな……俺の名はオエラルト・コティール。オランダの戦列艦で砲術長をやってたんだ。";
			link.l1 = ""+GetFullName(pchar)+"。俺はここに来たばかりの新参者だ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "俺も新入りさ、ここに来てまだ一年も経ってねえんだ――正直、これ以上長居したくねえけど、みんなはそうじゃないって言い聞かせてくるんだよな。会えてよかったぜ！";
			link.l1 = "「こちらこそ、お会いできて嬉しいです」 "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("ごきげんよう、旦那。最近の噂はどうだい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
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
				link.l2 = "島を出たいのか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "この島がどうやってできたか、何か知ってるか？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "「クランの船に行ったことはあるか？」";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "ありきたりな話さ。俺たちはイギリスのスクーナーと戦って、もう少しで勝てそうだったんだ。奴らは逃げて、 俺たちは追いかけた。一日が過ぎて、あと少しで捕まえられるところだったが、奴らにメインマストを撃ち落とされて、 結局逃げられちまった。\nその後、強い嵐で沈みかけて、さらに潮流に巻き込まれ、最後には船が外輪の近くの礁に打ち上げられたんだ。 生き残れた者はほんのわずかだった……";
			link.l1 = "悲しい……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "それが俺の夢なんだよ。ここがどれだけ退屈か、あんたには想像もできねえだろう。でも、 どうやって出ていけばいいんだ？全然わからねえ。\nここには浮かんでる船なんて一隻もねえし、新しいのを作るチャンスもない――それに、ロングボートで出て行こうなんて自殺行為だ。あんな小さな船じゃ、嵐に粉々にされちまうさ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "この島で見た中で一番古い難破船は百年ほど前のものだが、外周を見れば島自体はもっと古い可能性が十分にある。 外輪は上から下まで船でできていて、水面下の深いところには本当に古代の船が沈んでいるかもしれない、 数尋も視界の外にね。\n島の成り立ちについてだが……潮流や嵐が漂流船をここへ運び込むので、人工の浅瀬が作られたのだと思う。その上に外輪が築かれたんだ。\n俺たちが住んでいる内側の船は……最初にここに来たものか、あるいは何らかの方法で外輪をすり抜けてきたのかもしれない。実際、 提督とその海賊たちもブリッグで俺たちのところまでたどり着いたんだから、十分あり得る話さ。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "俺はリバドスの領地でプロテクターとベラスコに会ったことがある。ブラック・エディが昔、 船の大砲について相談したいって言ってきたんだ――理由は聞くなよ、あいつは何も教えてくれなかった。だから黒人の一人が俺を見つけて合言葉を教えてくれたんだ。\n見張りは手強いから、合言葉なしで通ろうなんて考えるなよ。";
			link.l1 = "覚えておくぜ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("旦那、何を……あっ！俺を盗もうとしてるのか！やめろ！", "俺が背を向けた途端に盗もうとするとは！？よくもそんなことを！", "俺のシーチェストから手を離せ、この泥棒め！");
			link.l1 = "くそっ……";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「何だと！？俺の宝箱を荒らすつもりか？そうはさせねえぞ！」";
			link.l1 = "くそ女め！";
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
			dialog.text = LinkRandPhrase("旦那、どうか武器をしまってください。あなたがそうしていると落ち着かないんです。", "刃物を振り回すなよ、自分がケガするかもしれねえぞ。", "無実の人々の周りを剣を振り回して走り回るのは、あんたが思ってるほど立派なことじゃねえぜ、旦那。しまいな。");
			link.l1 = LinkRandPhrase("いいだろう。", "わかった。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、どうか武器をしまってくれ。あんたのせいで落ち着かねえんだ。", "刃物を振り回して走り回るんじゃねえ、自分がケガするかもしれねえぞ。");
				link.l1 = LinkRandPhrase("いいだろう。", "わかった。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、どうか武器をしまってくれ。あんたがそうしてると落ち着かないんだ。", "刃物を持って走り回るなよ、自分がケガするかもしれねえぞ。");
				link.l1 = RandPhraseSimple("すまねえ。", "俺が片付けておくぜ。");
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
