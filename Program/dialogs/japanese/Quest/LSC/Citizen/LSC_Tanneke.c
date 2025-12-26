// Таннеке Эверс - просто девушка
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
				dialog.text = "俺にかまうな、旦那。平和な人々を襲うような奴とは話したくねえんだ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう！あなたを知っているかな？いや、見かけたことはなかったと思うが…";
				link.l1 = TimeGreeting()+"。俺は新参者だ、確かにな。俺の名は船長 "+GetFullName(pchar)+"";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("やあ、タネケ。正義の島では何か新しいことがあったかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。良い一日を！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "元船長だ。（くくっ）";
			link.l1 = "何を……？ああ、わかった。いや、俺はまだ船長だぜ。俺の船はスペイン領沿岸に停泊してるんだ。ここにはバーク船で来た――いや、正確にはほとんど辿り着けたってとこだな。バーク船は船倉に穴が開いて、沖合二マイルで沈んじまったんだ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "「それで、どうやって嵐を生き延びたんだ？」";
			link.l1 = "嵐？嵐なんて覚えてねえぞ……";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "どうして知らないんだ？島のまわりにはいつも嵐があるんだぜ。みんなそう言ってるさ。";
			link.l1 = "そうだな……俺は運よくそれを避けられたみたいだ。海はまったく穏やかだった……失礼、こんな美しいお嬢さんのお名前を伺ってもよろしいかな？";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "あっ！ごめんなさい、自己紹介を忘れていました……私の名前はタネケです。よろしくお願いします。";
			link.l1 = "こちらこそ、はじめまして、タネケ…。本当に光栄だよ。";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "それで、どうして自分の船をバーク船と交換したんだ？";
			link.l1 = "正義の島について噂を聞いて、自分の目で確かめたくなったんだ。だが、自分の船を危険にさらす気はなかったから、 ブルーウェルドに停泊させて、この辺りを探索するためにバーク船を買ったんだ…";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "なるほどな。お前もアドルフ・バルビエと同じだな。アルバラード船長の話を読み過ぎて、 ベタンコート提督の金を探しに来たってわけか。だがな、船長、 あのバルビエみたいな狡猾な悪党ですら見つけられなかったもんを、お前が見つけられるとは思えねえぜ。\nそれに、俺は提督の金なんて最初から存在しねえと思ってる。 アントニオがじいさんを偉く見せたくてでっち上げた話だろうよ。\nま、そういうわけでお前もここに残るんだな！ここに来るのは簡単だったろうが、出て行くのは無理だぜ――無傷でな。";
			link.l1 = "金？ベタンコート提督？そんな話は初耳だな……まあ、とにかく、俺はこの島を無事に出るつもりだぜ。話せて楽しかったよ、タネケ。じゃあな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "どうぞ、ご質問を、船長…。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "島を出ようとしたことはあるか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここでの暮らしはどうだい？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "「えっと…女性たちは提督から食料を買わなきゃいけないのか、それともタダでもらえるのか？」";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "私は生まれはオランダですが、サンティアゴで暮らしていました。両親に言われて、 ジェラルディ銀行家の家で女中として働くためにそこへ行ったんです。ご存じですか？三年前、 その家の一人が通信用ラガー船でヌエバ・エスパーニャへ向かいました。私は彼に付き添うよう命じられました。\n航海の二日目、スペイン国旗を掲げたブリガンティンに捕まりました。彼らの士官が私たちの船に乗り込んできて、 船長と何やら話していましたが、内容は分かりません。船長は激怒して士官をラガー船から追い払いました。 士官が自分の船に戻ると、彼らは私たちに砲撃してきたのです。\n私たちは逃げようとしましたが、結局乗り込まれてしまいました。彼らの狙いは私の主人ジェラルディだったのでしょう。 彼の船室に突入し、彼を手錠で拘束して連れて行きました。私と乗組員は船倉に閉じ込められました。\n沈められるのかと思いましたが、彼らはそのまま去っていきました。水夫たちはなんとか船倉から脱出しましたが、 甲板で船長が死んでいるのを見つけました。私たちの誰もまともに航海術を知りませんでした。\n手探りで航海を続けていると、強い嵐に巻き込まれました。数時間後、 私たちのラガー船は外輪の残骸に打ち上げられました。今もそこにあります。夜明けに、 私と他の生存者数人はラガー船のロングボートに乗り込み、この島まで漕いできたのです。";
			link.l1 = "なんて話だ！";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "いいや。どうやって逃げるんだ？航海できる船なんて一隻もないし、ロングボートで外に出ようとするのは自殺行為だ。 言っただろう、この島は嵐に囲まれてるんだ。\n昔、地元の連中が五人、この方法で脱出を試みたことがある。インディアマンの難破船から拾った頑丈な材木と良い帆で、 まともなロングボートを作った。九時間も潮流と戦って、ついに外洋に出た。だが数日後、 そのうちの一人がマストの残骸に縛り付けられて外輪部に戻ってきた……すでに死んでいた。\nそれ以来、出て行きたがる奴はほとんどいなくなったよ。";
			link.l1 = "恐ろしい……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "大丈夫さ。あの偉そうな高利貸しの家の下僕だった頃よりはマシだよ。ここには慣れさえすればいい。慣れてしまえば、 むしろ好きになるかもしれない。そう感じてる奴も多いんだ。クラン連中も、俺には別に気にならねえよ。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "もちろん買っているわよ。女の子の仕事はたくさんあるの。掃除、料理、みんなの手伝い……暇してるわけじゃないけど、無理して働いてるわけでもないわ。海賊たちは、クランとは違って、 普通の市民には食べ物を安く売ってくれるの。だから飢えることはないのよ。\n私はジリアンやナタリーを手伝うし、必要なときは彼女たちも私を助けてくれる。私たちは友達よ。 島にはもう一人女の子がいるの、スペイン人のラモーナ。でも彼女はほとんど一人でいるし、 私たちも特に仲良くなりたいとは思っていないの。";
			link.l1 = "それはなぜだ？";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "そうだな……まあ、人生に対する考え方が違うってことさ。彼女と話してみればわかるぜ。";
			link.l1 = "……わかった……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("誰だ……ああ神よ、泥棒だ！助けてくれ！", "ちょっと目を離した隙に俺を盗もうとするのか！？助けてくれ！", "俺の宝箱を荒らすつもりか？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の物に勝手に触るとは何様だ！誰か、助けてくれ！";
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
			dialog.text = LinkRandPhrase("武器をしまってくれ、旦那。あんたがそうしてると落ち着かねえんだ。", "ここでは刃物を振り回すのは許されていないんだ。しまってくれ。", "旦那、あんたが勇敢なのは知ってるぜ。剣を振り回して証明する必要はねえよ……");
			link.l1 = LinkRandPhrase("いいだろう。", "ご希望のままに……", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまってくれ、旦那。あんたがそうしてると落ち着かねえんだ。", "ここでは刃物を振り回すのは許されていないんだ。しまってくれ。");
				link.l1 = LinkRandPhrase("いいだろう。", "ご自由に……", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまってくれ、旦那。あんたがそうしてると落ち着かねえんだ。", "旦那、あなたが勇敢なのは知っている。剣を振り回して証明する必要はないんだ…");
				link.l1 = RandPhraseSimple("了解だ。", "俺が持っていくぜ。");
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
