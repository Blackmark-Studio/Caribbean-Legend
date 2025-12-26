// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴り響いていて、みんながお前を探している。俺だったら、そこには留まらねえな。","街の衛兵たちがみんなお前を探して町中を捜索している。俺は馬鹿じゃねえ、だからお前とは話さないぞ！","走れ "+GetSexPhrase("相棒","娘")+"……兵士たちに蜂の巣にされる前に……"),LinkRandPhrase("何のご用ですか、 "+GetSexPhrase("悪党","悪党")+"「！？　街の衛兵たちはもうお前の匂いを嗅ぎつけてる、そう遠くへは行けねえぞ、」 "+GetSexPhrase("汚い海賊","殺人鬼のクズ")+"!","汚らわしい殺人者め、今すぐ私の家から出て行け！衛兵！","「俺はお前なんか怖くねえ」 "+GetSexPhrase("忍び寄る","くせえ野郎")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には何の問題もねえさ……","奴らに俺は絶対に捕まらねえ。"),RandPhraseSimple("「黙れ、この野郎」 "+GetWorkTypeOfMan(npchar,"")+"、さもないとその汚い舌を引き抜いてやるぞ！！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"、そしてそこにいる全員が海賊を捕まえに来てるんだぜ！いいか、相棒、俺が言っておく。 おとなしくしてりゃ命は助かる……"));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("おい、この野郎！好き勝手に奪えると思ってるのか？絶対に許さねえ！\nお前ら！武器を取れ！このイカれ野郎をぶった斬れ！","何か欲しいなら買え、この野郎！今からお前に思い知らせてやるぜ！おい、みんな、武器を取れ！警戒しろ！");
				link.l1 = RandPhraseSimple("え？何だ？","えっ、なんでこんなことをするんだ？");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "ヨーロッパ産のワインを五十本か六十本ほどまとめて購入したいのですが、在庫は十分にあると伺いました。"; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "またお会いしましたね。この手紙をご覧ください――これで私にワインを売ることについて再考していただけませんか？"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "また俺だ。中断していたワインの取引を再開できるか？金は十分に用意したぜ。"; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "何かお買い求めですか、旦那？";
				Link.l1 = "もちろんだ、店ってのはそのためにあるんだろ？商品を見せてくれ。";
				Link.l1.go = "trade_1";
				Link.l2 = "特別な商用で来たんだ……";
				Link.l2.go = "quests";
				Link.l3 = "申し訳ないが、行かなくてはならない。";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "聞いてくれ、旦那、俺は仕事を探してるんだ。常勤とか荷物運びじゃなくて、いわば使い走りみたいな感じだ。 何か手伝いが必要だったりしないか？";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "お使いは終わったぜ。グララム・ラヴォワを見つけた。";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "新しい助手を紹介します、旦那。";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "また俺だ、旦那。報酬をもらいに来たぜ。";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "これらのイヤリングを見てください、旦那。ジャングルで倒された盗賊の死体から見つけたんです。 これは明らかに腕の良い宝石職人の作で、きっとこの辺りのものではありません。 何かこのイヤリングについてご存知ですか？";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "船長、助けてくれてありがとう。";
				Link.l1 = "「ああ、どういたしまして。」";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "どうしたんだい、船長？何か失くしたのか？なんでうちの店の中をそんなにウロウロしてるんだ？";
				Link.l1 = "へえ、驚いたな――実はやったんだぜ！あの忌々しいジェラール・ルクロワはどこにいる？ フロリアン・ショークから与えられた任務は全部果たしたんだ、 サメに丸呑みにされてもおかしくねえくらい苦労したってのによ！それなのに、報酬を受け取りに来たら、 あの野郎はもうとんずらかよ！";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "どう言えばいいか……失くしてしまったんだ。\n私の依頼人を見かけなかったか？名前はジェラール・ルクロワだ。";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "船長、お願いがあるんだ。手を貸してくれるか？";
				link.l1 = "ご用件は何でしょうか？"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("はじめまして、旦那！この地には初めていらしたのですか？","ようこそ、船長！俺の店はいつでも旦那のためにあるぜ。","旦那、どうぞお入りください！この諸島で手に入る最高の商品を喜んでご用意いたします。"),LinkRandPhrase("おお、船長旦那！フランス植民地中で最高の品々が、今ここに、そしてあなただけのために揃っております！","なんと嬉しいお出会い、旦那！最高級のフランス商品を揃えた一流の店が、あなたのお役に立ちますぞ！","以前お会いしましたかな、船長旦那？ご存じの通り、私の店は本国の一流店にも劣らぬ素晴らしさですよ！"),LinkRandPhrase("おお！旦那船長！私の店にお越しいただき、本当に嬉しいです！","スペイン植民地随一の店へ、これほど優秀なカバジェロをお迎えできて光栄です！","おお、高貴なるイダルゴ殿！運命があなたを私のつつましい店へと導いてくれました！ ここではご所望の品が何でも見つかりますぞ！"),LinkRandPhrase("ごきげんよう、旦那船長。こちらへは初めてのご来訪でしょうか？","こんにちは、旦那。ここは初めてですかな？うちのオランダ産の商品はきっとご満足いただけますぞ！","どうぞお入りください、船長旦那！最高品質の商品を最安値でご提供――それがオランダ流の商売ですぞ！"));
			Link.l1 = LinkRandPhrase("こちらこそ、はじめまして。私の名前は "+GetFullName(pchar)+" 俺はこの地に来たばかりなんだ。さて、群島の財宝を見せてくれよ！","こちらこそ、はじめまして。私は "+GetFullName(pchar)+"「』の船長"+pchar.ship.name+"「。それで、今のおすすめ商品は何だ？」",""+GetFullName(pchar)+"、「『」の船長"+pchar.ship.name+"、お会いできて嬉しいです。さて、私に何を提供してくれますか？");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "ヘレン船長！いつもお会いできて嬉しいです。";
				link.l1 = "私もあなたに同じ気持ちです、ありがとう。";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴り響き、皆がお前を探している。俺なら、そこには留まらないぜ。","街の衛兵たちがみんなお前を探して町中を捜索しているんだ。俺は馬鹿じゃねえ、だからお前とは話さねえぞ！","「走れ」 "+GetSexPhrase("相棒","娘")+"……兵士たちに蜂の巣にされる前に……"),LinkRandPhrase("何のご用ですか、 "+GetSexPhrase("ろくでなし","悪党")+"？！もう街の衛兵に嗅ぎつけられてるぞ、お前はそう遠くへは行けねえ、 "+GetSexPhrase("汚い海賊","殺人狂のクズ")+"!","汚らわしい殺人者め、今すぐ私の家から出て行け！衛兵！","「俺はお前なんか怖くねえ」 "+GetSexPhrase("忍び寄る","くさい野郎")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には問題じゃねえ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("「黙れ」 "+GetWorkTypeOfMan(npchar,"")+"、さもないとその汚い舌を引き抜いてやるぞ！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"、そしてそこにいる全員が海賊を捕まえに来てるんだ！いいか、相棒、俺が言ってやるよ： おとなしくしてりゃ死なずに済むぜ…"));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "申し訳ありませんが、今はあなたに構っている時間がありません。";
				link.l1 = "ええ、もちろんです。また別の機会に立ち寄りますね。";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "船長、助けてくれてありがとうございます。";
				Link.l1 = "「ああ、どういたしまして。」";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "どうしたんだい、船長？何か失くしたのか？なんでうちの店の中をそんなに走り回ってるんだ？";
				Link.l1 = "なんと、実は本当にやったんだぜ！あの忌々しいジェラール・ルクロワはどこにいる？ フロリアン・ショークから与えられた任務は全部果たしたんだ、サメに丸呑みされてもいいくらい、 くそ大変だったんだぞ！それなのに、報酬を受け取りに来たら、あの野郎はもうどこかへ飛んじまってるじゃねえか！\n";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "どう言えばいいか……迷子なんだ。私の依頼人を見かけなかったか？名前はジェラール・ルクロワだ。";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "船長、お願いがあるんだ。力を貸してくれるか？";
				link.l1 = "ご用件は何でしょうか？"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("おや、誰かと思えば！まあ、金に臭いはないって言うしな、入ってくれ、船長、さあ取引しようじゃねえか…","「お会いできて嬉しいとは言えません」 "+GetFullName(pchar)+"…しかし、まだあなたと取引はできます。","へへ……まあ、家には招待しませんが、船長、私の店ならいつでもご利用ください。"),LinkRandPhrase("おや、誰かと思えば！あれは "+GetFullName(pchar)+"！取引したいのか、それともタダで何か持っていくつもりか？おいおい、冗談だよ……","「ここで会えて嬉しいとは言えねえな」 "+GetAddress_Form(NPChar)+"。しかし金を使う余裕があるなら――どうぞ、中へ、中へ……","取引をしたいのか、船長 "+GetFullName(pchar)+"？もしそうなら、どうか早くしてもらえませんか？他のお客様があなたを避けていて、商売に差し支えますので。"),LinkRandPhrase("取引はいかがですかな、旦那？少々お待ちを、今お金を数えますので――ご存じの通り、世の中には怪しい連中もいますからな……もちろん、船長、あなたのことではありませんぞ！","もし大海原でお前を見かけたら、 "+GetAddress_Form(NPChar)+"……もっと帆を注文したいところですが……しかし、ここ私の店では、取引を提案できます。","船長、最初に言っておくぜ。もし布に血の染みがあったり、コーヒーが火薬臭かったりしたら、俺は引き取らねえ。 それ以外なら、見て選んでくれ。")),LinkRandPhrase(LinkRandPhrase("「そしてまたお会いできて嬉しいです」 "+GetAddress_Form(NPChar)+"！買いでも売りでも――いつでもお力になりますよ。","「お願いです、」 "+GetAddress_Form(NPChar)+"、いらっしゃい！いつもご贔屓にしてくれるお客様が来てくれて嬉しいよ。さて、今回はどうする？買うのか、 それとも売るのかい？","「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！またお会いできて本当に嬉しいです！今回は何になさいますか、買い取りですか、それとも売却ですか？"),LinkRandPhrase("「うちの商品はお気に召しますか、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"？いつでもお力になりますので、ご覧になってお選びください。","「こんにちは」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"。またお会いできて嬉しいです！商品を見ていかれますか？","お会いできて嬉しいです、船長！当店の高品質な商品をきっと気に入っていただけると思っていました。 新しい品もご覧になりますか？"),LinkRandPhrase("「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！どうぞお入りください！すべての商品はあんたのために用意してあります――しかも今回は大幅値引きですよ！","Captain "+GetFullName(pchar)+"、またお越しいただき嬉しい限りです！どうぞ、お好きなものをお選びください！","今回は何をお求めですか、船長？まだ私の店を覚えていてくださって嬉しいです。必要な品はすべて揃っています――最高品質ですよ！")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("そんな迎え方かよ、相棒？まあ、海で会ったときは覚えておくぜ……\n震えるなよ、冗談だって。さあ、品物を見せてくれ。","わかったぜ、相棒。お前の品は必要かもしれねえが、お前の口は要らねえ。黙っていられるか？それとも手伝いが必要か？ 黙って商品を見せろ。"),RandPhraseSimple("商売の話に入ろうぜ、商人。お前と士気の話なんてしてる暇はねえ、まともな取引だけしようじゃねえか。","落ち着けよ、相棒。冗談はいいが、俺だって怒ることもあるんだぜ……だから、これ以上俺を苛立たせるのはやめて、さっさと商品を見せてくれ。")),RandPhraseSimple(RandPhraseSimple("いつもお前の店に来るのは楽しいぜ、相棒。俺の目を引くような品は何かあるか？","会えて嬉しいぜ、相棒。さて、何か新しい話はあるか？何ヶ月も陸に上がってない海の放浪者にとってさ。"),RandPhraseSimple("そしてまた、私はいる "+XI_ConvertString("Colony"+npchar.City+"Acc")+"！ここにいなくてよかったぜ、忘れるところだったからな。だが、 あんたの倉庫にはまだ俺のために残ってる物があるのか？全部片付けちまったのか？","どうして来なかったんだ？お前はいつもあいつより俺を満足させてくれるのにな。さて、そこに何を持ってきたんだ？")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("全員、甲板に集まれ！ ","検査を行え！ ")+LinkRandPhrase("「何をする」 "+GetSexPhrase("旦那","旦那、あっ、失礼――ご婦人でしたか")+" 俺の店で運命を試したいのか、へへ？","なんとまあ、貧乏な年寄り商人には驚きじゃのう！へへっ！","さて、どんな順風に乗って私の店に来られたのですか？"),LinkRandPhrase("港を開け！","横にフックをかけろ！","まっすぐ進め！")+RandPhraseSimple(" ここでは見つかります"," 私の店には")+LinkRandPhrase(" 島中で一番の値段だ。"," 素晴らしい品揃えだ。"," 最高品質の品物をご用意しております。")+RandPhraseSimple(" お役に立てます"," ご要望のままに")+"「船長！」"),pcharrepphrase(RandPhraseSimple("何か商品は "+GetSexPhrase("諸君","紳士淑女の皆さん")+" 運命のいたずらだぜ！へっへっ！奴らが太陽の下で吊るされて干されるまでな！","港では吊るされた男たちが風に揺れ、鎖の音が運ばれてくる。\nだが、金に臭いはねえだろ？"),"「～なさいますか」 "+LinkRandPhrase("「最高級の品を買う」 "+NationNameGenitive(sti(NPChar.nation)),"積荷の売買","儲かる積み荷はあるか？")+RandPhraseSimple("？ご用命とあらば、喜んでお仕えします！","？私の店はあなたのためにございます！")+RandPhraseSimple(" お会いできて嬉しいです"," 好きにしな。")+"「船長！」")),NPCharRepPhrase(npchar,pcharrepphrase("俺の忠告が欲しいなら、船長――ぶどう弾には金を惜しむな。\n死んじまった奴らのほうが、ずっと楽に漁れるからな！","「あなたが～であることにはすぐに気づいた」 "+GetSexPhrase("抜け目のない相棒","小賢しい娘")+". "+RandPhraseSimple("しかし今は、あなたが本物の "+GetSexPhrase("英雄","命知らず")+".","若いが "+RandPhraseSimple("油断しないようにな。","あなたは確かに簡単には騙されませんね。"))),pcharrepphrase("拿捕した賞品からの積荷はすべて買い取ってやるぜ。支払いは銀がいいか、それとも金がいいか？ その手の品はいつだって高値だぜ。","商業航海は儲かる商売ですよ、船長 "+GetFullName(pchar)+"、そうだろう？")),NPCharRepPhrase(npchar,RandPhraseSimple("奴らをみんな本帆のシートで包み、\n二十回もロープを巻きつけて、\nそいつらを持ち上げて海の向こうへ放り投げたんだ！ ",RandPhraseSimple("「死人の胸に十五人の男！」","酒と悪魔が他の連中をみんな地獄に送っちまったんだぜ！")+" ヨーホーホー、ラム酒一本だぜ！ ")+RandPhraseSimple("どうしたんだ、船長？","何かお探しですか、船長？"),pcharrepphrase("なかなかの値切り上手ですね、船長 "+GetFullName(pchar)+"。常連のお客様ですので、とても良い価格をご提供いたします！","「了解だ、船長」 "+GetFullName(pchar)+"、あなたに敬意を表して、ほんの少しだけ多くお出しできます！何をご希望ですか？")),NPCharRepPhrase(npchar,"誓って言うが、お前と話してると気分が悪くなるぜ。 "+LinkRandPhrase("ピーナッツを少し買っていけ。豚はそういうものが大好きなんだ。 ","ここで誰かがラム酒でお前のブーツを磨いてくれるとでも思ってるのか？ ",pcharrepphrase("お前みたいな奴は分かってるぜ。ラムで酔っ払って、そのまま絞首台行きだ。","お前の母親はどうしてお前を船乗りにさせたんだろうな！船乗りだぞ！仕立屋のほうがよっぽど向いてるってのに…")),pcharrepphrase(RandPhraseSimple("そう思った ","そう願っていた ")+RandPhraseSimple("あなたはもう二度と我々の島に戻らないものと思っていた。","もう二度とあなたに会えないと思っていました。")+RandPhraseSimple(" 死者たちが首に重しのようにぶら下がっているんだな……"," お前は一体何人の船乗りをサンゴの間に見捨ててきたんだ！？"),"Captain "+GetFullName(pchar)+"、あなたの商売への情熱は私の期待をすべて超えました！"+RandPhraseSimple(" 出航前に最後の買い物をしておきたいかい？"," 何か特別なものをお探しか？"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("おや、誰が来たかと思えば！まあ、金に匂いはないって言うしな、入ってくれ、船長、さあ取引しようじゃねえか…","「お会いできて嬉しいとは言えません」 "+GetFullName(pchar)+"…しかし、まだあなたと取引はできます。","へへ……まあ、家には招待しませんが、船長、私の店ならいつでもご利用いただけますよ。"),LinkRandPhrase("おや、誰かと思えば！あれは "+GetFullName(pchar)+"！取引したいのか、それともタダで持っていきたいのか？\nおいおい、冗談だよ……","「ここで会えて嬉しいとは言えねえな」 "+GetAddress_Form(NPChar)+"……しかし、お金を使う気があるなら――どうぞ、中へ、中へ……","取引したいのか、船長 "+GetFullName(pchar)+"？もしそうなら、どうか手早くお願いします。他のお客様があなたを避けていて、私の商売に差し支えますから。"),LinkRandPhrase("取引はいかがですかな、旦那？少々お待ちを、今お金を数えますので――この辺りには怪しい連中もおりますからな……もちろん、"+pchar.name+"船長、あなたのことではありませんぞ！","もし大海原でお前を見かけたら、 "+GetAddress_Form(NPChar)+"……もっと帆を注文したいところだが……しかし、ここ、私の店では取引を提案できる。","船長、最初に言っておくぜ。もし布に血の染みがあったり、コーヒーが火薬臭かったりしたら、俺は引き取らねえ。 そうでなけりゃ、見て選んでくれ。")),LinkRandPhrase(LinkRandPhrase("「またお会いできて嬉しいです」 "+GetAddress_Form(NPChar)+"！買いでも売りでも、いつでもお力になりますよ。","「お願いです、」 "+GetAddress_Form(NPChar)+"、いらっしゃい！いつもお気に入りのお客様にお会いできて嬉しいです。今回はご購入ですか、それともご売却ですか？","「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！またお会いできて本当に嬉しいです！今回はどうなさいますか、買い取りですか、それとも売却ですか？"),LinkRandPhrase("「うちの商品はお気に召しますか、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"？いつでもご用命ください――ご覧になって、お選びください。","「こんにちは。」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"。またお会いできて嬉しいです！当店の商品をぜひご覧になりませんか？","お会いできて嬉しいです、船長！うちの高品質な品物をきっと気に入っていただけると思っていました。 新しい商品をご覧になりますか？"),LinkRandPhrase("「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！どうぞ、お入りください！すべての商品はあんたのために用意してあるぜ――しかも今回は大幅値引きだ！","Captain "+GetFullName(pchar)+"、またお越しいただき嬉しい限りです！どうぞ、お好きなものをお選びください！","今回は何をお求めですか、船長？まだ私の店を覚えていてくださって嬉しいです。必要な品はすべて揃っております――最高品質ですよ！")));
					link.l14 = "聞いてくれ、これからポルトベロへ出発するところなんだが、 お前からコーヒーとカカオをそれぞれ三百ユニットずつ仕入れたいんだ。\n"; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("おや、誰が来たかと思えば！まあ、金に匂いはないって言うしな、入ってくれ船長、さあ取引しようじゃねえか…","「お会いできて嬉しいとは言えません」 "+GetFullName(pchar)+"…しかし、まだあなたと取引はできます。","へへ……まあ、家にはお招きできませんが、船長、私の店ならいつでもご利用いただけますよ。"),LinkRandPhrase("おや、あそこにいるのは誰だ！？あれは "+GetFullName(pchar)+"！取引したいのか、それともタダで持っていきたいのか？おいおい、冗談だって……","「ここで会えて嬉しいとは言えねえな」 "+GetAddress_Form(NPChar)+"。しかし、お金を使う気があるなら――どうぞ、中へ、中へ……","取引をご希望ですか、船長 "+GetFullName(pchar)+"？もしそうなら、どうか早くしてもらえますか？他のお客があなたを避けていて、商売に差し支えるんです、"),LinkRandPhrase("取引はいかがですか、旦那？少々お待ちください、今お金を数えます――ご存知の通り、この辺りには怪しい連中もいますので……もちろん、"+pchar.name+"船長、あなたのことではありませんよ！","もし大海原でお前を見かけたら、 "+GetAddress_Form(NPChar)+"……もっと帆を注文したいところだが……まあ、ここ私の店では、取引を提案できるぞ。","船長、最初に言っておくぜ。布に血の染みがあったり、コーヒーが火薬臭かったりしたら、俺は引き取らねえ。 それ以外なら、見て選んでくれ。")),LinkRandPhrase(LinkRandPhrase("「またお会いできて嬉しいです」 "+GetAddress_Form(NPChar)+"「買いでも売りでも――いつでもお手伝いできて嬉しいですよ。」","「お願いします」 "+GetAddress_Form(NPChar)+"、いらっしゃい！お気に入りのお客様にまたお会いできて嬉しいですよ。今回はどうされますか――ご購入ですか、それともご売却ですか？","「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！またお会いできて本当に嬉しいです！今回は何になさいますか――ご購入ですか、それともご売却ですか？"),LinkRandPhrase("「うちの商品はお気に召しますか、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"？いつでもお役に立ちますよ。ご覧になって、お選びください。","「こんにちは。」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"。またお会いできて嬉しいです！当店の商品をぜひご覧になりませんか？","お会いできて嬉しいです、船長！当店の高品質な商品をきっと気に入っていただけると思っていました。 新しい品もご覧になりますか？"),LinkRandPhrase("「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！どうぞ、お入りください！すべての商品はあんたのために用意してあるぜ――しかも今回は大幅値引きだ！","Captain "+GetFullName(pchar)+"、またお越しいただき嬉しい限りです！どうぞ、お好きなものをお選びください！","今回は何をご所望ですか、船長？まだ私の店を覚えていてくださって嬉しいです。必要な品はすべて揃っております——最高品質ですよ！")));
				link.l14 = "俺はコーヒーとカカオを買いに来たんだ。 "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("「持ち物を見せてくれよ、年寄りの海賊！」","ちょっとあんたの商品を見せてもらいたかっただけだ、旦那。"),pcharrepphrase("「俺は絞首台に誓うぜ、」 "+GetFullName(npchar)+"、俺をはぐらかすつもりか！今すぐ商品を見せろ！","「お前の品物を見せてもらおう」 "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("それは間違いねえな！死んじまった奴らは噛みつきやしねえ！さて、船倉には何があるんだ？","さあ、旦那、早く用事を済ませたほうがいいぜ。どんな品物を俺に見せてくれるんだ？"),pcharrepphrase("いつかお前が俺の戦利品になる日が来るぜ、へっへっ。冗談だ。商品を見せてくれ。","「我々の商談について話し合いましょう。」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("俺が何を欲しいって？何か買いたいんだよ！","「酒を飲みすぎると墓場行きだぞ」 "+GetFullName(npchar)+"。あなたの商品を見せてほしい。"),pcharrepphrase("お前の割引なんて知ってるぜ！三ポンド分の値段でカカオ二ポンドだろうが！さあ、商品を見せてくれ。","それはいつだって良いことだ。さあ、値段交渉といこうじゃねえか。")),"品物を見せてくれ。余計なことは言わなくていい、早いほうがいいんだ。俺は急いでるんだぜ。",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("ああ、誰かを刺したくてたまらねえぜ。さて、本題に入ろうか。","他の用件に取りかかろうか、旦那。"),pcharrepphrase("カランバ！俺は別の用事で来たんだぜ！","「特別な取引について話がしたいんだ。」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("お前に用があるんだぜ、年寄りの海賊！","さあ、本題に入ろうぜ、相棒！"),pcharrepphrase("悪魔に誓って、俺はお前なんぞに騙されねえぞ、この野郎！他にもお前と片付ける用があるんだ！","「まったく同感だ」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"、他にもあなたと話したいことがありました。")),NPCharRepPhrase(npchar,pcharrepphrase("もう積み込みは終わったのか？お前と話があるんだ。","俺は取引のためにここへ来たんじゃねえ、旦那。別の用事があるんだ。"),pcharrepphrase("そんな値段じゃ雷に打たれてしまえ！用があって来たんだ。","「割引はいつでも嬉しいものだな」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"、しかし他にもあなたに用があるんだ。")),NPCharRepPhrase(npchar,pcharrepphrase("黙れ、この酔っぱらいのじじい、俺はお前に用があるんだ","ラムで気分が悪いんだろうな。俺もお前のことが特別好きってわけじゃねえ。さて、本題に入ろうぜ。"),pcharrepphrase("もうすでに俺からぼったくっただろ、この悪党め！お前とはまだ用があるんだ。","皮肉は不適切だ。お前には他の用件があるんだ。")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("まずは商売、それから楽しみだ。ちょっと聞きたいことがあるんだ。","今は違う。情報が必要だ。"),pcharrepphrase("てめえの値段なんざ知るか！まずは俺が知りたいことを全部話してもらうぜ。","喜んでお受けします。ちょっとお聞きしたいことがありまして。")),NPCharRepPhrase(npchar,pcharrepphrase("助言ありがとうよ、年寄りの殺し屋。ちょっと聞きたいことがあるんだ。","特別にお聞きしたいことがありました。"),pcharrepphrase("金は後回しでいい。ちょっと聞きたいことがあるんだ。","はい、同感です。あなたに聞きたいことがありました。")),NPCharRepPhrase(npchar,pcharrepphrase("私が何を聞こうとしていたか、あなたにはお分かりだと思います。","私の質問に答えていただけると期待しています。"),pcharrepphrase("値札以外に何か考えられることはあるか？というのも、それについて聞こうと思ってたんだ。","それには興味がない。俺が必要なのは情報だ。")),NPCharRepPhrase(npchar,pcharrepphrase("あんまり興奮するなよ、相棒！ちょっと質問しようと思っただけだ。","あまり興奮しすぎると卒中を起こすぞ。質問を一つだけ答えてくれれば、俺はすぐに立ち去る。"),pcharrepphrase("お前に気の利いたことを言えなんて期待しちゃいねえよ、ゴキブリ並みの脳みそしかねえんだからな。だが、 何かは知ってるはずだろう。","長くは引き止めません。ひとつだけ質問があります。")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "別件で来たんだ。";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "私は町から価格表を持ってきました "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "ヨーロッパ産のワインを一括で購入したいのですが――50本か60本ほど。あなたの店には十分な在庫があると聞きましたが……。"; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "またお会いしましたね。どうぞ、この手紙をご覧ください――これで私にワインを売ることについて、ご再考いただけませんか？"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "また俺だ。中断してたワイン取引を再開できるか？金は十分に用意したぜ。"; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "聞いてくれ、旦那。俺は仕事を探してるんだ。常勤や重い荷物運びじゃなくて、いわば使い走りみたいなものさ。 何か手伝いが必要だったりしないか？";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "お使いは済ませたぜ。グララム・ラヴォワを見つけた。";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "新しい助手を紹介します、旦那。";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "また私です、旦那。報酬を受け取りに来ました。";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "こちらのイヤリングをご覧ください、旦那。ジャングルで倒された盗賊の遺体から見つけたものです。 これは明らかに腕の良い宝飾職人の作で、きっとこの辺りのものではないでしょう。 何かこのイヤリングについてご存じありませんか？";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "こんにちは、あなたの息子さんの招待で参りました。"; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "これはあなたの娘さんのことですが…";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("じゃあな、酔っぱらいのじじい。","良い一日を。 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("カランバ！どこにも行くなよ、すぐ戻るからな。","ここに来てくれて嬉しかったよ、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"！さようなら！")),NPCharRepPhrase(npchar,pcharrepphrase("錨を上げろ！","さようなら、旦那。"),pcharrepphrase("おい！そこに何を隠してるんだ？ラムか？違うのか？まあいい、喉を潤しに行くぜ。","申し訳ありませんが、町で急用があるのです。")),NPCharRepPhrase(npchar,pcharrepphrase("へっ！じゃあな！","俺は行かなくちゃならねえ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("俺に口答えしようなんて思うなよ！こんなことで時間を無駄にしてる暇はねえんだ！","そろそろ自分の船で何が起きているか見に行くべきかもしれないな。では、さらば。 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("どうしたんだい、旦那？俺だよ―― "+GetFullName(pchar)+"「寝て頭を冷やせ、後でまた来るぜ。」","またお前に会いに来る前に、肝臓が先にお前をやっちまいそうだな。"),pcharrepphrase("ギニーやドゥブロンを数え続けてな、年寄りの狐め！また来るぜ。","会えて嬉しかったよ "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "ご用件は何ですか？レインボウ号の補給、それとも戦利品の売却でしょうか？今儲かる積荷には興味ないでしょうな、 はは。";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("何を持ってるか見せてみろよ、この老いぼれ海賊め！","ちょっとあなたの商品を見せてもらいたかっただけですよ、旦那。"),pcharrepphrase("「絞首台にかけて誓うぜ、」 "+GetFullName(npchar)+"「俺を無視させねえぞ！今すぐ商品を見せろ！」","「お前の品物を見せてもらおう」 "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("それは間違いねえな！死んじまった奴らは噛みつきやしねえ！さて、お前の船倉には何があるんだ？","旦那、早く商売に取りかかったほうがいいぜ。どんな品物を見せてくれるんだ？"),pcharrepphrase("いつかお前が俺の戦利品になる日が来るぜ、へっへっ。冗談だ。商品を見せてくれ。","「我々の商談について話し合いましょう。」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("俺が何を欲しいかって？何か買いたいんだよ！","「酒を飲みすぎると墓場行きだぞ」 "+GetFullName(npchar)+"。あなたの商品を見せてほしい。"),pcharrepphrase("お前の割引なんて知ってるぜ！三ポンド分の値段でカカオ二ポンドだろう！さあ、商品を見せてくれ。","それはいつだって良いことだ。では、値段交渉といこうか。")),"品物を見せてくれ。余計なことは言わなくていい、早い方がいいんだ。俺は急いでるんだぜ。",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("ああ、誰かを刺したくてたまらねえ。さて、仕事に取りかかるとするか。","他の商談に入りましょうか、旦那。"),pcharrepphrase("カランバ！俺は別の用事で来たんだぜ！","「特別な商談について話がしたいんだ」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("「お前に用があるんだ、年寄り海賊！」","さあ、本題に入ろうぜ、相棒！"),pcharrepphrase("悪魔に誓って、俺は騙されねえぞ、この野郎！お前には他にも用があるんだ！","「まったく同感です」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"、他にも話したいことがあったんだ。")),NPCharRepPhrase(npchar,pcharrepphrase("もう積み込みは終わったのか？お前と取引があるんだ。","俺は取引のために来たんじゃねえ、旦那。別の用事があるんだ。"),pcharrepphrase("そんな値段じゃ雷に打たれてしまえ！お前と商談があるんだ。","「割引はいつだって嬉しいものだな」 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"、しかし他にもあなたに用があるんだ。")),NPCharRepPhrase(npchar,pcharrepphrase("黙れ、この酔っ払いの爺、用があって来たんだ","ラムで気分が悪いんだろうな。俺もお前が特別好きってわけじゃねえ。さて、本題に入ろうぜ。"),pcharrepphrase("もうすでに俺をだましやがったな、この野郎！お前とはまだ用があるんだ。","皮肉は不適切ですよ。他にもあなたに用があるんです。")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("まずは商売、それから楽しみだ。ちょっと聞きたいことがあるんだ。","今は無理だ。情報が必要なんだ。"),pcharrepphrase("てめえの値段なんざくそくらえだ！まずは俺が知りたいことを全部話してもらうぜ。","喜んでお受けします。ちょっとお聞きしたいことがありまして。")),NPCharRepPhrase(npchar,pcharrepphrase("助言ありがとうよ、年寄りの殺し屋。ちょっと聞きたいことがあるんだ。","特別に聞きたいことがあったんだ。"),pcharrepphrase("金のことは後回しだ。ちょっと聞きたいことがあるんだ。","はい、同感です。あなたにお聞きしたいことがありました。")),NPCharRepPhrase(npchar,pcharrepphrase("私が何を尋ねようとしていたか、あなたは分かっていると思います。","私の質問に答えていただけると嬉しいです。"),pcharrepphrase("値札以外に何か考えられるか？というのも、まさにそのことを聞こうと思ってたんだ。","それには興味がない。俺が欲しいのは情報だ。")),NPCharRepPhrase(npchar,pcharrepphrase("あんまり興奮するなよ、相棒！ちょっと質問しようと思っただけだ。","あまり興奮しすぎるなよ、脳卒中を起こすぞ。質問を一つだけ答えてくれれば、すぐに立ち去る。"),pcharrepphrase("お前の頭はゴキブリ並みだから、気の利いたことを言えとは期待してねえよ。\nだが、何かは知ってるはずだろう。","長くは引き止めません。ひとつだけ質問させてください。")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("じゃあな、酔っ払いのじじい。","良い一日をお過ごしください。 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("カランバ！どこにも行くなよ、すぐ戻るからな。","ここに来てくれて嬉しかったよ、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"「！さようなら！」")),NPCharRepPhrase(npchar,pcharrepphrase("錨を上げろ！","さようなら、旦那。"),pcharrepphrase("おい！そこに何を隠してやがる？ラムか？違うのか？なら、俺は喉を潤しに行くぜ。","申し訳ありませんが、町で急用があるのです。")),NPCharRepPhrase(npchar,pcharrepphrase("へっ！じゃあな！","俺は行かなくちゃならねえ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("俺に口答えなんてするんじゃねえぞ！こんなことで時間を無駄にしてる暇はねえんだ！","そろそろ自分の船で何が起きているか見に行くべきかもしれないな。では、さらばだ。 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("どうしたんだい、旦那？俺だよ―― "+GetFullName(pchar)+"！酔いをさませ、また後で来るぜ。","またお前に会いに来る前に、肝臓が先にお前をやっちまいそうだな。"),pcharrepphrase("ギニーやドゥブロンを数え続けてな、年寄りのキツネ野郎！また来るぜ。","お会いできて嬉しかったです。 "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "申し訳ありませんが、今はとても忙しいのです。お客様が多くて！また明日お越しください。";
				link.l1 = "「おや、本当かい？それじゃあ、また後で来るとするか。」";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("丸玉、帆布、薬、上質な木材、その他の商品も取り揃えております！何にご興味がありますか？","砂糖や香辛料を買いたいのか？それともラム酒や火薬か？");
			link.l1 = pcharrepphrase(LinkRandPhrase("俺の船倉には戦利品が山ほどあるぜ！金に匂いなんてねえだろ？","俺の船倉の戦利品を全部降ろして、お前の金でいっぱいにしてやるぜ。ははっ！","ああ、お前が満杯のドゥブロン金貨一袋のためなら母親でも売る奴だってことは知ってるぜ！だが、 俺はただ補給品を補充したいだけなんだ。"),LinkRandPhrase("俺の積み荷を売って、補給品を補充したいんだ。","販売用の商品を購入したい。","大砲の弾や爆弾、そういったものを見せてくれ。"));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "私の会計士が必要な買い物をすべて行います…";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("取引せずに出ていくぜ。またな！","俺はちょっと一杯引っかけてくるぜ。お前はそこにいろ！"),RandPhraseSimple("今は取引の時間がないんだ。では、失礼する。","申し訳ありません、急用があるので失礼します。さようなら！"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "お話をうかがいましょう。";
			link.l1 = "逃亡者を連れてきたぞ。";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "ああ、船長、本当にありがとうございます！彼女はどうですか？怪我はしていませんか？ あのいたずら娘が家出してからもう一日経ちましたよ。私が彼女に危害を加えるように見えますか？ ちゃんと夫を見つけてやったんです。縁談もまとめました。裕福で若い婚約者です。 顔は大したことないかもしれませんが、見た目なんて誰が気にしますか。違います！ 彼女はいつも自分の思い通りにしようとするんです。まったく、母親も昔からそうでしたよ、まったく！\nもっとも、母親が昔、有望そうな馬鹿と駆け落ちしなければ、彼女も生まれていなかったでしょうが……まあ、どうでもいい……若さとは、無知で愚かで残酷なものです。";
			link.l1 = "もちろん、あなたは父親ですし、決めるのはあなたですが、結婚を急ぐのは控えたほうがよいかと……";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "何が分かるんだ？お前に子どもはいるのか？いないのか？自分の子どもができたら話しかけてくれ……\nああ……娘を連れ戻した者には褒美をやると約束した。ほら、受け取れ。";
			link.l1 = "ありがとう。それと、彼女から目を離すなよ。俺の勘だが、あれで終わる女じゃねえ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "「おお、そうか、あなたが」 "+GetSexPhrase("「連れてきたあの船長」","「連れてきたあの娘」")+" 「放蕩息子が若い花嫁を連れてきたのか？」";
				link.l1 = "ああ、俺が奴らの逃亡を手助けしたんだ。";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "おう、そこの "+GetSexPhrase("彼は、我々の恩人だ","彼女こそ、我々の恩人だ")+"。報酬を期待しているんだろう？";
				link.l1 = "まあ、報酬なんてなくても構わねえが、あんたの感謝の言葉だけで十分だぜ。";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "困難な状況で私の子を見捨てず、繊細な問題から救い出してくださったこと、心より感謝申し上げます。\nどうか私からのささやかな金銭と贈り物をお受け取りいただき、感謝の意をお伝えさせてください。";
			link.l1 = "ありがとうございます。この若いカップルのお手伝いができて光栄でした。";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感謝だと？何が感謝だ！？あの間抜けは半年も仕事もせずにぶらぶらしてやがる――しかも見ろよ、恋愛にうつつを抜かす余裕まであるじゃねえか！俺があいつの歳の頃には、 もう自分の商売を切り盛りしてたぜ！ふん！総督には嫁入り前の娘がいるってのに、 あの馬鹿は身寄りもない女をうちに連れてきて、祝福してくれだとぉ！？";
			link.l1 = "ふむ……どうやら本当の気持ちを信じていないようだな？";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "何の感情だ？どんな感情のことを言っているんだ？感情…お前の年でそんなに軽率になれるとはな！若い者の気まぐれに付き合い、世話役のように振る舞うとは恥を知れ！ お前は娘を家から連れ出しただけでなく、俺の未熟者の人生まで台無しにしたんだ。感謝などしないぞ。さらばだ。";
			link.l1 = "ああ、そっちも同じようにな…";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("…もう済んだ。あとはどの船に積み込むか決めるだけだ。","あなたの財務官はすでにそれを済ませている。さて、どの船に積み込むか今決めよう。","「はい」 "+PChar.name+"、知っているよ。もう彼は俺のところに来たぜ。さて、どの船に積み込むんだ？");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "考え直した、もう何もいらない。";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("ふざけてるのか？お前の船はどこだ？桟橋に見当たらねえぞ！","悪魔に誓っても、お前には騙されねえぞ！お前の船は桟橋にねえんだ！"),pcharrepphrase("港にあなたの船が見当たりませんね、船長 "+GetFullName(pchar)+"。まさか彼女が「フライング・ダッチマン」じゃないだろうな？","船長、桟橋から積荷を積む方がずっと楽です。私はそのやり方が好きなんですよ。早く船を持ってきて、 戻ってきてください。"));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"なんて面倒なんだ！よし、ずる賢いじいさん、またすぐ会おうぜ！","「あなたを欺くつもりはなかった」 "+GetFullName(npchar)+"「島の向こう側に船がいるぞ。」"),pcharrepphrase("いいや。俺の船は『ブラックパール』って名前だぜ。\nどうして顔色が変わったんだ？ははっ！冗談だよ！","助言ありがとう、必ず活用させてもらうよ。"));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("さて、船長、どの船に積み込むんだ？","それで、どの船に積み込めばいいんだ？",PChar.name+"「どの船の船倉に商品を積み込みましょうか？」");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "気が変わった、何もいらねえよ。";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("すべて準備できた！選択された船への積み込みを開始した。","よし、選択した船への積荷作業を開始したぞ。","船長、選んだ船への積荷作業が始まったぜ。");
					link.l1 = "ありがとうございます。お取引できて光栄です。";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("船長、あなたの財務官が依頼したすべての商品は、すでにご指定の船に積み込まれております！","船長、指定された船にはもう全部の商品を積み込んだぜ！","船長、その船は整備の必要はねえぜ、もう全部の貨物が積まれてるからな。");
					link.l1 = "「ああ、そうだな。」";
					link.l1.go = "exit";
					link.l2 = "じゃあ、別の船を選ばなきゃならねえな。";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("申し訳ありませんが、その種類の船では、どうしてもそれほど多くは積めません。","船長、あんたの船じゃそんなに積み荷は積めねえぞ！","船長、あなたの船の船倉にはそんなに多くの貨物は積めません！");
				link.l1 = "ああ、その通りだ。別の船を選ばなきゃならねえな。";
				link.l1.go = "TransferGoods_2";
				link.l2 = "考えてみたんだが……何も買う必要はないな。";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("ふざけてんのか？お前の船はどこだ？桟橋に見当たらねえぞ！","悪魔に誓って、俺は騙されねえぞ！お前の船は桟橋にはねえんだ！"),pcharrepphrase("港にあなたの船が見当たりませんね、船長 "+GetFullName(pchar)+"。あの娘が“フライング・ダッチマン”じゃなければいいが？","船長、桟橋から積荷を積む方がずっと楽ですよ。早く船を持ってきて、戻ってきてください。"));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"なんて面倒なんだ！よし、ずる賢いじじい、またすぐ会おうぜ！","「あなたを欺くつもりはなかった」 "+GetFullName(npchar)+"「島の向こう側に船がいるぞ。」"),pcharrepphrase("いいや。俺の船は『ブラックパール』って名前だぜ。\nどうして顔色が変わったんだ？ははっ！冗談だよ！","助言ありがとう、きっと役立ててくれるだろう。"));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "家賃についてだが、まだ俺に借りがあるぞ "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "わかった、今すぐ家賃を払うよ。";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "後でまた来るぜ。";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "来い。";
				link.l1 = "ありがとう。";
				link.l1.go = "storage_2";
			}
			link.l2 = "いや、考え直した。";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "ああ、港に倉庫を持ってるぜ――貨物を五万センター積み込めるんだ。さて "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" 月ごとに、あなたの品物をお預かりできます。 "+"これには警備や浸水対策、そしてネズミの駆除も含まれているんだ。どうだい？それと……前金で一か月分の支払いが必要だぜ。";	
			link.l1 = "「スーツですか。見せていただいてもよろしいですか？そこにはネズミが多いのですか？」";
			link.l1.go = "storage_1";
			link.l2 = "いや、ちょっと聞いただけだ。必要なときには使えるからな……";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "先ほど申し上げた通り、前払いで一ヶ月分の支払いが必要です。それと、ネズミはごめんですよ！";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "あなたは…かなり商売熱心ですね。はい、これが金だ――この小屋を借りるぞ。";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "あなたは……かなり商売熱心ですね。わかりました、すぐにお金を持って戻ってきます。";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "もうお帰りですか？残念ですね――本当に素晴らしい場所で、条件も最高なのに。カリブ中どこを探しても、こんな取引は他にありませんよ。";
			link.l1 = "俺は「免除しろ」って言ったんだぜ。それとも空気を預かるのに金を払えってのか？他の借り手を探しな。";
			link.l1.go = "storage_4";
			link.l2 = "カリブのどこにもないって言うのか？\nわかった、しばらくはこの話はやめておくぜ。";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "それから家賃についてだが、まだ俺に借りがあるぞ "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "「結構だ。」";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "品物を受け取ってください、倉庫を閉めます。";
				link.l1 = "「結構だ。」";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "おお！ちょうどいいところに来てくれました、船長。お願いしたいことがあるのです。";
					link.l1 = "聞こう。"; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "お話を伺いますよ、船長。";
				link.l5 = "ご注文の品をお持ちしました。"; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "おお！ちょうどいいところに来てくれましたね、船長。特別なお願いがあるのです。";
				link.l5 = "聞こう。"; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "お話を伺いましょう、船長。";
				link.l5 = "奴隷を連れてきたぜ。"; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "聞けよ、お前はいろんな品物を扱ってるだろう……昨日か今日、誰かが売りに来たものはあるか "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "船長、お願いしたいことがございます。もし引き受けていただけるなら、十分なお礼をお支払いします。";
				link.l1 = "興味深いな。で、何か問題でもあるのか？"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "船長、お会いできて嬉しいです。あなたが私の依頼をすでに果たしてくれたことは知っていますよ。 "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "へっ！それは間違いねえな。 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" そして積み荷は―― "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+"、もはやあなたのライバルのものではない。"; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "旦那様、船長……なぜ彼を殺したのですか？私が頼んだのは彼の船を沈めることだけでしたのに！聖母マリアよ、 これで私の手は無実の人の血で汚れてしまいました……";
				link.l1 = "へっ！どうしたんだ、 "+npchar.name+"？そんなことどうでもいいだろう――もう二度とあんたを悩ませやしねえんだ、それが大事なんだよ！"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "仕事があったんだが、 "+GetFullName(&Characters[iTmp])+" すでに私のためにそれを引き受けてくれている。";
				link.l1 = "「おや、本当かい？じゃあ、また後で来るとするか。」";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"「何の用だって！？全部話せ！」","聞いているぞ。どんな取引の話だ？");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("俺の船の船倉に、あんたの店向けの品物が一山積んであるぜ。","私の船はあなたの店に商品を届けるために雇われたんだ。\n今、荷物を荷下ろししているところだ。");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "残念ながら、私は自分の約束を断念せざるを得ません。\n政治的な状況により、品物を届けることができません。";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("貨物輸送のために私の船をチャーターすることを提案できます。","俺は立派な船を持ってるぜ、どんな貨物でもあんたの望む場所へ届けてやる。");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "船をチャーターなさいますか、 "+GetAddress_FormToNPC(NPChar)+"？俺には信頼できる船と経験豊富な乗組員がいるんだ。";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "別件で来たんだ。";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("ああ、海の上では本当にくたびれたよ……さて、相棒、今は金が本当に問題なんだ。","よし、老狐、俺たちの金の話をしようじゃねえか。"),RandPhraseSimple("あなたと財政の件について話し合いたいのです。","財政のことについて話そう、これらについて話し合う必要がある。"));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("私はある男の依頼でここに来た。その名は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" あなたのところに来るように言われたんだ。何かを受け取ることになっていて……");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("最新の噂話を教えてくれないか？どうせ一日中ここにいるんだろう。","騒ぐんじゃねえよ、この食わせ者のじじい――陸の新しい話でも聞かせてくれよ？"),RandPhraseSimple("まるで永遠に海の上にいた気分だ。そちらの地域では何か新しいことがあったか？","おそらく最新の情報はご存知でしょう？何か重要な出来事がありましたか？"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "倉庫まで案内してくれ。中の様子を見たいんだ。";
						link.l7.go = "storage_0";
						link.l8 = "倉庫を手放すことにした。今はもう必要ない。";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "失礼、旦那――もしかして倉庫を貸してたりしませんか？";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "ご覧の通り、私は仲間を探しているんだ。 "+pchar.GenQuest.FindFugitive.Name+" 彼の名前です。ポートロイヤルの酒場で、彼があなたの入植地に向かったと聞きました。もしかして、 お会いになったことはありますか？";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "しかし今は話している時間はない。";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"島の反対側に船を置いてきた。後で戻ってくるぜ！","「失礼いたしました」 "+GetFullName(npchar)+"「後で来るよ。俺の船はまだ桟橋に着いてないんだ。」"),pcharrepphrase("ちくしょう！この間抜けどもは積み込みの準備もしてねえじゃねえか！後でまた来るぜ！","失礼、俺の船を桟橋に係留するよう命令を出さなきゃならねえんだ！"));
                link.l1.go = "exit";
				link.l22 = "別件で来たんだ。";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("ああ、海では本当にくたびれたよ……さて、相棒、今は金が本当に問題なんだ。","よし、じいさん、俺たちの金の話をしようじゃねえか。"),RandPhraseSimple("あなたと財務の件について話し合いたいのですが。","話し合うべき金銭の問題について相談しよう。"));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("私はある男の依頼でここに来た。その名は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" あなたのところに来るように言われたんだ。何かを受け取ることになっていて……");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "実は、私の仲間を探しているのです、 "+pchar.GenQuest.FindFugitive.Name+" 彼の名前です。ポートロイヤルの酒場で、彼があなたの居留地に向かったと聞きました。もしかして、 お会いになりましたか？";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "いや、お前のサービスなんて必要ねえ！少なくとも、今はお前が敵対している限りはな。 "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "その場合は、さらばだ。";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"「お前は」 "+GetFullName(pchar)+"、だろ？噂では "+RandPhraseSimple("あなたについて恐ろしいことがたくさん","お前についてたくさんの醜い噂")+"、そしてお前とは取引したくないんだ。";
						link.l1 = RandPhraseSimple("もちろんだ――一度でも失敗すれば、誰もが喜んでお前に唾を吐きかけるさ。",RandSwear()+"「まあ、海にはもっとやるべきことがあるぜ。」 "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"「へっ、」 "+GetAddress_Form(NPChar)+"、今日は積荷の時間がないんだ。また明日来てくれ。","明日また来てくれ。もしかしたらお前に有利な取引を提案できるかもしれねえ。");
						link.l1 = "わかった、明日また来るよ。";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"お前のみすぼらしいオンボロ船じゃ全部の荷を積めねえから、今日は取引なしだぜ。","残念ながら、船長 "+GetFullName(pchar)+"、私の配達にはもっと大きな船が必要になります。");
    							link.l1 = NPCharRepPhrase(npchar,"俺の船も悪くねえが、言いたいことはわかるぜ。じゃあな。","なるほど、商売は商売だな。では、さらばだ。");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
                                }
                                dialog.text = "おお！ちょうどあなたに頼みごとをしようと思っていたところです。実は、私はこの積み荷を届ける必要がありまして "+GetGoodsNameAlt(iTradeGoods)+" 「～の額で」 "+FindRussianQtyString(iQuantityGoods)+" 「町へ」 "+sNation+sTemp+"、そして早ければ早いほどいい。もしそれをまでにやり遂げられたら\n "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+"、到着したらその時に受け取れる "+FindRussianMoneyString(iMoney)+" 報酬としてだ。どうだ？";
    							link.l1 = "私も同意すると思います。";
    							link.l1.go = "exit_trade";
    							link.l2 = "これはたぶん俺には向いてないな。";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "諸島の政治的現実が私に商売を許してくれません。 "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"狩人")+" 誰に対しても敵対的で、店には俺だけを残して出て行ったんだ。";
    						link.l1 = "おっと！申し訳ありません。ご武運を。";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"消え失せろ、暇じゃねえんだよ！","もうあなたに渡せるものは何もないと、すでに言いました。");
				link.l1 = NPCharRepPhrase(npchar,"礼儀をわきまえろ、さもないと俺が礼儀ってもんを叩き込んでやるぞ！","「あっ、すまない！」");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"その取引を思い出すの、ちょっと遅すぎたんじゃないか？俺はもう一度商品を発注しなきゃならなかったんだ。では、 さらばだ。";
				link.l1 = "お許しください、急いでいたもので。もし損失を補償すれば、私の評判も回復するでしょうか？";
				link.l1.go = "generate_quest_failed";
				link.l9 = "ごきげんよう。";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "確かに！ずっと待っていたんだ。俺に届けてほしい貨物があるんだぜ\n "+GetGoodsNameAlt(iTradeGoods)+" 「の額で」 "+FindRussianQtyString(iQuantityGoods)+" そしてそれを受け取る "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "「その通りだ。」";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"お詫び申し上げます。 "+GetAddress_Form(NPChar)+"……実は、問題というのは私が…… "+RandPhraseSimple("恥ずかしい状況で、あなたに支払うことができなくなる"," その貨物はすでに他の商人からもっと良い値段で購入した")+"。チャーターの報酬として、あなたが運んでいた積荷はすべてそのままお持ちください。";
				link.l1 = RandSwear()+RandPhraseSimple("そして俺はその忌々しい積荷をあらゆる危険から守ってきたんだ！そのせいで二百匹ものネズミを殺したんだぞ！","君に手詰まりにされてしまったから、同意せざるを得ない。");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "それが全部じゃないぞ！我々の取り決めによれば、俺が必要なのは "+FindRussianQtyString(iTmp)+" さらにいくつ。";
				link.l9 = RandPhraseSimple("ええ、確かに。その不足分は俺が補うしかないな。それじゃ、またな。",RandSwear()+"この忌々しいネズミどもが積み荷を台無しにしやがった。俺が不足分を補って戻るぜ。");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "素晴らしい！こちらがあなたの報酬です、船長 "+GetFullName(pchar)+".";
				link.l1 = "あなたと一緒に仕事ができて光栄でした。";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "よし……合計は "+FindRussianMoneyString(iMoney)+" 我々の取引条件違反によって生じた損害のみを補償します。";
			link.l1 = "おったまげたぜ！いや、それはダメだ！もう二度と荷物なんか運ばねえ！ そんなクソみてえなもんは海にいくらでも転がってるんだ！";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "必要な金額だ";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "素晴らしい。これで同業者たちにも、あなたとはまだ取引できると伝えられます。";
			link.l1 = "ありがとうございます！もう二度とご期待を裏切りません。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "ふむ。前回の契約で義務を果たしていないと聞いているが――それで今また新しい契約を求めるのか？本来なら貨物を届けるはずだったのに "+GetGoodsNameSeaSection(&Goods[iTradeGoods])+" へ "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "ああ、まさにその通りだぜ！";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+"、俺をがっかりさせるじゃねえか！！！この問題を解決するために何かできねえのか？";
			link.l1 = "わかった。荷物を届けるために最善を尽くす。";
			link.l1.go = "exit";
			link.l2 = "いいえ、できません。申し訳ない。";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "待て！お前の船には積荷が足りねえぞ！持ってないんだ "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" 積荷の単位。";
				link.l9 = RandPhraseSimple("ええ、確かに。その不足分は私が補わなければなりませんね。",RandSwear()+"ネズミどもが積み荷を台無しにしやがった。不足分は俺が買い足して戻るぜ。");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "なるほど、なるほど……荷物は引き取らせてもらうよ。";
    			link.l1 = "ありがとうございます！もう二度とご期待を裏切りません！";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "何を言っているんだ？明らかに誤解されているな――俺はそんな大量のヨーロッパ産ワインなんて扱ったことはないぜ。せいぜい一本か二本、それ以上はない。 だが地元のワインなら話は別だ――あれならたっぷりあるし、瓶じゃなくてデミジョン単位で売っているんだ！";
			link.l1 = "ちくしょう！だが、そう聞いていたのに……";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "何を聞かされたのか知らないが、もう一度言うぞ。ヨーロッパ産のワインは在庫にない。 それだけがこの件について言えることだ。";
			link.l1 = "よし…じゃあ、俺が片付けてくるぜ、じゃあな！";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "それはまた別の話だな。ここにはいろんな奴が来て、余計なことを聞いてくるんだぜ。さて、取引を始めるか？";
			link.l1 = "もちろんだぜ！";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "何本必要ですか？一本の値段は500ペソで、最小ロットは20本です。";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "今は十分なお金がないんだ。後でまた来るよ。";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "私は行商人ではありませんよ、船長。たしか、もっと大口の取引について話していたのでは？";
				link.l1 = "申し訳ない……では、金額をもう一度考え直しましょう。";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "残念ながら、そんなに持っていません。";
				link.l1 = "残念だな……では、金額をもう一度考え直そう。";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" 瓶か？いいぜ。それなら代金がかかるぞ "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "「はい、どうぞ。」";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "今は十分なお金がないんだ。また後で来るぜ。";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "大丈夫だが、あまり時間をかけすぎないようにな。この品はここでかなり人気なんだ。";
			link.l1 = "すぐ戻るぜ！";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "そうだな……すべて問題ないようだ。購入品を受け取ってくれ。";
			link.l1 = "ありがとうございます！ご武運を！";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "良い取引をするつもりだったが、そのためにはまだ特定の品が必要なのだ― "+GetGoodsNameAlt(iCGood)+"。問題は、この商品が我が植民地では禁制品でして、交易船長から買い取ることは期待できません\n私が必要なのは "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" それを何単位か。もしかして届けてくれるか？十分に報酬を払おう、 "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" 1単位あたりで、合計は "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+"。ああ、それと、遅くともそれまでには必要だ "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+"。さて、手を貸してくれるか？";
			link.l1 = "ふむ……面白そうだな。俺も賛成だぜ！";
			link.l1.go = "Contraoffer_1";
			link.l2 = "密輸品の運搬か？悪いが、興味ねえな。";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "素晴らしい。承諾してくれて嬉しいよ。では、品物を持って戻ってくるのを待っているぞ。";
			link.l1 = "すぐに戻るぜ！";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "冗談か？俺が必要としている商品が全部そろってねえじゃねえか！";
				link.l1 = "申し訳ない、私のミスだ……";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "さて、それでは。あなたは荷物を届けることになっていたはずだが "+GetGoodsNameAlt(iCGood)+" 「…の額で」 "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+"。正しいか？";
				link.l1 = "「その通りだ」 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "お勤めご苦労さまです。どうぞ、こちらがあなたの報酬です― "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "ありがとうございます！お取引できて光栄です。";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "おっと……船長、どうやらここで問題が起きたようだ……";
				link.l1 = "「また何だって？」";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "至急奴隷の一団が必要だ―― "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" 首だ。支払う用意はできている "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" 一人あたりの金貨で、合計は "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" 合計ペソ；期間― "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "同意しようと思う。面倒だが、とても儲かる商売だからな。";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "興味はない。";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "まさにその通り――実に儲かる話だ。\nでは、奴隷たちと共にあなたの帰りをお待ちしていますよ。";
			link.l1 = "長く待たせないよ。またな！";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "冗談じゃねえか？俺が必要な奴隷が全部そろってねえじゃねえか！";
				link.l1 = "申し訳ない、私のミスだ……";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "さて、それでは。俺に奴隷を一括で納品する予定だった数は "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+"。正しいか？";
				link.l1 = "「その通りだ」 "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "お勤めご苦労さまです。どうぞ報酬をお受け取りください― "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+"。また、これをお受け取りください。きっとお役に立つはずです。";
			link.l1 = "ありがとうございます！お取引できて光栄です。";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "「ふむ、」 "+pchar.GenQuest.Device.Shipyarder.Type+"？今まで聞いたことがないな……それは一体何なんだ？こんなもの、生まれてこのかた一度も聞いたことがないぞ。";
			link.l1 = "「まあ、これは船大工の道具だ」 "+pchar.GenQuest.Device.Shipyarder.Describe+"。そんなことを誰かがあなたに持ちかけてきたのか？";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "ふむ……ああ、変な奴が一人いたな。だが、そいつはそれが何なのか教えてくれず、ただ俺に売りつけようとしただけだ。だが、 何に使う物か分からねえのに、俺がそれを買ってどうする？どうやって転売するんだ？だから、俺は断ったんだよ。";
				link.l1 = "それで、そいつはどんな奴だったんだ？どこへ行った？俺はその道具がどうしても必要なんだ。";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いや、そんなことはない。すまないが、力になれないんだ。他の人に聞いてみてくれ。";
				link.l1 = "なるほど。さて、聞き込みを始めるとするか！";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "競争……それがなければ商売は成り立たねえ。お前の居心地のいい商売に割り込もうとする強欲な野郎どもが、 あの手この手で客を奪おうとしやがる。\nだが、それはただの話さ。実はな、俺の競争相手の一人を排除するのを手伝ってほしいんだ。いや、殺す必要はねえ。 ただ、あいつの船と積み荷を拿捕するか沈めてくれりゃいい。";
			link.l1 = "ふむ……まあ、報酬がいいなら手配してやれるぜ。";
			link.l1.go = "Sunplace_1";
			link.l2 = "いや、俺はお前らの商売争いには首を突っ込まねえ。俺の助けなしでライバルを沈めてこい。";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "承知しました。では、あなたの部下の名前は "+pchar.GenQuest.Sunplace.Trader.Enemyname+"。最近、彼は送り出した "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Acc"))+" 「」"+pchar.GenQuest.Sunplace.Trader.ShipName+"「」には積荷として "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+"。彼はこの貨物にかなりの大金を支払ったから、それを失うのは財布に大きな打撃となるだろう。";
			link.l1 = "「それで、その“友人”とやらを具体的にどこで探せばいいのか教えてくれないか？」";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "俺の「友人」は今、自宅にいるんだが "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+"。あんたが必要なのは彼じゃなくて、彼の船さ。俺が調べたところによると、約 "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" 近くを通過する "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+"。沈めてもいいし、拿捕しても構わん――重要なのは、その船と積み荷がもはや所有物でなくなるようにすることだ "+pchar.GenQuest.Sunplace.Trader.Enemyname+"。そして俺は、それを誰が主張しようと――お前でも海でも――気にしねえ。その仕事には報酬を払うぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)) + ".";
			link.l1 = "わかった。さて、出発の時間だな！";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "素晴らしい！君ならやってくれると信じていたよ。その船と積み荷の行方については聞かないでおこう。結局、 私の関知することではないからね。それに、私の友人もあの打撃から立ち直るにはしばらく時間がかかるだろう、ふふっ。 さあ、こちらがお金だ――よくやってくれてありがとう。";
			link.l1 = "どういたしまして……では、また。 "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Poor "+pchar.GenQuest.Sunplace.Trader.Enemyname+"、なんてむごい運命だ！しかも間接的とはいえ、俺があいつの死の原因になっちまった！船長、 あなたにはわからないんだ！俺があいつを殺せと頼んだか？積荷に費やした金を失った後、あいつはまた……いや、もういい……お前は…";
			link.l1 = "おい、聞けよ、泣き言はやめろってんだ。お前がライバルを始末しろって頼んだんだろ？俺はやったぜ。しかもな、 もしあいつが荷を失っただけなら、また金持ちになってお前の商売を邪魔し続けただろうさ。だが今や、 あいつは死んじまったんだ。もうどうしようもねえよ。";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "もうたくさんだ！これ以上、その冒涜的な話は聞きたくない！さっさと血塗られた金を持って、 今すぐ俺の店から出ていけ！";
			link.l1 = "「おい、」 "+npchar.name+"落ち着けって、いいな？さもないと、俺が自分でお前の頭を冷やしてやるぜ――俺のサーベルはいつも腰にあるからな！\nまあまあ、怖がるなよ、冗談だ。\nこうなっちまって悪かったな――でも最初に俺を騙したのはお前の方だぜ。\nじゃあな。";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"「ああ、あいつなら知ってるぜ。俺からロングボート用の食料を買っていったんだ。 昼間はたいてい人目につかない入り江で釣りをしてるが、毎晩必ず酒場に現れるぜ。」","その男についてはすでに聞かれましたし、私の知っていることはすべてお話ししました！","俺をからかってるのか、それとも本当にバカなのか！？もう三回も同じ質問をしてるじゃねえか！","まったく、どうしてあんな馬鹿が船長になれたんだ……","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("ありがとうございます、おかげで本当に助かりました！","ああ、ああ、わかったよ。","まあまあ、そんなに興奮するな。ちょっと忘れてただけだ。","まあ、見ての通り、彼はやったんだよ……",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("ポートロイヤルの酒場で人々が何を言っていたのかは知らないが、俺の店でその男に会ったことは一度もない。 実のところ、どこでも見かけたことがないんだ。村で聞き込みをしてみな――誰かが何か教えてくれるかもしれないぞ…","その男についてはもう聞かれましたし、私は「知らない」と答えましたよ！","俺をからかってるのか、それとも本当にバカなのか！？同じ質問をもう三回もしてるじゃねえか！","考えただけで、どうしてあんな馬鹿が船長になれたんだ…","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("なるほど。まあ、とにかくありがとう。","ああ、ああ、わかったよ。","まあまあ、そんなに興奮するな。ちょっと忘れてただけだ。","「まあ、見ての通り、彼はやったんだ…」",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "旦那、一体どうしたんです、若者よ！もっと慎みを持って、尊敬される方々について話す時は言葉を選んでください！ ジェラール・ルクロワは本土への遠征でグアドループを発ちましたが、あなたへの報酬はここに預けていきました。 これで満足ですか？";
			link.l1 = "うむ……失礼しました、旦那。少し調子に乗ってしまいました……";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "よろしいでしょう。ルクロワ旦那はあなたへの報酬を地元の灯台守に預けていきました――彼らは古い友人同士です。あなたは灯台守のところへ行き、報酬を受け取るだけでいいのです。 ルクロワ旦那は誠実な方ですから、きっとご満足いただける報酬でしょう。";
			link.l1 = "了解だ、ありがとう！それじゃあ灯台守のところへ行くぜ。今はちょっと休ませてくれ。";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "ああ、彼はここにいて、あなたを待っていましたよ。しかし、 彼があなたに託した任務が思ったよりも難しかったのかもしれません、それで彼は待たずに本土への遠征に出発しました。 報酬は信頼できる者に預けていきました。";
			link.l1 = "はい、本当に予期せぬ事情がありましたが、任務は無事に完了しました。\n報酬が用意されていると聞いて嬉しいです。\n誰から受け取ればよいでしょうか？";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "ルクロワ氏はあなたへの報酬を地元の灯台守に預けていきました――彼らは古い友人同士なのです。あなたは灯台守のところへ行って、報酬を受け取るだけでいいのです。\nルクロワ氏は誠実な方ですから、きっと満足できる報酬でしょう。";
			link.l1 = "了解だ、ありがとう！じゃあ灯台守のところへ行ってくるぜ。今はちょっと休ませてくれ。";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "ご武運を、旦那。";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "なんてうるさいんだ、若造！落ち着け、そして尊敬すべき人のことを話すときは言葉を選びなさい！ ジェラール・ルクロワは本土への遠征でグアドループを発ったが、君への伝言を残していったぞ\n落ち着いたかい、旦那？私の話を聞く準備はできたかな？";
			link.l1 = "うむ……失礼しました、旦那。少し熱くなってしまいました。お話を伺います。";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "よろしい。次は、まず尋ねてから大声で叫ぶようにしてくれ。さて……シモン・モロワという男を知っているか？";
			link.l1 = "はっ！シモン・モロワの名は誰もが知ってるさ！もちろん俺も知ってるぜ。";
			link.l1.go = "trial_2";
			link.l2 = "知らねえな。誰だそいつは？";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "素晴らしい。では、彼のところへ行きなさい。ショーク旦那の遠征を資金提供したのは彼だから、 報酬は彼から受け取れるはずだ。\nそれにしても、そんなに熱くなる必要が本当にあったのか？";
			link.l1 = "重ねてお詫び申し上げます……ご協力ありがとうございます、旦那。すぐにマロワ旦那にお会いしてまいります！";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "彼はモーロワ銀行のオーナーであり、カプスターヴィル支店の責任者でもあります。\nですから、サン・クリストファーへ行き、カプスターヴィルの銀行を訪ねなければなりません。\nショーク旦那の遠征に資金を出したのはモーロワ旦那ですから、報酬は彼から受け取れますよ。\nそれにしても、そんなに熱くなる必要が本当にあったのでしょうか？";
			link.l1 = "改めてお詫び申し上げます……ご協力ありがとうございます、旦那。すぐにマロワ旦那にお会いしてまいります！";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "おお、やり手の商人さんだな！商才はひと目で分かるぜ。感心するよ。もちろん、あんたが必要な品は揃ってるぜ。";
			link.l1 = "きっと利益を出して売れるだろう。私の知る限り、この品はポルトベロで需要が高い。\nいくらかかるのだ？";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "まあまあだな…それで、コーヒー三百樽…同じ量のカカオもか…それでお代は…"+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" ペソだ！";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "うーん……失礼、どうやら手持ちの金が足りないようだ。少し待ってくれ、今すぐ船まで金を取りに行ってくる――すぐ戻るからな！";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "「はい、どうぞ。」";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "ちょっと待ってくれ、旦那。どうやらあなたの船にはこれだけの人数を乗せる余裕がないようだ。 船倉を空けてから戻ってきてくれ。";
				link.l1 = "あっ、荷下ろしを忘れてた！ちょっと待ってくれ、すぐに行くぜ！";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "素晴らしい！すぐにあなたの船に商品を積み込むよう命じます。お取引できて光栄です！";
				link.l1 = "こちらこそ、旦那！さて、これで失礼するよ。物事は待ってくれないからな。";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "品物は用意してあります。金は持ってきましたか？";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "まだだ。あんたの申し出がまだ有効か確認したかっただけさ。金はすぐに用意するぜ。";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "「はい、どうぞ。」";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "今のところ、あなたのサービスは必要ありません。";
			link.l1 = "残念だな。話題を変えよう。";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
