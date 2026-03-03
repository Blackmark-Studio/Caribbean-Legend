// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("町は警戒態勢だ。俺も武器を取る時が来たようだな…","町中の衛兵に追われてるんじゃねえのか？俺のところに来い、兵隊ども！","ここに隠れ場所なんてねえぞ。だが、お前の肋骨の下には冷たい鋼が数インチ突き刺さることになるぜ！"),LinkRandPhrase("何の用だ、この悪党め！？市の衛兵はもうお前の後を追ってるんだ、そう遠くへは逃げられねえぞ。 "+GetSexPhrase("汚い海賊め！","ろくでなし")+"!","止まれ！ "+GetSexPhrase("汚ねえ殺し屋め！警備兵！！","俺はお前なんか怖くねえ！すぐに俺たちの砦で絞首刑にされるんだ、もう隠れる場所なんてねえぞ…")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("生きるのに飽きちまったようだな……","「それで、なぜお前たちは平和に暮らしたくないんだ、市民たちよ……」"+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("地獄へ落ちろ！","この世でお前に残された時間は、あとほんの数秒だ……"));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "あ、ああっ！あんたか……誰だ？何の用で墓地に来たんだ？";
				link.l1 = "私の名前は "+GetFullName(pchar)+"。で、あんたは誰で、ここで何をしているんだ？それに、なんでそんなに怯えているんだ？";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "それで、どうだった？確かめたか？今なら俺の言うこと信じるだろう？";
				link.l1 = "いや、まだ地下墓所には降りていない。もう少し待ってくれ、全部調べてくる。";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "どうだ？見てきたか？見えたのか？";
				link.l1 = "ああ、やったぜ！お前の言う通りだった！";
				link.l1.go = "Lantern_10";
				link.l2 = "思っていたのとは少し違ったんだ。";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("やあ、水夫！俺の名前は "+GetFullName(npchar)+"、そしてここに生きているのは俺一人だけだ。実のところ、俺たちは皆どうせ死ぬんだよ、ははは！何しに来たんだ？","こんにちは！生きている人間を見るのは久しぶりだ……自己紹介させてくれ―― "+GetFullName(npchar)+"、そしてこの墓地が私の最後の避難所だ。どうやら私はここに埋葬されるらしい。何かお手伝いできることはあるか？");
				link.l1 = "「こんにちは。」 "+npchar.name+"！俺の名は "+GetFullName(pchar)+"、そして俺は船長だ。ジャングルを歩いてここまで来た。この居心地の良さそうな家の中を覗いてみようと思ってな、 こんな場所に住む度胸のある奴が誰なのか見てやろうと思ってな…";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ああ、俺の古き友よ、船長 "+GetFullName(pchar)+"「！入ってくれ、入ってくれ！」";
				link.l1 = "ようこそ、友よ！会えて本当に嬉しいぜ。夜になると踊る骸骨や、目に銅貨を乗せた死人が夢に出てきたりしねえか？";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "「それで、なぜ俺が怖がらなきゃいけねえんだ、船長？怖れるべきは生きてる奴らさ、死者じゃねえ――あいつらは噛みつかねえよ。ええ！昔は全然違う人生を送ってたが、今じゃこの墓地の見張り番さ。墓を見守ってるんだ。 そして時々、変わった品を商売にすることもある……」\n";
			link.l1 = "「それで、どんな商品を扱っているんだ？教えてくれよ、頼むぜ？」";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "今回は何の用で俺のところに来たんだ？";
			link.l1 = "今日売っているものを見せてくれ。";
			link.l1.go = "trade";
			link.l2 = "ちょっと聞きたいことがあるんだが……";
			link.l2.go = "quests";
			link.l3 = "大したことじゃねえ。ただ挨拶しに来ただけだ。";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "暇な時間がたくさんあるから、ジャングルを歩いて役に立つ植物や面白い石を集めるのが好きなんだ。 それを町で売るんだよ。大した値にはならないけど、何もないよりはましさ。それに友達からいろんな物ももらえるし……";
			link.l1 = "友達だと？つまり、他人が持ってきたものをお前が転売してるってことか？";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "おほほほ……いや、全部タダでもらってるのさ。墓守なんて死人以外に友達がいると思うかい？";
			link.l1 = "な、なんだと…死体をあさってるのか？";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "俺は盗みなんかしねえ。ただ、もう必要なくなった奴らから物をもらうだけさ。ここにはいろんな奴が埋まってる――名も知らぬ者や、俺たちの土地の出じゃねえ奴もいる。司令官が町から死体を運んできてこう言うんだ。 「これはお前の分だ」、 "+npchar.name+"「……あいつを最後の旅路に送り出してやれ」。家もなく、絞首刑になった海賊や、守衛に殺された盗賊――みんなここに埋められている。そして年老いた\n "+npchar.name+" キリスト教の習わしで遺体を埋葬する。";
			link.l1 = "なるほどな。まあ、金は金だ。持ってるものを見せてくれ。";
			link.l1.go = "trade";
			link.l2 = "承知した。行かねばならない。お会いできて光栄だった。";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("「そしてお前」 "+GetFullName(pchar)+"「お前は泥棒だ！衛兵！！！」","なんだと！ちょっと目を離した隙に、もう俺の物を盗もうとしてやがるのか！泥棒を捕まえろ！！！","「衛兵！強盗だ！！！泥棒を捕まえろ！！！」");
			link.l1 = "「なんてこった！！！」";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "ふう、ただの旅人か……俺の名前は "+GetFullName(npchar)+"、この見捨てられた場所の管理人だ。";
			link.l1 = "なぜ墓地についてそのように感じるのですか？\n逆に、こここそが主が正しき者たちを埋葬の後にお連れになる場所なのです。";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "だが、不義の者たちは埋葬された後もどうやらここに留まっているようだ！ここ数晩、 地下墓地から何やら物音が聞こえてくるんだ。しかも、そのうめき声があまりにも不気味で、身の毛もよだつほどだ……迷える魂が安らぎを得られずにいるらしい！今では昼間しか眠れなくなった――夜は持ち場を離れることも、ひと眠りすることもできないんだ……\n";
			link.l1 = "物音？うめき声？でも、そこには死者以外誰もいないはずだ。";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "俺が言ってるのはそういうことだぜ、わかるか？幽霊に気づかれる前にここから出て行ったほうがいいぜ……さもないと、俺みたいに眠れなくなるぞ。";
			link.l1 = "ふむ、そうだな、ここを離れたほうがよさそうだ。";
			link.l1.go = "Lantern_04";
			link.l2 = "もしかしたら俺が手伝えるかもな？今夜、その奇妙な物音を調べてみよう。";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "正気じゃねえのか！？武器を持ってるのは分かるが、それでアンデッドとどう戦うつもりだ？それに、 もしそこでくたばったらどうなる？幽霊は自由にさまよい、お前をしもべとして蘇らせるかもしれねえぞ！";
			link.l1 = "まあ、それはただの迷信だよ……";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "迷信だと？ここは敬虔なヨーロッパの土地じゃねえんだ、くそっ…あの赤い肌の原住民どもは、何でも呪術で呼び出せるって話だ――で、俺たちは今ここで暮らさなきゃならねえんだよ！";
			link.l1 = "それでも、やってみるさ。夜になるまで待ってから、地下墓所へ降りていくぜ。";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "好きにしろよ。だが、夜明けまでに戻らなかったら、全部施錠して、板で塞いで、俺一人でここを出ていくからな！ 水夫として甲板を磨こうが、港で荷物を運ぼうが――とにかくもうここには戻らねえぞ！\n";
			link.l1 = "落ち着けよ……全部うまくいくさ。";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "待て……このランタンを持っていけ。予備があるんだ。あそこでは必要になるぞ。真っ暗だからな！";
			link.l1 = "ありがとう、ああいう場所では確かにランタンが役に立つな。";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "そうだろ？何があったんだ？教えてくれ！";
			link.l1 = "女の落ち着かない霊がいたんだ！運よく、地元の神父に俺の剣を祝福してもらって、邪悪を討てるようにしたから、 すべてうまくいったぜ。もうあの霊がお前を悩ませることはないさ。";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "ああ主よ、我ら罪深き魂をお救いください！警告したじゃないか！なのに信じてくれなかったんだ！";
			link.l1 = "はい、そして本当に残念に思っています。しかし、今はもう大丈夫です――この場所に聖水を撒きましたから、どんな霊も墓から出てくることはありません。安心してお休みください。";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "本当にありがとうございます！あなたにはこれがどれほど私にとって大切か分からないでしょう！\nさあ、これを受け取ってください。大したものではありませんが、何も渡さずにあなたを帰すわけにはいきません。";
			link.l1 = "ありがとう、断れないな。幸運を祈るぜ！";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "違うのか？じゃあ一体、悪魔でも…いや、神に誓って、そこで何が起きたんだ？";
			link.l1 = "幽霊なんてまったくいなかったんだ。若いカップルがこの地下墓所を逢引きの場所に選んだだけさ。\n両親が二人の仲に反対しているから、二人きりになれる場所を探していたんだよ。";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "一人きりか……？なんだと、あの若造どもめ！もう一度ここに来てみろってんだ！俺がムチで二人まとめて追い払うか、 地下納骨堂にぶち込んで二度と出られねえようにしてやる！！！";
			link.l1 = "もうここには戻ってこないよ。あいつらには、 あのちょっとした悪ふざけが地元の衛兵を本気で怖がらせたって伝えておいた。あいつらもそれが狙いだったんだ。 それに、ちなみにドアの鍵はどうせ壊れてるしな。";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "問題ない、俺が取り替えてやるよ。だが、もしあいつらを見つけたら……";
			link.l1 = "そんなに怒るなよ。誰だってあの年頃はそうだったさ。ここが恋愛に最適な場所だから来たわけじゃねえんだ。";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "まあ、仕方ないな……そうか、主があの者たちと共にありますように。困っている老人を見捨てずにいてくれて、ありがとう。さあ、 これを受け取ってくれ。大したものじゃないが、礼なしで帰すわけにはいかんからな。";
			link.l1 = "ありがとう、断れないな。幸運を祈るぜ！";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
