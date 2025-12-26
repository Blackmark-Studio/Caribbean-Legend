// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

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
				dialog.text = "消え失せろ、友よ。理由もなく人を襲う奴らに話すことなんてねえんだよ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "おお！ここにいたのか。ちょうど探しに行こうとしてたんだ。お前が必要なんだ、相棒。";
				link.l1 = "今日は妙に愛想がいいな、リチャード。さあ、言ってみろ。何の用だ？";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "何の用だ？正直言って、今日は機嫌が悪いんだ――いや、最後に機嫌が良かったのがいつだったかも思い出せねえな。";
				link.l1 = "そんなにひどいのかい、友よ？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何の用だ？";
				link.l1 = LinkRandPhrase("リチャード、最近何か噂を聞いたかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。気分は良くなったか？じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "悪い？いや、悪くはねえが、良くもねえさ。で……何の用だ？";
			link.l1 = "ちょっと挨拶しに来ただけさ。俺はここに来たばかりだから、島を歩き回って人々と知り合っているんだ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "本当かい？まあ、いいだろう。俺はリチャード・シャンボンだ。昔は貴重な品物――中には違法なものもあったが――を取引していた。だがここ九年は、沈没船の残骸をあさってはガラクタを探し、 それを食い物や金と交換して暮らしてるんだ。";
			link.l1 = "そして俺は "+GetFullName(pchar)+"「…船長か…」";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "「元船長ってことか、ははっ！」";
			link.l1 = "実は、俺の船は今ブルーウェルドにあるんだ。ここへはバーク船で来たんだぜ。";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "本当か？ありえねえ！で、今お前のバーク船はどこにあるんだ？";
			link.l1 = "底で……";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "ああ……俺はてっきり……まあいいさ、相棒。ラムでも飲みに行くぜ……";
			link.l1 = "うまくいくといいな。話せて楽しかったぜ。また今度な。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("「ようリチャード、最近何か噂は聞いたか？」", "島で何か新しいことが起きたか？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "前はそうじゃなかったか？まあまあ、誰だって悪い日くらいあるさ！それより、 島中でお前が腕利きの戦士だって噂になってるぜ。本当なのか？";
			link.l1 = "人々が何を言っているかは知らねえが、剣の扱いなら俺に任せとけ。";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "「よし。聞け、」 "+pchar.name+"「外輪のこと、そしてそこで見つかる貴重な品々について俺が話したのを覚えてるか？」";
			link.l1 = "リチャード、みんなからその話を聞いたぜ。どうやらあの指輪を探すのがこの正義の島で唯一の暇つぶしらしいな――政治的な駆け引きを除けばな。";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "これほど真実を言ったことはないな、はは！単刀直入に言うぜ。（声を潜めて） 外輪のところで手つかずの船を見つけたんだ。状態もいい、こんなのは珍しいぜ。\nしかもでかい船だ――ピナスだ。ここに流れ着いたのはつい最近、二ヶ月ほど前だ。他の誰もまだ気づいてねえから、 今ならあの船を荒らしてひと儲けできるってわけさ。";
			link.l1 = "俺に一緒に来てほしいのか？";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "その通りだ！ピナスの船首は潰れてるし、あの忌々しいカニどもが中に入り込んで、船倉に巣まで作りやがったんだ。 奴らに気付かれずに忍び込むなんて無理だし、水面からメインデッキにどうやって上がればいいかも分からねえ。\n俺は戦いが得意じゃねえ――もう何年も刃物なんて握ってねえからな――だからあんな化け物どもを一人で倒すなんて絶対無理だ。だからお前に頼みに来たんだ。";
			link.l1 = "つまり、お前のためにあの船の中のカニを全部始末しろってことか……";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "ああ。俺の提案はこうだぜ：俺が船までの道を案内する、あんたがカニどもを片付ける、 そして見つけた戦利品は山分けだ。";
			link.l1 = "いや、旦那、俺は興味ねえよ。半分沈んだ船の中でカニの大群と戦って、報酬も怪しいんじゃ、 そんな苦労する価値はねえ。もっと無鉄砲な奴でも探しな。";
			link.l1.go = "ring_exit";
			link.l2 = "面白いな……俺もずっと外輪を探索してみたいと思ってたんだ。決まりだ！沈没船を案内してくれ、カニどもは俺が片付けるぜ。";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "残念だな……間違いを犯してるぜ、外輪で手つかずの難破船なんて滅多にねえんだ。まあ、あんたの選択だ。じゃあな……";
			link.l1 = "「じゃあな、リチャード…」";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "お前のこと、俺の勘は当たってたみたいだな、相棒。あの中には面白いものがたくさん見つかりそうな気がするぜ……";
			link.l1 = "どうかな。あそこにカニが何匹いるか知ってるか？";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "四人か五人くらい……まあ、俺が見たのはそれくらいだ。";
			link.l1 = "よし……いつ出発するんだ？";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "明日でどうだ？準備する時間が必要なんだ。ジュリアン兄弟から解毒剤をもらっておけ――カニの顎は毒があるからな。用心するに越したことはねえ。明日の朝八時に傾いた甲板で会おう。場所は分かるか？\n";
			link.l1 = "いや、どこだ？";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "サン・アウグスティンの裏手に古い難破船があるんだ。船首は水中に沈み、船尾が高く持ち上がってるから「傾いた甲板」 って呼ばれてる。乗り込むには泳ぐしかねえんだよ。\nロープ橋の両側どちらからでも水に入って、サン・アウグスティンの船首か船尾を回り込んで傾いた甲板によじ登れ。 そこから俺たちの手つかずの難破船まで泳ぐぞ。";
			link.l1 = "わかった。じゃあ、また明日な！";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "八時、傾いた斜めの甲板だ。";
			link.l1 = "ああ、ああ、覚えておくよ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "おう、いたな、相棒。カニサラダでも作る気か？";
			link.l1 = "もちろんだ！";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "よし。さて、頭を外輪の方に向けて見てみろ。水面から突き出してる難破船が二隻見えるだろう？";
			link.l1 = "ふむ……ああ、見えるぞ。";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "あいつらの間を見て、外側の輪を見ろ。俺たちの方に船首を向けてるガレオンが見えるか？";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "ああ、俺…見える、見えるぞ！";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "あいつが俺たちの標的だ；俺たちのピナスはあいつの背後に隠れている。まっすぐ泳いで、曲がるな。 そこから先は俺が道を示すし、終わったら正義の島へ戻る方法も教えてやる。\n貨物倉への入口はピナスの船首に空いた穴だ。お前が全部のカニを始末するまで、俺は中に入らねえ。";
			link.l1 = "俺は約束を覚えてるぜ。お前が道を案内してくれりゃ、カニの始末は俺がやる。行くか？";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "そうしよう。俺がついていくぜ。";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "へっ、やるじゃねえか！どうやら全部仕留めたみてえだな！";
			link.l1 = "「『四人か五人くらい』しかいないって、誰かがはっきり言ってたのを覚えてるんだが…」";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "見てくれよ、旦那、俺は点呼なんてしてねえ、ただ穴から覗いただけだ。わざと嘘なんかつかねえって！";
			link.l1 = "どうでもいいさ。積荷室を探してみるか……？";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "もちろんさ！だから俺たちはここにいるんだぜ。";
			link.l1 = "よし、時間を無駄にしないでおこう…";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "ちょっと待ってくれ、友よ、まだ見たい場所を全部調べてないんだ。もっとよく探せば、 もっと価値のあるものが見つかるかもしれねえぞ。";
			link.l1 = "……いいだろう……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "特に変わったものはないよ。ここには高価な品物はなくて、塩漬け牛肉の樽とコプラの箱ばかりさ。だけど、 高級なワインのケースは見つけたぜ。そっちは何かあるか？";
			link.l1 = "大したものじゃねえよ。ちょっとした価値のある物もあるが、あとは言った通り塩漬け牛肉とコプラばかりさ。";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "足りねえな……上の階に行って、上甲板と船室を調べようぜ。";
			link.l1 = "行こう。";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "くそっ！見てみろよ！クソみたいなカニどもがそこら中にいやがる！どうやってここまで上がってきたんだ！？";
			link.l1 = "落ち着け！ここにいろ、動くな、そして静かにしてろ。俺があいつらを片付けてくる……";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "ほう！お前の剣の腕前の噂は本当だったんだな！俺が一人だったら、とっくに海に飛び込んで逃げてたぜ。";
			link.l1 = "「それで、そんなに簡単にビビっちまうようじゃ、どうやって昔は密輸業者なんかやってたんだよ、あん？」";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "まず第一に、俺はもっと若くて、力もあって、無鉄砲だったんだ。第二に、俺は兵隊じゃねえ――密輸屋はいつだって流血を避けようとするもんさ。第三に、俺の得意なのは帆や舵を扱うことで、剣やピストルじゃねえ。 そんでもって、ここで何年も暮らしてたら、すっかり骨抜きになっちまった！\nだから俺に腹を立てないでくれよ。上の甲板を見に行こうぜ。どうやらこの船、ひどい戦いに巻き込まれたみたいだ。 見ろよ、この損傷……";
			link.l1 = "お前の言う通りだ。この船は確かに激しい砲撃を受けたんだ。引き続き探してみよう。";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "それから、士官たちの船室への入り口も探さなきゃならねえ。";
			link.l1 = "それじゃあ、時間を無駄にしないようにしよう。カニを見かけたら呼んでくれ！";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "また何もない！ちょっとした宝飾品があるだけだ。それでもいいさ、甲板にはたいてい貴重な物なんてないからな。 本当にいい物は船室にあるはずだ。あそこに船長室への入口があるぜ。調べてみよう。";
			link.l1 = "気をつけろ、中で何が待ち受けているかわからねえからな。俺が先に入ったほうがいいかもな？";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "行こう。 "+pchar.name+"。もうあなたの陰に隠れたりしない。";
			link.l1 = "さあ、行けよ……";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "どうやら運が良かったみてえだな。カニも他のクソもここにはいねえ。だがクソッ、だんだん腹が立ってきたぜ。 せいぜい数十枚のドゥブロンとガラクタしか見つからねえじゃねえか！";
			link.l1 = "落ち着け。覚えておけ、貴重品はいつも船長室に保管されてるんだ。さて、何があるか見てみようぜ！";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "ははっ！やっぱりな！商人どもの癖はよく知ってるぜ。船のあちこちに隠し場所を作って、 財宝をしまい込むのが好きなんだ！このピナスの船長もなかなかのずる賢い野郎だったが、俺はそう簡単には騙されねえ！ 見ろよ、こんなもんを見つけたぜ！";
			link.l1 = "見せてくれ！";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "四万ペソ、ドゥブロンでいっぱいの宝箱が二つ、エメラルドの包みと宝石の山だ！持ち主はかなりの金持ちだったんだな。 少なくとも俺たちの苦労は報われるぜ、もっといろいろ見つかると思ってたがな。さあ、戦利品を分けようぜ。";
			link.l1 = "素晴らしいぞ、リチャード。少なくとも手ぶらでは帰らずに済むな！";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "さて、それぞれが甲板で見つけたものは自分のものにしようじゃねえか。みんな、それでいいか？ お前は宝箱や棚で何かいいもの見つけたか？";
			link.l1 = "いくつかのインディアンの遺物やお守り、書類などだ。";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "自分で持ってな。結局、一番危ない仕事をやったのはお前だろう。";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "いいだろう。それから、あんたみたいな財宝探しには役立ちそうなものを教えてやるぜ。 あの机の上に船長の日誌が置いてあったんだ。その内容はとても悲しいものだが、俺たちの探索にはきっと役立つはずだ。 積荷室のどこかに金でいっぱいの箱が隠されてるらしい！ほら、読んでみな！";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "いいだろう。しかし、もう一つ見つけたものがある――船長の日誌だ。";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "それは否定しねえよ、ははっ！さて、戻る時間か？";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "ああ。船のことは誰にも言うなよ、俺たちだけの秘密だ。確かにコプラはいらねえが、あの食料は役に立つぜ。 もう提督から買う必要もなくなるしな。";
			link.l1 = "よし、わかった。他の奴らがこの船をすぐに見つけないことを祈るぜ。行こう！";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "読んだか？";
			link.l1 = "「まだだ……」";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "じゃあ、読んでみようぜ！何か大事なことが分かるかもしれねえ。それに、 この船がどうやってここに来たのか知るのも面白そうだ。読んでくれ！";
			link.l1 = "ふむ。よし、今読むとするか……";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "読んだのか？中には何が書いてあった？";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "やったよ。聞いてくれ、とても悲しい話なんだが、実は貨物室に金でいっぱいの隠し箱があるってことが分かるんだ！ 読んでみてくれ、もしかしたら場所が分かるかもしれないぜ。";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "ちょっと待ってくれ。読んでから教えるぜ…";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "本当か？ "+pchar.name+"……俺は……まあ、字を読むのがあんまり得意じゃねえんだ。そこに何て書いてあるか教えてくれよ、な？";
			link.l1 = "要するに、このピナス船はカリブ海を南から北へと横断し、新スペインの海岸沿いを進んでいたんだ。\nその途中で、船長は下オリノコの部族のインディアンの王女に恋をして、結婚した。\n彼女は、自分たちの民が生贄の儀式を行っていると語ったんだ……";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "奴らの生け贄は金塊だったんだ！だから当然、うちの船長は副長と航海士の助けを借りてその金を盗んだのさ。 貨物室の箱に入れて、その上にコプラをかぶせたんだよ…";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "だが、その聖なるインディアンの場所を荒らしたことは罰せられたようだな。船は無風状態に陥り、水も尽き、 熱病が発生し、海賊に襲われた。\n船員たちはインディアンの娘――船長の妻を責め、彼女を海に投げ捨てろと要求した。もちろん船長は拒否し、反乱が起きたんだ……";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "船長は戦いに敗れた。\n最後の日誌によれば、彼は自分とインディアンの妻を船室に立てこもらせ、扉を破ろうとした者は誰でも撃ったそうだ。\n嵐が彼らに迫っていたとも書かれている――おそらくそれが船を正義の島へと導いたのだろう。\n結局、妻は撃たれ、反乱者たちが最終的に船長も殺したのは疑いようがない。";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "ふむ、そうだな、そうだ……悲しい話だ……だが金は……本当に金塊の箱が船倉にあるのか？どれだ！？探し出そうぜ！必要ならオーロップ全部ひっくり返してやる！";
			link.l1 = "わかった、わかったよ、探すってば――落ち着け、リチャード！";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "ははは！見つけたぞ！この輝きを見てみろよ！箱いっぱいだ！ここには五千個以上の金塊があるに違いねえ！ こんなに大量の金は見たことがねえ！！";
			link.l1 = "おめでとう、相棒。俺たちの努力が実ったみたいだな！この金をどうする？";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "どういう意味だ？俺たちで半分に分けるんだろうが！";
			link.l1 = "つまり、どこにそれを置くつもりなんだ？ここに置いていくのか？";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "はっ！いや、俺は金貨を自分だけの隠し場所に隠すぜ、誰にも見つからねえ所にな。隠すことなら俺の得意分野だ！ 金貨の半分はこの樽に入れよう――それが俺の取り分だ。日が沈む前に持ち出すぜ。\nお前の分は好きにしな。だが、自分の隠し場所に移しておいた方がいいぜ。金貨がなくなっても俺のせいにするなよ。 俺は俺なりに正直者だし、お前の取り分には手を出さねえ。でも、すぐに他の奴らがこの船を見つけるかもしれねえし、 見つけたものは容赦なく持っていくだろうからな。";
			link.l1 = "ありがとう。自分の金の使い道は自分で考えるさ。さて、お前の取り分はあの樽に入れておくぜ…";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "終わった……ありがとう。 "+pchar.name+"、一緒に来てくれてありがとう。君がいなければ、これは成し遂げられなかった。さて、 これからはタルタン船でも建造して……ここから帆を上げて出ていくべきか……\nいや、それは後で考えよう。今はこの金貨を隠し場所に運ぶだけで手一杯だ。じゃあな、友よ。 君も自分の取り分を賢く使ってくれよ！";
			link.l1 = "「じゃあな、リチャード。今日は素晴らしい一日だったぜ。元気でな！」";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "質問かい？まあ、仕方ねえな、どうぞ…";
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
				link.l3 = "どこかのクランに入ることを考えたことはあるか？例えば、ナーワル族とかさ。";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "外輪では面白いものがたくさん見つかるって本当かい？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "十年間、俺と仲間たちはキューバからこの島までタルターヌ船で行ったり来たりして、島の連中と交易してたんだ。 島の場所は秘密にして、新鮮な肉や果物、野菜を沈没船の積み荷から手に入れた品物や金と交換してた。 いい時代だったぜ！\n正義の島の連中は昔から食料の調達に苦労してたから、 俺たちが持ってきた香辛料付きのジューシーな肉には大金を払ってくれた。ヨーロッパじゃとんでもない値段だからな！ 毎回の航海で、トルトゥーガの娼婦を全員買えるくらいの稼ぎがあったもんさ。\nだが、何事にも終わりはある。この海域の嵐はどんどん激しくなり、島への航海は危険極まりなくなった。 仲間の何人かは商売から足を洗ったが、俺と勇敢な連中が十数人、最後までやり続けた。\nそしてついに、嵐に巻き込まれて島から二マイルのリーフに打ち上げられたんだ。 あの荒れ狂う海をどうやって泳ぎ切ったのか、今でも分からねえ。今じゃ俺も、かつて交易してた連中の一人さ。";
			link.l1 = "面白い話だな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "はっ！いつかここから出てやるさ、くそっ、でも乞食のままじゃごめんだぜ！キューバに行ったって何になる？ もう友達もいねえし、懐も空っぽだ。\n外輪のどこかで積荷が宝物でいっぱいの船か、ドゥブロン金貨の山を見つけりゃいい。 それさえあれば新しいタルタン船を作って、嵐をくぐり抜けて、文明の世界に戻ってやるさ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "なぜ俺がそんなことしなきゃならねえんだ？三日に一度、 サン・ガブリエルの見張りで日差しに焼かれながら立ちっぱなしなんてごめんだぜ。\nそれに、あいつらは島民以外を雇いたがらねえんだ――結局、あいつらは生まれも育ちもここだからな……黒人たちも同じさ。\nだから、俺は一人でいたほうがマシだ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "もちろんさ！それがこの島の連中の生き方だぜ。やつらがいつ宴を開くか知ってるか？ 新しい船があの輪っかで難破した時さ。\nまだ手つかずの沈没船がたくさんあって、金や物資がぎっしり詰まってるが、外輪の探索は危険だぜ。 あそこはめちゃくちゃだし、一人で行くもんじゃねえ。索具に絡まったり、足を滑らせて落ちたりしたら、 そこで終わりだ。そうやって死んだ奴も多いんだぜ。";
			link.l1 = "ふむ…それなら気をつけるよ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("おい、俺の隠し物に手を出すんじゃねえ、泥棒め！", "この島の誰も信用できねえ！覚悟しろ、泥棒め！\n", "俺の海のチェストに触るんじゃねえ、この野郎！");
			link.l1 = "消え失せろ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "無実の女を襲うなんて！？このままじゃ済まさないぞ！";
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
			dialog.text = LinkRandPhrase("武器をしまえ。お前のせいで落ち着かねえんだ。", "その刃を使うつもりがないなら、しまっておいた方がいいぜ。", "その武器をしまえよ、人々が怯えてるぜ――俺も含めてな！");
			link.l1 = LinkRandPhrase("「いいだろう。」", "「わかった。」", "すまねえ……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "その刃を使うつもりがないなら、しまっておいたほうがいいぜ。", "武器をしまえ。お前のせいで落ち着かねえんだ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "「わかった。」", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "武器をしまえよ。お前のせいで落ち着かねえんだ。", "その武器をしまえよ、みんな怯えてるぜ――俺も含めてな！");
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
