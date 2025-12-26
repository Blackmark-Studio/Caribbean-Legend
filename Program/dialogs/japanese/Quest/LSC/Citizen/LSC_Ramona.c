// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "どっか行け、旦那。俺たち普通の人間が自分の用事をこなそうとしてるのに、あんたは襲いかかってくるんだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ほうほう！あんた、ここじゃ新顔か、それともどっかの貨物倉にでも隠れてたのかい。 俺があんたの顔を見るのはこれが初めてだぜ。";
				link.l1 = TimeGreeting()+"…貨物倉に隠れるなんて俺の流儀じゃねえ。俺は船長室の方が性に合ってる……でも、そうさ、ここは初めてなんだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+pchar.name+"! "+TimeGreeting()+"！会えて嬉しいぜ！どうしたんだ？";
				link.l1 = LinkRandPhrase("ラモナ、元気かい！？島の様子はどうだ？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "お前の美しい顔が見たかっただけさ。またな、ラモナ！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "それじゃあ、お互いに自己紹介といこうか…船長。私はラモナ・ロサノだ――「ロサノ夫人」なんて呼ぶんじゃないよ。大嫌いなんだ。あんたの名前は？";
			link.l1 = ""+GetFullName(pchar)+"。お会いできて嬉しいです、ラモナ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "本当に喜んでいるのか、それとも礼儀でそう言っているのか、 "+GetFullName(pchar)+"？本当に船長なのか、それとも冗談だったのか教えてくれよ？";
			link.l1 = "おおっと、質問が多いな！順番に答えてもいいかい？まず第一に、本当に嬉しいぜ。 こんな可愛い娘に毎日会えるわけじゃねえからな。第二に、確かに俺は船長だが、 今は俺の船がスペイン領沿岸に停泊してるんだ。\n";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "おかしいな！それで、船長、どうしてあんたはここにいるのに、あんたの船は本土の海岸にあるんだ？ 乗組員が散り散りになって船を奪われるのが怖くねえのか？";
			link.l1 = "俺はここへバルク船で航海してきたんだ……この海域を探検するためにな。自分の船は危険にさらしたくなかった――あれは俺の誇りであり、宝だからな。だが夜になって、バルク船は暗闇の中で暗礁か沈没船にぶつかり、転覆しちまった。 で、ほらよ！俺はここだ。\n俺の船は、どれだけ待たせても必ず俺を待っててくれるさ。ダニー・ホークが仲間たちをまとめてくれるだろう。";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "ダニー・ホーク？つまり…ダニエル・ホークのことか？まさか、あんたはあの女と一緒に航海してるって言うのか？";
			link.l1 = "神に誓って言うが、ラモナ、俺は嘘なんかついてねえ。ダニーは俺の部下だ。俺が自分の小舟で出かけてる間、 彼女に指揮を任せてきたんだ……どうしてあんたは彼女を知ってるんだ？";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "はっ！スペイン植民地の誰もが海賊ダニエル・ホークとその旦那ナサニエルを知ってるぜ。そうだ、お前だよ、旦那\n "+GetFullName(pchar)+"……きっとタフな男なんだろうな……お前さん、海賊かい？心配すんな、俺はお前さんみたいな連中とはうまくやれるんだ。タフな男は好きだからな。";
			link.l1 = "まあ、俺は今は本当の海賊じゃねえよ……今はヤン・スヴェンソンのために働いてて、ダニーが行方不明の旦那を探すのを手伝ってるんだ。";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "それでいて自分は海賊じゃないって言うのか？森の悪魔に仕えてて、相棒はダニエル・ホーク、ナサニエルを探してる……それに、ここに来たのは提督のためだろう？違うか？\n";
			link.l1 = "ラモナ、俺のことを海賊と呼びたきゃ呼べばいいさ。錨と呼んでも構わねえ――ただし、本当に錨として使わなきゃな！";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "どうやらあんたは本当に手強い男の一人みたいだな。 "+pchar.name+"。さて、俺はもう行かなくちゃな。島のどこかでまた会えるといいな、なんだかお前とは友達――いや、親しい友達になれる気がするんだ……";
			link.l1 = "なぜだ？良い一日を！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "おや、本当かい？まあ、聞いてくれ。答えられることなら答えるぜ…";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "きっと正義の島を出ようとしたことがあるんだろう？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここでどうやって暮らしているんだ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "ここで何をしているんだ？食い物はタダじゃねえんだろう？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はありません。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "それは長い話だ……全部、継父のせいさ。\n四年前、俺はハバナで幸せに暮らしていた。母が亡くなり、俺が財産の唯一の相続人になった。裕福ではなかったが、 十分に快適に暮らせる金はあった。\nだが継父はそれが気に入らず、俺を始末しようと決めたんだ。もちろん、 それを知ったのは街の門で二人の雇われゴロツキに襲われてからさ。あいつら、自分たちを雇ったのが誰で、 なぜ俺を殺そうとしたのか、自分でベラベラ喋ったんだ。\n幸いにも、奴らは素人だった。でなけりゃ、今ごろ俺は喉を掻き切られて茂みに転がってただろう。 馬鹿どもはまず遊んでやろうと思ったらしい。\n運命が俺を救った――ちょうどあんたみたいな船長が通りかかったんだ。状況を見てすぐにクズどもを斬り捨ててくれた――奴らに勝ち目はなかった。俺は事情を話して、少し泣いた……行くあてもないと知った船長は、俺を継父から守るために船に乗せてくれた――最初は一時的なつもりだったが、そのうち……\nきっと、俺はそのまま彼と一緒にいたと思う。だが二ヶ月後、彼は巡回船に出くわし、マストを失い、 強風に巻き込まれて、外輪の底で安らかに眠ることになった。俺は何とか生き延びて、正義の島の共同体に加わったんだ。 ";
			link.l1 = "悲しい話だ、言葉も出ないよ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "もちろん無理さ。ここをロングボートで出ようとした男を見たが……二日後に戻ってきたぜ。溺れないように壊れたマストに自分を縛りつけてたが、体は青ざめて石のように死んでたよ。\nそれで、教えてくれよ "+pchar.name+"、たとえ逃げ出せたとしても、俺はどうすりゃいいんだ？ハバナは俺にとって危険すぎる――義父がまた必ず俺を殺そうとするだろう。家も金もない。どこへ行けっていうんだ？娼館か？";
			link.l1 = "それでも、カリブ海に戻りたいのか？";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "どう思う？もちろん、そうさ。でも無理なんだよ、理由はさっき言った通りだ。もし誰かが俺の継父を――剣か弾丸で――始末できたら、昔の生活に戻れる希望もあるだろうさ。だが、 ハバナの総督と親しいあの継父に手を出す奴がいると思うか？だから何を話しても無駄さ。 ここから抜け出す道なんてないんだよ……";
			link.l1 = "どうなるか見ものだな。その時が来るかもしれねえ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "俺はただ生きてるだけさ。他に選択肢なんてねえんだ。友達はほとんど男ばっかりだよ、 だってうちの結婚適齢期の美女二人――ジリアンとタネケ――は俺のことが気に入らねえんだ。ナタリーはいい子だったけど、 あの二人のバカとつるむようになってから変わっちまった。馬鹿は伝染するもんだぜ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "私も他の女たちと同じように働いていて、主に男たちの手伝いをしているの。正義の島では女の仕事がたくさんあるから、 毎日忙しいわ。それに、よく贈り物ももらうのよ――ここでは普通のこと。でも、あたしを安い女だなんて思わないで。ちゃんと教育を受けて、良い家の出なの。ただ、 聖女ぶったりはしないだけ……あの人たちみたいにね……";
			link.l1 = "俺は別にあんたのことを悪く思ってたわけじゃねえんだ…";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("何をしているんだ――あっ！泥棒！", "見てみろよ！俺がちょっと背を向けた途端に、お前は俺の箱をあさろうとするのか！", "俺の宝箱をあさってるだと！？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「この野郎！俺の目を盗んで俺の宝箱を漁るとは！？」
\n";
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
			dialog.text = LinkRandPhrase("旦那、武器をしまってくれ。そいつを見ると落ち着かねえんだ。", "馬鹿が剣を振り回して走り回るのは気に入らねえんだ。しまってくれ。", "剣を抜いたまま走り回ってるなんて、まるで間抜けみたいだぜ。早くしまえよ……");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ああ。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞け、剣をしまえ。みんなが不安がってるぞ。", "バカが剣を抜いて走り回るのは気に入らねえんだ。しまいな。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "ああ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、武器をしまってくれ。落ち着かねえんだ。", "剣を抜いたまま走り回ってるなんて、まるで馬鹿みたいだぜ。しまっとけよ……");
				link.l1 = RandPhraseSimple("すまねえ。", "俺はそれを片付けている。");
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
