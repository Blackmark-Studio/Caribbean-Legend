// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "聞けよ、旦那、なんで喧嘩を始めたんだ、ああ？俺の作業場に用がねえなら、敵ってことだろ。出て行け！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "「ああ、」 "+GetFullName(pchar)+"！お前の活躍は聞いているぜ。ドナルドの友人、そして俺たちの仲間になってくれて嬉しいぜ。 ナーワル族は友情の価値をよく知ってるんだ、それだけは間違いねえよ。";
					link.l1 = "そうだといいな。今はお前の助けを頼んでもいいか？";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "それで？何の用だ？";
					link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"……それで、俺はただ島を歩き回って、人々と知り合っているだけさ。邪魔してるかい？";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "「ああ、」 "+GetFullName(pchar)+"！お前の活躍は聞いているぜ。ドナルドの友人となり、俺たちの味方になってくれて嬉しいぜ。 ナーワル族は友情を大事にするんだ、それだけは間違いねえ。";
					link.l1 = "そうだといいな。今はお前の助けを頼んでもいいか？";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "「ああ、」 "+GetFullName(pchar)+"！また話したいのか？悪いが、俺にはそんな時間も気もねえんだ。";
					link.l1 = "わかった、邪魔はしねえよ。";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "その通りだ！お前、邪魔なんだよ、旦那。俺はユルゲン・シュミット、ナーワル族の鍛冶屋兼銃工だ。 俺は仲間たちに武器を作ってやってる。だがな、良い刃や鍵、錠前を作ったり、 タワーマスケットの機構を直したりするには時間がかかるんだ。たっぷりの時間と根気、そして細心の注意が必要だ。 だから俺は邪魔されるのが大嫌いなんだよ。";
			link.l1 = "武器を作っているのか？何か注文できるか？";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "いや。俺はナーワル族の仲間のためだけに武器を作るんだ。これが俺の信念で、絶対に曲げねえ。だから、旦那、 期待するだけ無駄だぜ。俺たちの一員になるか、せめて味方になるなら、その時は話をしようじゃねえか。";
			link.l1 = "わかった。じゃあ、お前のところを離れるぜ。迷惑かけて悪かったな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "できるさ。ナーワルの仲間は俺の仲間でもある、だからお前の話を聞いてやるぜ。";
			link.l1 = "刃物を注文したいんだ。";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "アラン・ミルロー故人のために特別な刀を作ったと聞いたぜ。あのブロードソードは見たことがある。いい武器だな。 俺もああいうのを注文できるか？";
				link.l2.go = "narval";
			}
			link.l3 = "まだ考えがないんだ。考えてからまた戻ってくるぜ！";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "「はっ、」 "+GetFullName(pchar)+"！お前、溺れなかったのか？すごいじゃねえか！本当に生きてるのか？";
				link.l1 = "心配するな、ユルゲン。俺は生きてるぜ！溺れるつもりなんてなかったんだ…";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "「ああ、」 "+GetFullName(pchar)+"「！何の用だ？」";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "頼まれていた特別な鉄を三つ持ってきたぜ。見てくれ、これで合ってるか？";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "見てくれ、ユルゲン。底で面白い鉄のインゴットを見つけたんだが、お前が頼んだよりずっと重いぞ。 少なくとも五ポンドはあるな。";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "刃物を注文したいんだ。";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "刃の代金として、さらにドゥブロン金貨を持ってきたぞ。";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "故アラン・ミルローのために特別な刃を作ったと聞いたぜ。あのブロードソードは見たことがある、見事な武器だ。 俺もああいうものを注文できるか？";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "俺の注文を受け取りに来たんだ。もう出来上がってるはずだろう？";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "いや、なんでもないさ。ちょっと挨拶したかっただけだ。";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "わかった。しかし、どんな依頼でも特別な条件があるから、まずはよく聞いてくれ。";
			link.l1 = "聞き耳を立ててるぜ。";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "俺から注文できる剣は一振りだけ、しかも一度きりだ。特定の武器は作らねえ、選べるのは種類だけ――レイピア、サーベル、もしくはブロードソードだ。よく考えて選べよ。その時手元にある素材次第で、 剣の性能と質が決まるからな\nさて。注文品の製作には二十日かかる。支払いはドゥブロン金貨のみ、千枚だ。前金で頼むぜ。";
			link.l1 = "本当に！高いな…";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "高いぜ。でも俺の作る刃物は一級品だ、だから値段も妥当ってもんさ。\n決めるのはあんた次第だ、無理にとは言わねえよ。";
			link.l1 = "わかった、ユルゲン。ああ、注文をお願いしたい。";
			link.l1.go = "blade_3";
			link.l2 = "ふむ。お前に何か注文する前に、少し考える時間が必要だ。あとでまた話そう！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "よし。じゃあ、ドゥブロンを渡しな。";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "こちら、どうぞ。私には "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "ふむ。残念ながら、今は手元にないんだ。でも必ず持ってくるから、その時にまた話を続けよう。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "これが最後の選択か？本当にいいんだな？";
			link.l1 = "ああ、そうだ。";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "素晴らしい。仕事と材料の代金はいただいたから、今すぐ始められるぞ。";
				link.l1 = "注文してもいいですか？";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "よし。お前のドゥブロン金貨を受け取るぜ。俺に持ってくるんだ\n "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" もっと。";
				link.l1 = "手に入れたらあなたのところに持ってくる。";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "もちろん！どの種類が好みだ？レイピア、サーベル、それともブロードソードか？";
			link.l1 = "レイピアか。俺は優雅で軽い武器が好きなんだ。";
			link.l1.go = "rapier";
			link.l2 = "サーベルだ。俺の考えじゃ、これが最適だぜ。";
			link.l2.go = "sabre";
			link.l3 = "間違いなくブロードソードだぜ！斬って叩き切るんだ！";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "かしこまりました。ご注文の品は二十日後に取りに来てください、それより早くは渡せません。";
			link.l1 = "ありがとう！二十日後にまた会おう。じゃあな、ユルゲン。";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "かしこまりました。ご注文は二十日後に取りに来てください、それより早くは渡せません。";
			link.l1 = "ありがとう！二十日後にまた会おう。じゃあな、ユルゲン。";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "かしこまりました。ご注文品は二十日後に取りに来てください、それより早くはお渡しできません。";
			link.l1 = "ありがとう！二十日後に会おう。さようなら、ユルゲン。";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "はい。あなたの剣はできています。どうぞ、お受け取りになり、お使いください。\n手に取った瞬間、その価値が分かるはずです。";
			link.l1 = "ありがとう、Jurgen。";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "あいにくだが、友よ、断らねばならん、理由は二つある。まず第一に、 俺がそんなブロードソードを作るのはナーワル族の者だけ、それも特別な相手だけだ。\n第二に、そのための材料が手元にないんだ。";
			link.l1 = "それで、その特別な鉄って何なんだ？底から手に入れたって聞いたが…";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "その通りだ。この金属のかけらは、俺たちの浅瀬のあちこちに散らばっている。どうしてここにあるのかは分からねえ。 だが、この鉄は特別で、決して錆びず、これで作った刃は鈍らねえんだ。だから、もしその鉄を手に入れられれば、 この件は解決できるかもしれねえ。\nだが、まだ問題がある。お前はナーワルじゃねえ……";
			link.l1 = "ふむ。本当にそれが重要なのか？";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "ああ。気まぐれだと思ってくれて構わねえが、俺はナーワルのためだけにそんな幅広の剣を作るつもりだ。";
			link.l1 = "そうか……まあ、仕方ねえ、受け入れるぜ。だが、ひとつ提案がある。この剣をナーワル族の仲間のために注文してもいいか？";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "ふむ。鉄を持ってきてくれるなら、作ってやってもいいぞ。俺の信念には反しねえ……で、その幅広の剣は誰のために作ればいいんだ？";
			link.l1 = "レッド・メアリーのためだ。彼女はナーワル族の出身で、こんな素晴らしい武器を持つにふさわしい。";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "はっ！そんなこと自分で気づけたはずだがな。もう年を取りすぎたか……まあ、同意するぜ。メアリーはきっとそんな贈り物をもらって本当に喜ぶだろうよ……鉄を持ってきてくれれば、俺がブロードソードを作ってやる。刃の代金は……ああ、もういい、今回はタダで作ってやるさ。これはお前だけじゃなく、俺たち二人からの贈り物ってことにしよう。";
			link.l1 = "ありがとう！どれくらい鉄が必要なんだ？";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "底で見つけてきたあの破片は全部同じだった――どれも一ポンドずつだ。俺はあれと同じやつを三つ必要なんだ。";
			link.l1 = "わかった。探してみるとしよう。また話そうじゃねえか。";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "見せてくれ……ああ、そうだ！こんな小さな破片を底から見つけるのは大変だったか？";
			link.l1 = "そうだな……まあ、メアリーはそれだけの価値がある女だろう？";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "見せてくれ……こりゃ驚いた！確かに底板の鉄だが、こんなに大きな塊は初めて見るぜ。これだけあれば幅広の剣が作れるな。 見つけるのは大変だったか？";
			link.l1 = "そうだな……まあ、メアリーはそれだけの価値がある女だろう？";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "ますます君のことが好きになっていくよ、 "+pchar.name+"……よし、わかった。それじゃあ今度は俺が美しいアマゾンのために働く番だな。ブロードソードを作るのに二日かかるから、 他の注文は後回しにするぜ\n明後日、メアリーをここに連れてきてくれ。本人には言うなよ、サプライズだ。きっと子供みたいに喜ぶだろうさ。";
			link.l1 = "よし、ユルゲン。決まりだ！明後日会おう！";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+"「邪魔しないでくれ。大剣を期限までに仕上げてほしいんだろう？」";
			link.l1 = "ああ、もちろんだ。俺は行くぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してるんだ、え？泥棒め！","見てくれよ！俺がちょっと物思いにふけってた隙に、お前は俺の胸を調べやがったな！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("聞いてくれ、武器はしまってくれよ。見てると落ち着かねえんだ。","ここではな、刃物を振り回すのは許されねえんだ。しまいな。","聞けよ、剣を振り回して中世の騎士みたいな真似はやめとけ。しまっとけ、似合わねえんだから…");
			link.l1 = LinkRandPhrase("「いいだろう。」","いいだろう。","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの街の住人だ。剣を下ろしてくれないか。","聞いてくれ、俺はこの町の住人だ。だから剣を下ろしてくれ。");
				link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろついてると俺がビビっちまうじゃねえか…","男たちが武器を抜いたまま俺の前を歩くのは好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。","俺が持っていくぜ。");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
