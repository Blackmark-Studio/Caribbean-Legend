// Дугал Эббот - дворянин
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
				dialog.text = "俺はあんたと話さねえよ、旦那。あんたは何の理由もなく平和な人々を襲うじゃねえか。俺の目の前から消えろ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ご挨拶を、旦那。自己紹介させていただきます、ダグール・アボットと申します。 ここで貴族の方にお会いできて嬉しいです。ここの農民どもは本当に退屈でしてね。 まさか残りの人生をこんな下賤な者たちと共に過ごすことになるとは、夢にも思いませんでした。";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。会えて嬉しいよ。ところで、どうしてここの住民が気に入らないんだ？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何かご用かい？";
				link.l1 = LinkRandPhrase("ダグール！島の様子はどうだ？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "奴らのことは、もっと知ってから判断しな。\nお前、今来たばかりか？新しい難破船の話なんて聞いてねえが……";
			link.l1 = "俺は小さなバーク船でここに来たんだ。あいつは真夜中に突然沈んじまった。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "そういうこともあるさ――船が沈んで、生き残ったわずかな者だけが岸にたどり着くんだ。\n時には、何ヶ月もこの島で暮らしている連中がいるのに、一度も顔を合わせないことだってあるぜ。";
			link.l1 = "なるほど。お会いできてよかったです、アボットさん。さようなら！";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("やあ、Dougall！何か新しいことはあるか？", "この島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いてるぜ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島の住人たちについて何か教えてくれないか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "クランについて何か教えてくれないか？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "天気はどうだい？ここじゃ嵐が多いのかい？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "五年前のことだが、まるで昨日のことのように覚えている。俺はポートロイヤルからベリーズへ、 高価な積荷を満載したフリュート船で出航したんだ。\n翌日から事態が悪化し始めた。まず、俺の甲板長が酔っ払って海に落ちちまった。それから、 危うく暗礁にぶつかりそうになり、さらに航海士が間違えて南じゃなく北へ進路を取っちまった。\nそこへスペインのブリッグとガレオンが現れた。俺たちは逃げ出し、奴らは追ってきた。ガレオンは振り切ったが、 ブリッグには追いつかれた。\nガレオンは遠すぎて小さい仲間を援護できなかったから、俺はすぐさま回頭してブリッグに乗り込むよう命じたんだ。 スペインの野郎どもはまさかの展開に驚いてやがった、へへっ！（ため息）勝ったは勝ったが、 ほとんどの仲間を失っちまった。\nそれから数時間後、嵐がやってきてな。人手が足りなくて乗り切れず、結果は見ての通りだ。 俺のフリュートは外輪のどこかで難破し、今じゃ俺と他の三人の生き残りがここで暮らしてるってわけさ。ふっ！";
			link.l1 = "なかなかの話だな。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "クズどもだ。全員な！プッ！（唾を吐く）あらゆる種類の下衆ばかりだ。 リチャード・シャンボンなんざ顔に犯罪者って書いてあるぜ。カッセル？ あいつにとっちゃ人殺しなんて呼吸みたいなもんだ。ジャスパー・プラットは前科者。マスケットはただの酔っ払い。 まだ続ける必要あるか？\nジョセフ・ローダーデールだけがここでまともな男だ――もちろんお前を除いてな。あいつはイギリス海軍の士官だ。ここには貴族が二人いる： アントニオ・デ・ベタンクールとロレンツォ・ソルデッラ――くそったれなスペイン野郎どもめ！あんな連中と同じテーブルに座る気にもならねえ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "クズやろうどもと下衆の集まりさ。だが、俺たちには手を出さねえ。 あいつらは互いに殺し合うことの方がずっと興味あるからな。しかも、それが止まったことは一度もねえ――暴力なしじゃ生きていけねえ連中だ。\n俺も海賊は好きじゃねえが、正直言って、あいつらが来てから島は前より静かになったと思うぜ。 ナーワルとリバドスの均衡を取ってくれてるからな。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "決してないよ。島の周りでは嵐がよく起こるが、島自体はいつも穏やかなんだ。たぶん神の御業か、 何かの魔法かもしれないが、俺にはわからねえ。たまに強い風や雨が来ることはあるが、 被害が出るほどひどいものじゃないさ。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あっは！お前がただのならず者だって、一目見た瞬間にわかったぜ！", "俺の持ち物に手を出すんじゃねえ、このクズ野郎！", "俺の胸からその汚え手をどけろ！この仕打ち、串刺しにしてやるからな！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の物を盗もうなんて、ふざけんじゃねえぞ、この悪党め！とっとと失せろ！";
			link.l1 = "落ち着け、女！";
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
			dialog.text = LinkRandPhrase("旦那、武器をしまってくれ。あんたのせいで落ち着かねえんだ。", "武器をしまえ、騒ぎを起こしてるぞ。", "そんなに武装して歩き回ったら誰かを傷つけるかもしれねえ。しまっときな、旦那。");
			link.l1 = LinkRandPhrase("いいだろう。", "「いいだろう。」", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "この町の紳士として、武器をしまうよう要求する！", "あなたのような紳士なら、武器を振り回す必要なんてないはずだ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "よし、そういうことだな。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、武器をしまってくれ。お前のせいで落ち着かねえんだ。", "お願いですから武器をしまってください、旦那。あなたに怯えてしまいます。");
				link.l1 = RandPhraseSimple("「よろしい。」", "俺はそれを片付けている。");
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
