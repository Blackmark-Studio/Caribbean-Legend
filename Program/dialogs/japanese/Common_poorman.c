#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "見てください、旦那、面白い小物はいかがですか？安いですよ、ほんの数千ペソで……";
				link.l1 = "ふむ。その「ちっぽけな物」を盗んだんだろう、そして今はそれをどうにかごまかそうとしてるんじゃねえか？";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("こんにちは。私の名前は "+GetFullName(npchar)+"……俺に会えて嬉しいとは思っちゃいねえだろうが、せめて俺の名前くらいは覚えてくれよ……","「ごきげんよう」 "+GetAddress_Form(NPChar)+"。私の名前は "+GetFullName(npchar)+".","私の名前は "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+"。はじめまして。");
				link.l1 = RandPhraseSimple("ごきげんよう。","こんにちは。");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "おい、聞けよ、こんなみすぼらしい施しよりも、何千ペソか稼ぎたくねえか？";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "そのカメオ付きのペンダント……どこで見つけたんだ？";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("「俺がどこまで落ちぶれちまったか、見てくれよ……」","施しで生きるのは楽じゃないんだ……","この貧乏から抜け出せるなら、何だって差し出すぜ！","またお前か……","ブロック",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("なるほどな。まあ、大したことじゃねえよ。","もちろんさ。まあな、歴史上最も偉大な人物は一番貧しかったんだぜ。","だったら、一日中ここで座ってるだけじゃなくて、何か行動を起こしたらどうだ。","あっはっは。もう俺がお前をうんざりさせてるのか？",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("何の用だ？","何の用だ？");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "おい、聞けよ、こんなみみっちい施しよりも、何千ペソか稼いでみねえか？";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "その宝石付きのペンダント……どこで見つけたんだ？";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("何か面白い話を聞かせてくれないか？","町で何か新しいことはあるか？","ああ、最近の噂話を聞きたいんだが…");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("いや、どうして、もうイライラしてるのか？見ての通り、俺は特に忙しくもないんだが…","ただ疲れるだけだ。貧しくても、俺はまだ男だ。");
			link.l1 = "へえ、そうか……";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("「ふむ、」 "+GetAddress_Form(NPChar)+"「お前さんのこと、ひどい噂をたくさん聞くよ。\nでもね、俺は人を信じてるんだ――お前さんみたいな奴でもさ。\nどうか、パンと水のために施しを恵んでくれ、頼む、情けをかけてくれ。」","「お願いだ、」 "+GetAddress_Form(NPChar)+"！お願いです、貧しい男から目をそらさないで、食事のために施しをください…");
				link.l1 = RandPhraseSimple("何もやらねえよ。","金がなくても何とかなるさ。");
				link.l1.go = "exit";
				Link.l2 = "よし、それで一体いくら必要なんだ？";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("お前からか？何もない。","「何もいらねえ」 "+GetAddress_Form(NPChar)+"、ありがとうございます。");
				link.l1 = RandPhraseSimple("ふむ、わかった。","どうやら、お前の人生はそんなに悪くねえみたいだな、相棒。");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "「くだらねえ銅貨一枚でも断らねえぜ。」 "+GetAddress_Form(NPChar)+"…あなたの財布と慈悲が許す限り…";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "弱くて疲れた者を嘲笑うのは罪だ……";
				link.l1 = "ハハハ！俺が金をやると思ったのか、このイカれた乞食野郎！？";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "ありがとうございます "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+"…これでパンが買えるな…";
				link.l1 = "ほら、浮浪者、ちょっと元気つけてこいよ。";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "ありがとうございます。 "+GetAddress_Form(NPChar)+"。これで一週間は食っていけるぜ！";
				link.l1 = "お手伝いできて光栄だったぜ。";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "ありがとうございます。 "+GetAddress_Form(NPChar)+"。あなたのご親切を皆に伝えます！";
				link.l1 = "これは本当に必要じゃない。";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "ありがとうございます、ご尊敬する方 "+GetSexPhrase("旦那","ご婦人")+" "+GetAddress_Form(NPChar)+"……主があなたを見守ってくださいますように……";
				link.l1 = "ああ、奴の加護があれば悪くねえだろう！";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "ありがとうございます。 "+GetSexPhrase("ご高名な旦那","ご高名なご婦人")+" "+GetAddress_Form(NPChar)+"。ご多幸をお祈りします！";
				link.l1 = "ありがとうな、相棒。";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "「聞け、」 "+GetAddress_Form(NPChar)+"、お前、頭がおかしいのか？俺にくれるのは "+FindRussianMoneyString(iTemp)+"！そんな金は受け取れねえ、きっと裏があるんだろう……俺に構うな！";
				link.l1 = "まあ、好きにしな…";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "二万五千受け取った…この金があれば、レリヤと俺は一年間十分に暮らせるぞ！";
				link.l1 = "まずはこの一年を生き延びろ……";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "「聞け、」 "+GetAddress_Form(NPChar)+"、お前、頭がおかしいのか？俺に "+FindRussianMoneyString(iTemp)+"！そんな金は受け取れねえ、きっと裏があるんだろう……俺に構うな！";
				link.l1 = "まあ、好きにしな…";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "馬鹿な質問だな、旦那！もちろんやるさ！でも…俺は何をすればいいんだ？まさか、この美しい笑顔だけでその金をくれるってわけじゃねえだろうな。";
			link.l1 = "もちろん違う。よく聞け。俺は総督閣下ご自身の代理として動いているんだ。閣下は、自分のガレオン船『アラカンタラ』 の進水を、誰かが造船所でわざと妨害しているのではないかと疑っている。 そして最近フランスのスパイが捕まったことで、その疑いはますます強くなったんだ……";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "閣下はすでに船大工の言い訳を聞いたが、本当のことを言っているかどうか確信が持てない。誰が、 なぜ作業を妨害しているのか突き止める必要がある。\n港へ行き、周囲を調べて、作業員たちに「なぜ『アラカンタラ』がいまだに出航できねえんだ？」と聞いてみてくれ…";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "誰にもお前を疑う奴はいねえし、もしかしたらタバコの山まで手に入るかもな。\n俺のことは誰も何も話しちゃくれねえ。みんな俺が誰のために働いてるか知ってるからな。\nもし何か価値のある情報を手に入れたら、三千ペソやるぜ。少なくとも一ヶ月はその“仕事”をやめられる額だろう。";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "三千ペソだと？しかし、尊敬する旦那……";
			link.l1 = "俺と値切り交渉でもしてるのか？ああ、それと、この遅延の黒幕が誰か突き止めたら、さらに二千やるぜ。どうだ？";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "わかったぜ、旦那。そんなに難しくねえはずだ――今じゃ俺の昔の仲間の多くが波止場で働いてるからな。おい、俺も昔は船乗りだったんだぜ。そうだな、 十年くらい前の話だが……";
			link.l1 = "お前の身の上話は後で聞いてやる。夜の十一時過ぎに桟橋で会おう。今は行け。";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			DialogExit();
			AddDialogExitQuestFunction("Trial_Poorman_DlgExit");
		break;
		
		case "trial_6":
			dialog.text = "こんばんは、旦那……";
			link.l1 = "それで？何か分かったか？";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "やったさ、旦那、やったよ。あんたが言ったことと全部合ってるかは分からねえが……金は持ってきたか？五千ペソだ。";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "心配するな。ほら、金だ。さあ、白状しろ。";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "まずは情報だ、それから金だ。さあ、俺の時間を無駄にするな！";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "「俺を騙そうとしてるな、旦那！金を払う気がねえなら、自分で他の奴に頼みに行け。剣に手を伸ばすんじゃねえぞ、 さもないと衛兵を呼ぶからな！」";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Trial_FailPoormanInPort");
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "こういうわけさ。「アルカンタラ」はずっと前から出航の準備ができていたが、 総督自身の命令でわざと積み荷をしていなかったんだ。まあ、そう聞かされたのさ。 今は大工たちがあれこれ細かい作業をしているが、船の出発には影響しない程度のものだ。\nみんなカルタヘナから来るあるバーク船の到着を待っているんだ。実は、「アルカンタラ」 は船長の判断で火薬の備蓄が足りないってことになってる。それで、「プエブラ」が火薬を運んでくるまで、 何日もここに留まっているんだ。\nでも、みんなこの待ち時間は無駄だと思ってるから、もし「プエブラ」が三日以内に来なければ、「アルカンタラ」 は火薬なしで錨を上げることになるだろう……";
			link.l1 = "そうか？それで、誰がそんなことを言ったんだ？名前は？";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "『アルカンタラ』の船乗りの一人――フェリペ・ダビーニョだ…だが、それはまったく秘密じゃねえし、総督閣下ご自身が命じたことだ…";
			link.l1 = "なるほどな。やっぱりそうか。フランスの間者が町にいるってのに、 こいつらは市場の女みたいにペラペラしゃべりやがって、信じられねえ！ どんな新参者でも閣下の計画について好きなだけ知ることができちまう。ああ、 あのフェリペ・ダビーニョは今ごろ本当にヤバいぜ！それに『アラカンタラ』の水夫長もな！ あいつのせいで自分の部下が規律ってもんをまるで知らねえんだ！";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "「ああ……最初から知ってたのか？でも、なぜ……俺のせいじゃない！やれって言ったのはあんただろう！」";
			link.l1 = "お前のせいじゃねえ、気にすることはねえさ、誰もお前を罰したりしねえよ。\nこれでわかっただろう、「アラカンタラ」号の乗組員は、秘密にすべきことまで敵にペラペラしゃべっちまうってな。\nよし、もう行っていいぜ。手伝ってくれてありがとな。\n金でも使ってこいよ。";
			link.l1.go = "trial_11";
			link.l2 = "さらばだ。（殺せ）";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddDialogExitQuestFunction("Trial_KillPoormanInPort");
		break;
		
		case "trial_11":
			DialogExit();
			AddDialogExitQuestFunction("Trial_PeacePoormanInPort");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "失礼します、旦那……これは見知らぬ奴とのサイコロ勝負で手に入れたんです。お守りか何かで病気が治ると思ったんですが、間違いでした……病気は治らないし、市場の商人たちも興味を示しません。そんな時、あなたが現れた――水夫であり、船長であり、学のあるお方。これを見てください、もしかしたらあなたには役立つかもしれません。\nあなたにとってはこの二千ほどの金は大した額じゃないでしょうが、私には一か月分のパンとラムの一口なんです。 頼みますよ、旦那……";
			link.l1 = "よし、見せてくれ…";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "「ここに…」";
			link.l1 = "まあまあ……面白い品だな、同感だぜ。きっとインディアンの集落から盗まれたものに違いねえ。よし、買ってやる。これが金だ。";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "ありがとうございます、旦那！これがあなたに幸運をもたらしますように！主のご加護がありますように！";
			link.l1 = "幸運を祈るぜ、相棒。酒場で一度に全部使っちまうなよ。";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "「えっ、」 "+GetAddress_Form(NPChar)+"、なんでそんな古いガラクタにこだわるんだ？";
			link.l1 = "俺のブーツでてめえの間抜けな頭を蹴っ飛ばしてやれば、なんで俺が気にしてるか一発でわかるぜ。";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "このペンダントはベッツィ・プライスのものだったんだ。で、どこで見つけたんだ？";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "「ランタンのある家の近くに落ちていたんだ」 "+GetAddress_Form(NPChar)+"。荒くれ者のブーツで泥に踏みつけられていた。しかし、あの家には長い間誰も住んでいなかったから、 俺は持ち主がいないと判断したんだ…";
			link.l1 = "ふむ……";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "「ランタンのある家の近くに落ちていたんだ」 "+GetAddress_Form(NPChar)+"…荒くれ者のブーツで泥の中に踏みつけられていたんだ。しかし、あの家には長いこと誰も住んでいなかったから、 俺はもう見捨てられた家だと判断したんだ…";
			link.l1 = "ふむ……";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
