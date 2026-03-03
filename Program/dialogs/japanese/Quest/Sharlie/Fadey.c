int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "ファディ、アロンソという男を知っているか？";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "ファデイ、君の鏡の胸当てを買う準備ができたよ。";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "ご用件は何でしょう、旦那？私は知り合い以外とは話しません。もし世間話や、1640年にマラカイボへスペインの銀輸送隊がいつ到着するかを聞きに来たのなら、残念ですがお答えできません。 無駄話に時間は割きませんので。";
					link.l1 = "こんにちは、ファデイ旦那。まだ私のことはご存じないかもしれませんが、兄のことはご存じでしょう。 自己紹介させていただきます――シャルル・ド・モール、ミシェル・ド・モンペールの弟でございます。";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "ああ、またお前か、シャルル！カク・デラ？今度は何の用だ？";
					link.l1 = "盗賊にやられたと言っていたな……犯人は見つかったか？";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "それでシャルル、あの野蛮人と話しに行ったのか？";
					link.l1 = "私には……それがあるんだ。だから君のもとに戻ってきたんだ。";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "ああ、またお前か、親愛なる友よ！さて、インディアンのための身代金のドゥブロン金貨は持ってきたのか？";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "はい。こちらがあなたの35ドゥブロンだ。";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "いいえ、まだ十分に集めていません。";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "はい。こちらがあなたの40ドゥブロンだ。";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "いいえ、まだ十分に集まっていません。";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "はは、なんだ、シャルル・ド・モールご本人じゃないか！入れって言っただろ、そこで突っ立ってないで！ どうして俺の家に来たんだ？";
					link.l1 = TimeGreeting()+"「ファディ、兄さんがあなたのところに行けって言ってたんだ。仕事を探すのを手伝ってくれるって。」";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "ははっ、お前か！何の用だ、ド・モール旦那？";
					link.l1 = TimeGreeting()+"「ファデイ、兄がこのことを君に話すなと強く言っていたけど、どうしても黙っていられなかったんだ……」 ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "「おお、古い友よ！入ってくれ、入ってくれ。」 "+pchar.name+"！ご機嫌いかがですか？";
					link.l1 = TimeGreeting()+"「ファディ。会えて嬉しいよ。実は大事な話があるんだ。黒い黄金のことさ。」";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "ああ、またお前か、親愛なる友よ！戦利品は手に入れたか？ドゥブロン金貨は十分見つけたか？";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "「はい、ファデイ様！こちらがあなたの金貨です。」";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "いや、通りすがりだ。まだちょうどいい額を探しているところさ。";
						link.l1.go = "exit";
					}
					
					link.l2 = "ファディ、今ちょうどいい考えが浮かんだんだ。もう奴隷は必要ない。悪いが、また後で会おう！";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "「ああ、懐かしい友よ！入ってくれ、入ってくれ、」 "+pchar.name+"！元気か？";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+"、また君の助けが必要なんだ。";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+"「ファディ、会えて嬉しい。君に用があるんだ。」";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "ああ、またお前か、親愛なる友よ！さて、金は見つけたか？";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "持ってきましたよ、Fadey旦那！こちらがあなたの75ドゥブロンです。";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "ございます、ファデイ旦那！こちらがあなたの四万ペソです。";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "いいえ、ただ見に来ただけです。まだちょうどいい金額を探しているところですよ。";
						link.l3.go = "exit";
					}
					link.l4 = "すまない、ファディ。だけど、俺にはそんな余裕はないんだ。自分でなんとかしてみるよ。またな！";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "「入って、入って」 "+pchar.name+"！俺の目を見りゃ、俺の武勇伝を聞きたくてたまらねえってわかるぜ。";
					link.l1 = "その通りだ、ファディ。私が欲しいものを持ってきてくれたと信じているぞ。";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "ああ、またお前か、親愛なる友よ！それで、金は見つかったのか？";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "７５ドゥブロン受け取ってくれ。水夫たちにこの木箱を俺の船まで運ばせるよ。\nああ、ファディ、君がいなかったらどうなってたことか！？君がどれだけ助けてくれたか、想像もつかないよ！";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "4万ペソを受け取れ。この箱は水夫たちに運ばせて俺の船に積む。ああ、ファデイ、 君がいなかったらどうなっていたことか！？君がどれほど助けてくれたか、君には分からないだろう！";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "いや、ただ通りかかっただけだ。まだ十分集めようとしているところさ。";
						link.l3.go = "exit";
					}
					link.l4 = "すまない、ファディ、俺はすっからかんなんだ。預けた金はそのまま取っておいてくれ。 この取引の経費をまかなうのに足りるといいんだが、あとは自分でなんとかしてみるよ。じゃあな！";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "おお、来てくれたな、旦那！君の船が我々の港に停泊したと聞いて、ぜひ訪ねてくれるのではと期待していたのだ。";
					link.l1 = "「こんにちは。」 "+npchar.name+"…長話はいたしません。私の仲間メアリーと私は、二十年前に跡形もなく姿を消した彼女の父親を探しているのです…";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "メアリーの父親については……";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "「おやおや、誰かと思えば」 "+pchar.name+"!";
					link.l1 = "「本当に輝いているわ」 "+npchar.name+"「それで、どうだった？何か分かったのか？」";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "ああ、印を持つ者――いや "+pchar.name+"「さあ、俺に何を用意してくれたんだ、言ってみろよ！」";
					link.l1 = TimeGreeting()+"「フェイディ、会えて嬉しいよ。今日は商談の話で来たんだ。」";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"。俺が神父と魂を見つめ直す会話をした結果、どうなったか聞きたくてたまらないんだろう？";
					link.l1 = "もちろんだよ！どうだった？";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "ああ、失礼しました、あなたのポケットの中で鳴る小銭の音に気を取られてしまいました！";
					link.l1 = "なんて強欲なんだ、ファディ！ほら、金貨だ。";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "「おお、古い友よ！さあ、入ってくれ、入ってくれ」 "+pchar.name+"！それで、新しい情報でも手に入れたか？";
					link.l1 = "やあ、ファディ。もう一度君の助けをお願いしたいんだ。";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "何だ、お前は石像か？言いたいことがあるならさっさと言え。ないならとっとと失せろ。 "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "見てみろ、ファディ。これはペルシャのシャムシールだと思うが、 お前のコレクションから盗まれたものの一つかもしれないな？";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "良い知らせがあります。ここにもう一本ペルシャのシャムシールを用意しました。";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "三本目のペルシャ製シャムシールがある。頼まれた通り、できるだけ早く持ち帰ったぞ。";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "例の軽装甲の件で来たんだ。";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "ファディ、君の有名なロープを少し買いたいんだ。";
					link.l3.go = "ropes";
				}
				link.l1 = "ファディ、君の助けが必要だ。";
				link.l1.go = "help";
 				link.l9 = "いいえ、今のところ何もありません。";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "ご用件は何でしょうか、旦那？私は知らない方とはお話しません。";
				link.l1 = "ああ、ちょっと誰がここに住んでいるのか見に寄っただけさ。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "ああ、君があの懐かしいミシェルの弟さんか！それは話が変わるな！さあ、どうぞ、旦那、座ってくれ。\n我々の出会いを祝ってウォッカで乾杯しないか？まだ何本か残っているし、親友の弟と一緒に飲めるのは嬉しいことだ、 ダー！";
			link.l1 = "申し訳ありません、Fadey様、ですが今夜は酒を飲む気分ではありません。できれば早速本題に入りたいのです。";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "なんだと！この地元のラムなんざ、ロシアのウォッカに比べりゃ水みてえなもんだぜ！お前ら、本当の酒を知らねえな。 もし俺が嘘ついてたら海に呑まれてもいいぜ！\nよし、仕事の話に移ろうか。全部聞いてるぜ、シャルル。";
			link.l1 = "旦那、これからお話しすることは大変不愉快かと存じますが、義務によりお伝えせねばなりません！\nミシェルから、あなたが彼との賭博でかなりの額を借りていると聞いております。そして、 兄の代理として私にその金を渡すようにと指示されました。兄は……今は直接お会いできない事情があるのです。";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "おお、若者よ！もちろん、すべて覚えているとも、そして君の兄上に借りがあることも認めよう。 賭けの借金は神聖なものだ、その義務を果たすことこそが、我々 を死の混沌や危険な盗賊から救ってくれる唯一の道なのだ！だが、どうか私の事情も理解してくれ！最近、 私には不愉快な出来事があった――実に図々しい手口で盗みに遭ったのだ！\n忌々しい盗人どもが持てる限りの物を奪っていった、長年の労苦で得たものも、金も、 かけがえのないコレクションもすべてだ！今すぐ借金を返済することなど到底できん、無理だ\nだが、ド・モール旦那、私は義務を放棄するつもりはない！ただ、歩み寄りをお願いしたいのだ。 今は手元に一文もないので、この素晴らしい希少な短剣を差し出そう。見てくれ！\nこれは本物の鋼の傑作で、私の盗まれたコレクションの誇りだった一品だ。しかも、 インディアンのシャーマンによって魔法がかけられており、強力な隠された力を持っている！インディアンたちはこれを 「酋長の爪」と呼んでいた\n本来なら絶対に手放したくなかった、なにしろこの短剣には借金よりはるかに多くの金を払ったのだからな。しかし、 この状況と君の兄上との関係を考慮して、君に譲る覚悟を決めた。受け取ってくれ、とても良い取引だぞ！";
			link.l1 = "俺はナイフより金の方がずっと欲しいんだが…";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "でも金は持ってないし、この珍しい魔法のアーティファクトならあるんだ！なあ、ドラグ・モイ、もし他の状況だったら、 こんな素晴らしい魔法の短剣を、ただのくだらない銀貨の代わりにお前に差し出すと思うか？ ペソなんてどこにでも転がってる、道端にだって落ちてるさ！正直、俺はちょっと困ってるんだよ。 この見事な職人技の逸品と別れることを考えるだけで胸が痛む……だが、賭けの借金は名誉の借金だ。だからこそ、お前だけに譲る覚悟を決めたんだ。 俺にとっては本当に大切なものだけど、お前は本物の名誉ある男で、本物の友だからな。";
			link.l1 = "よし、金がないって誓うなら、お前のこの魔法の短剣をもらっていくぜ。うまく売れればいいんだがな……";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "「売れ」だと！？出ていけ、この…いや、シャルル！冗談じゃない、耳を疑うぞ！俺の一番大事な宝物を、ヨーロッパなら十倍は値がつく代物を、 ただで譲ってやろうってのに、お前は平然と質に入れるだと！？この短剣はな、若造、ある男の命を救ったんだ！ 聞かせてやろう――";
			link.l1 = "「それで、あなたが言っていたその隠された力とは何ですか？」";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "おお、ほっほっほ！さて、シャルル、私は善良なキリスト教徒でしてね、 インディアンのシャーマンなんかじゃありませんよ。この刃物に秘められたすべての力を知る術はありません。しかし、 確かに存在しますとも！この短剣を手に取ってみなさい、内に宿る力を自分で感じられるはずです！さあ、 受け取りなさい、受け取りなさい！どうだい！何か感じるかい？";
			link.l1 = "ふむ……何も感じないな。だが、手にはしっくりくる。";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "あはは！そうだ、それでいい！だが、これはその力のほんの一部にすぎない。この短剣を戦で振るえば、 きっとさまざまな劇的な力を見せてくれるはずだぜ！\nさて、受け取るか？";
			link.l1 = "さて、俺に選択肢があるのか？仕方ねえ、金がねえなら俺がもらっておくぜ…";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "ありがとう、シャルル。絶対に後悔はさせないよ、本当にね！はい、どうぞ。\nそれから、ミシェルによろしく伝えてくれ！時間ができたら、ぜひ顔を出してくれって言っておいてくれよ。";
			link.l1 = "「ああ、伝えておくよ…」";
			link.l1.go = "exit";
			link.l2 = "盗賊にやられたと言っていたな……犯人は見つかったのか？";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "問題は、私がまだ持っていないことだ。あのごろつきどもが家中を荒らし回って、銀も金も、 何年も汗水流して貯めた蓄えも全部持ち去っていった。まあ、普通ならそんなことは気にしない。何しろ、 本物の紳士たる者、たとえ全財産を失っても、決して動じてはならん！金など紳士にとっては取るに足らぬもの、 気にする価値もないはずだ。しかし最悪なのは、 やつらが私の壮麗なペルシャのシャムシール剣コレクションまで持ち去ったことだ！新世界にも旧世界にも、 あれほどのコレクションは他にない。本当に見事なペルシャ騎兵刀なのだが……\n";
			link.l1 = "ペルシャの剣だって？それはなかなか興味深いね。つまり、君は収集家ってことかい？";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "そうだな、俺は珍しい物を集めるのが好きでね……聞いてくれ、シャルル、もしかしたらこの件でお前に手伝ってもらえるかもしれないんだ……";
			link.l1 = "助ける？でもどうやって？盗賊を捕まえるってことか？";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "いいや。盗賊どもには特に興味はない。私のペルシャ騎兵刀を取り戻したいだけだ。もし見つけてくれたら、 必ず礼はする、約束しよう。";
			link.l1 = "ふむ。でも、どこを探せばいいんだ？カリブ中か？それとも世界中か？";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "まあ、島のどこかの露天商で見かけるかもしれねえな。 あいつら悪党どもはあの騎兵刀の価値なんざ分かっちゃいねえから、きっとガラクタ同然で売っちまうだろうさ。だから、 もしペルシャの剣をどこかで見つけたら、俺のところに持ってきてくれ。見分けはつくか？";
			link.l1 = "そうしようと思う。よし、しっかり目を光らせておくよ、もし話に合う変わった剣を見かけたら、 必ずあなたのもとに持ってくる。";
			link.l1.go = "Sharlie_12";
			link.l2 = "実は、私は高級な武器については詳しくないんだ。残念だけど、君の力にはなれそうにない。だから、 無駄な期待を持たせるのは不誠実だと思うよ。";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "ホロショ！運よくその遺物を見つけてくれることを願っているよ、そうしたらちゃんと報酬も用意するぜ。 狩りの幸運を祈る、ストーカー…いや、船長！ダ、シャルル、想像できるか、最近また強盗未遂があったんだ！\n数日前に泥棒が俺の家に押し入ろうとしたんだ\nさすがに頭にきたぜ！だが今回は逃がさなかった、しっかり捕まえて、 たっぷり殴ってから町の牢屋の衛兵に引き渡してやった。早く絞首刑になればいいんだがな！";
			link.l1 = "あいつがあんたのシャムシールを盗んだ盗賊の一味だと思うのか？";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "残念だけど、ないものねだりしても仕方ないわ。そうよ、シャルル、信じられる？最近また強盗に狙われたのよ！\nほんの数日前、泥棒が私の家に押し入ろうとしたの。\nもう我慢の限界だったわ！でも逃がさなかったわよ。私が捕まえて、しっかり懲らしめて、 地元の牢屋に送り込んでやったの。他人の不幸の上に幸せなんて築けないわ。早く絞首刑になればいいのに！";
			link.l1 = "あいつがあんたのシャムシールを盗んだ泥棒の一味だと思うのか？";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "いや、そうは思わない。奴は金目当てだった。俺の部屋で箱を漁っているところを捕まえたんだ\nスペイン領本土の奥地から来たインディアンさ。ここの連中とはまるで違って、滑稽なほど奇妙な格好をしている。 全身に戦化粧を施し、派手な衣装を身につけてな……興味があるなら、あの道化を見に地下牢へ行ってみるといい。まだ生きているうちにな。";
			link.l1 = "ふむ……ちょっと寄って彼に会ってみるか。";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "さあ、見世物小屋を覗いてこいよ……よし、シャルル、いい話だったな。マルティニークへの帰路、順風満帆を祈るぜ、poputniy veter！";
			link.l1 = "ごきげんよう、ファディ。";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "面白いじゃないか！聞かせてくれ。";
			link.l1 = "ファディ、あのインディアンと話をしたんだ。それで君のところに来て、彼を助け出す手を貸してほしくてな。 あの可哀想な奴は、ただ何か食べたかっただけなんだよ……";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "ははは、その話を信じたのか？最近の若い奴らは本当に騙されやすいな……";
			link.l1 = "ファディ、俺はお前より若いかもしれないが、正直に話されてるのか嘘をつかれてるのかくらい、俺にも分かるさ。\nそれに、そんな罪で絞首刑が妥当な罰だと思うのか？やりすぎだろう。故郷なら、せいぜい鞭打ちか、 再犯者には焼き印を押されるくらいだぜ。";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "やりすぎだと！？あいつは俺の家に押し入ったんだぞ！あんな野蛮人、ここに来るべきじゃなかったんだ！ お前が俺の立場だったらどうする？きっとあいつの内臓をぶちまけて、虫の餌にしてやるだろう、なあ！？";
			link.l1 = "いや、しないさ、ファディー。お前はまだ自分のシャムシールのコレクションを盗まれたことに腹を立ててるだろう。 もしあれがなけりゃ、このふざけた赤肌野郎にもっと痛い目を見せて、 ケツに蹴りでも入れてやる気になってたんじゃねえか？俺が間違ってるか？";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "あああ、シャルル……お前は兄貴そっくりだな……よし。ここは正直な商人同士らしく決着をつけようじゃないか。どうしてもこのインディアンが欲しいなら、 奴が引き起こした精神的苦痛と財産への損害を補償してくれ。その代わり、私は司令官に訴えを取り下げると伝えよう。 どうだ？";
			link.l1 = "いくらだ？";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "はは、シャルル、お前もカリブのやり方を覚え始めてるな。金貨ドゥブロン150枚、1コペイカもまけねえぞ。";
			link.l1 = "ファディ、神よお慈悲を……";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "よしよし、40枚の金ドゥブロンだ。それが最終価格だぜ。ペソじゃなくてドゥブロンな。うちの金貸しならきっと持ってるはずだ。";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "今、必要な額は持っている。ほら、40ドゥブロン受け取れ。";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "（信頼できる）ファディ、聞いてくれ……君の苛立ちは分かるが、この面倒に対して本物の金で補償しようとしているのは俺だけなんだ。";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "わかった、必要なものを取ってきてやる。";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "おお、お前は大物になるぜ、友よ。説得された！３５枚の金貨――これより一枚もまけねえぞ！";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "急げ、シャルル！処刑まであと十日しかないぞ。";
			link.l1 = "覚えておくよ。じゃあな！";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "よろしい。今すぐ書状を書いて印を押そう、ちょっと待ってくれ……はい、できた。これを司令官に渡せば、そのインディアンを連れて行っていいぞ。 なぜそんなに彼のことを気にするのかは分からんが、それはお前の問題だ。さて、どうするつもりだ、 仮面舞踏会で見世物にでもするのか？はは、面白い考えだな！";
			link.l1 = "神はすべてを見ておられるぞ、ファディ。人の命を救うのは高貴な行いだ。";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "最初の意見には同意するが、二つ目は議論の余地があるな、シャルル。もしお前が、 絞首刑を待つ殺人者や強姦犯を救ったとしたらどうする？\nふん、まあ、もう俺の問題じゃねえ。神のご加護を。お前の赤い肌の友が首に縄をかけられて青ざめる前に、 司令官のところへ行けよ…";
			link.l1 = "今行くところだ。また後でな、ファディ。";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "顔が険しいな、友よ！悪い知らせを持ってきたんじゃないか？";
			link.l1 = "それが事のすべてだ、ああ。正直に言うぜ、ファデイ。ミシェルが言ってたんだ、お前がこの「酋長の爪」 とかいうガラクタで俺を騙したってな。これは遺物なんかじゃなくて、 どこの露店商からでも数百ペソで買える代物だってさ。俺も金物を扱う露店商に聞いて回った。 まさにその値段を提示されたぜ。";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "ああ、ド・モール様……私は傷ついております！あなたのご兄弟には驚かされました。 街の半端者どもが何を言おうと好きにさせておけばいいですが、彼が！シャルル、教えてください、 もし誰かがカール大帝の時代の古い両手剣を持ってきて、あなたに売ろうとしたら、あなたはいくら出しますか？\n";
			link.l1 = "両手剣だと？ふざけてんのかよ、ファディ？そんな錆びついた死刑執行人の刃なんて、俺に何の役に立つってんだ？ 今は我らが主イエス・キリストの十七世紀だぜ！そんなもんに一ペソだって払う気はねえよ！";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "ああ、ほら見ろ、君の近視眼的な考え方だよ、友よ！そんな態度じゃどこにも行けやしないぜ。それに、 もし君がそんな遺物を俺に持ってきたら、三百ドゥブロン払うさ。なぜかって？それは骨董品であり、 歴史的なお宝であり、今の時代じゃなかなか見つからない代物だからだ！君は理解せずに、すぐに判断する！ 神と聖母マリアに誓って言うが、酋長の爪は傑作の短剣だ――俺の情報筋によれば、コルテス本人が持っていたらしい。あのエルナン・コルテスだぞ！伝説の征服者、 テノチティトランを陥落させ、アステカ皇帝を捕らえた男だ！それを君は鼻で笑って、ただのガラクタだと言うのか！ それに、俺はもう言ったはずだ、これはただの短剣じゃない――魔法がかかった短剣なんだ！カリブの不思議をまだ全部見てないほど青いのか？呪文や魔術、儀式や呪いを知らないのか？ シャルル、ここは新世界、マヤやアステカの故郷だぞ。奴らの悪魔的な技術の知識は、我々 キリスト教徒には想像もつかない高みに達していた！この短剣には隠された力がある。残念ながら、 まだ誰もどんな力か知らない。君には、その力が何なのか自分で確かめるという、 唯一無二の素晴らしいチャンスがあるんだぞ。それなのにまだ『クソみたいなもの』だとか、 親愛なる哀れな古い友人のファディーが君を騙そうとしたとか言うのか！もし俺に君の兄貴への借金を返す金があれば、 すぐにでもその忌々しいコインと引き換えに取り戻すさ……これはとても貴重な品で、その価値は金だけじゃ測れないんだ、だ！";
			link.l1 = "わかった、わかった、落ち着けファディ。君のことは信じるよ。君の主張はなかなか説得力があるし、 その熱い情熱は誠実さの証か、あるいは比類なきペテン師ぶりのどちらかだな。";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "スパシーバ！よくやったぞ、シャルル、気を悪くせずに直接私のところへ説明を求めに来てくれて。 これで問題は解決したと信じていいかな？";
			link.l1 = "はい、ファデイ様。まったくその通りです。では、どうかこれで失礼させていただきます……";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "待て、シャルル！正直に言うと、お前のやり方、俺は気に入ってるぜ。もしかしたら、 いつか俺たち親友になれるかもしれねえ。だったら今、その第一歩を踏み出してみねえか？ 地下の貯蔵庫で極上のロシア産ウォッカを二本、冷たい湧き水で冷やしてあるんだ。どうだ、 兄貴の健康を祝って一本開けようじゃねえか？\n";
			link.l1 = "ふむ。申し訳ありません、Fadey様、しかしもう出航の時間です。少々急いでおります。";
			link.l1.go = "vodka_no";
			link.l2 = "前回は君が申し出てくれて、俺は断った……二度も断るのは失礼だな。よし、ファディ、乗ったぜ！";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "それは残念だな。ウォッカに比べりゃ、ラムなんてただの水みてえなもんだ、安っぽくて薄い酒さ。だが急いでるなら、 これ以上引き止めねえよ。狩りの幸運を祈るぜ、シャルル！";
			link.l1 = "「あなたも同様です、Fadey様……」";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "それを聞いて嬉しいよ！素晴らしい！どうぞ座って、足を楽にしてくれ！どうぞ、旦那、私がウォッカを取ってくる間、 ごゆっくりなさってください。ああ、友人たちとのこんな午後の集まりが本当に懐かしかった！ああ、 ウォッカはよく冷えてるから、きっと気に入るはずだ、ナズドローヴィヤ！ピクルスと燻製ハムも並べておこう。";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "おおっと……で、教えてくれよ、ファデイ、そ、それってどういうことなんだ？ひっく！俺たち……ウオッカを二本も飲んだんだぜ……ちなみに！――お前はし、しらふそのもので、俺は……ベロベロに酔っ払ってる。な、なんでだよ、ああ？";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "シャルル、友よ、落ち着けよ。イタチなんてこの話に何の関係があるんだ？俺たちは今、 最高のウォッカを飲んだばかりだろう。少し寝れば、目もぱっちり、元気いっぱいで起きられるさ。二日酔いも残らず、 頭もすっきりするぜ。わかるさ。";
			link.l1 = "あ、ああ、ウォッカか……こ、これは本当に素晴らしい、ウォッカだよ。こんな酒、今まで飲んだことがない。";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "ははっ！その通りだぜ！ああいうウォッカは秘密のレシピで作られて、俺の祖国ロシアから運ばれてきたんだ。 向こうでもちゃんと作れる奴はそう多くねえ。俺は最高のものしか買わねえ！お前と俺が今飲んだこれみたいにな。";
			link.l1 = "で、でもさ、ファディ、ど、どうしてそんなに酒を飲んでも酔っぱらわないんだ？ど、どうやってるんだよ、なあ？ その秘密、俺にも教えてくれよ。も、もしかしたら後で役に立つかもしれないし……ひっく！";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "ははっ！まあ、お前は俺と比べられねえよ、若造のシャルル！その細っこい体を見てみろよ。しかも、 本気の飲み方には慣れてねえだろう？だがな、俺たちは本当の友だから、特別に酒の飲み方と、 酔っても漏らさねえコツを教えてやるぜ。\n";
			link.l1 = "お、おねがい…ひっく！";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "さて、飲みたいけど一気に潰れたくないなら、いくつか大事なルールを守らなきゃならねえ。まず一番大事なのは、 空腹で酒を飲むなってことだ。飲み始める前にしっかりしたもんを食っとけ\n二つ目は、一杯飲むごとに何か食うのを忘れるな。肉か魚が一番だ、塩気のあるやつがいいぜ。三つ目は、 ウォッカで口をすすぐな、すぐに飲み込め\nそれから、メインの料理の前に小さなショット――せいぜい半パイントまで――を飲んでおくと、体が本格的な酒に備えられる。この前菜をやりすぎるなよ、 逆効果になって出航前に自滅する羽目になるぜ\n最後に、鍛錬が肝心だ。ラム酒や他の酒を適量ずつ定期的に飲むことで、酒に強くなれるんだ。";
			link.l1 = "ふむむ…そ、そうやってやるんだな！ぜ、絶対に…ひっ！…お前の指示、全部覚えておくよ、ファディ。あ、ありがとう。そ、それじゃ今はちょっと…ね、寝たほうがいいかもな、今あんまり気分よくないし。";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "休んでくれ、シャルル。今夜は楽しかったな、俺たち！狩りの幸運を祈るぜ！";
			link.l1 = "ど、ど、どすヴィダーニヤ、ファディ！俺はこれから――ひっく！――願いを叶える者のところへ行くぜ！";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "「何だって、俺が君を助けるなんて本当に言ったのか？」";
			link.l1 = "まあ、そんなところさ。長年の友の兄貴に手を貸してくれないか？物乞いみたいに施しを頼んでるわけじゃねえ。 稼ぐチャンスをくれって頼んでるんだ。";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "ああ、シャルル！遅かったのね。もっと早く来てくれたら、あなたにぴったりの仕事を見つけてあげられたのに、今は――ごめんなさい。\n心配しないで、町を歩き回って、人々と話してごらんなさい。カリブにはやることがたくさんあるわ。";
			link.l1 = "なるほど、それは残念です。さようなら！";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "ふむ。いや、もちろん断ったりはしないさ。人に食べ物を与えたいなら、魚をやるんじゃなくて釣り竿を渡せ、 って言うだろう？そうだよな、ド・モール旦那？つまり仕事が欲しいってわけだな……簡単なことだ。知り合いに話をつけて、お前を推薦してやるよ。あとは全部、 お前がその仕事をどれだけうまくやるかにかかってるぜ。";
			link.l1 = "素晴らしい。誰に話せばいいんだ？";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "明日店に来い。ジェラール・ルクロワという男がそこでお前を待っている。仕事をくれるはずだ。 あいつはこの植民地に明日の夕方までしかいない。早く会って、きちんと仕事をこなせ。俺を困らせるなよ。";
			link.l1 = "取引成立だ。ありがとう、Fadey！";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "ああ、どうしたんだい、友よ？";
			link.l1 = "ファディ、聞いてくれ。本当に密輸業者から奴隷を五十人買う必要があるんだ。問題は、 俺はあいつらにとって無名の存在で、君に紹介してもらわないといけないってことさ。君がいなきゃ、 話も聞いてくれないし、これはとても大事な人物の命に関わることなんだ。";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "おおっと！商売を拡大しているんだな！なんとも儲かりそうじゃねえか！手伝ってやるぜ、親友よ。だが知っての通り、 俺はタダじゃ動かねえ。売り手にお前の善意を信じさせて黒人たちを買わせるには、金貨ドゥブロン150枚が必要だし、もちろん俺の骨折りにも少し上乗せしてもらうぜ…";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "さすがだな、ファデイ様！ほら、これが約束の金貨だ。";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "すぐに高利貸しのところへ行ってくる！待っててくれ、ファデイ旦那、すぐ戻るからな！";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "ファディ、どうやらいい案が浮かんだから、もう黒人たちは必要なくなったよ。すまない。またな！";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "素晴らしいな、友よ。だが、この取引の必要性について俺を騙そうとしているなら、 そしてお前の意図がくだらないものなら、俺は本気で怒るぜ。そんなことは望まないだろう。明日十時、 日没時にキャプスタービーチでお前のために会合を用意する。俺を失望させるなよ。";
			link.l1 = "心配いらないさ、品物はちゃんと取りに戻るぜ。";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "やあやあ！さて、旦那、こんなつましい我が家に何の用で？";
			link.l1 = "武器が必要だ。地元の商人たちじゃ俺の求める量は用意できねえが、あんたなら助けてくれると思うぜ。";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "まずは教えてくれ、親愛なる友よ、君が正確に何を必要としているのかを。\nそれから、私が力になれるかどうか答えよう。";
			link.l1 = "30丁の兵士用ピストル、マッチロック式マスケット銃2丁、それ用の弾薬70発、そして回復薬90本が必要だ。";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+"、君は私を怖がらせているよ。最初は五十人の黒人、次は武器だ。友よ、奴隷の反乱でも起こすつもりか？";
					link.l1 = "さすがだな、ファディ。先ほども言ったが、これはすべてある重要人物を救うために必要なことなんだ。心配するな、 スペイン人の手から必ず助け出すから、お前のここでの評判が傷つくことはないさ。";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "それは良い知らせです。お手伝いできます。";
			link.l1 = "それは嬉しいです。いくらですか？";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "説明してくれて嬉しいよ。そして、もし本当にこれがスペイン人に関係しているなら、俺も手を貸そう。\nだが、もし俺を騙していたと分かったら、すごく怒るからな。";
			link.l1 = "俺をもう少し信じてくれよ、ファディ。いくらだ？";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "よし、それじゃあ…ピストル数丁とマスケット銃、それぞれの火薬と弾薬だな…だから…君が頼んだものをすべて必ず用意できるとは約束できないが、できる限りのことはするつもりだ。その間に、 頭金として四万ペソ、もしくは希望なら七十五ドゥブロンが必要だ。";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "ドゥブロン金貨を持っていけ、ファディ。ちょうど今、俺がいくらか持ってるんだ。";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "俺のドゥブロンは全部なくなっちまった、ペソで受け取ってくれ、ファディ。";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "私の銀行家と話す必要があるんだ。すぐ戻るよ！";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "すまない、ファディ、でも今は払えないんだ。自分でなんとかしてみるよ。またな！";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "「明日来てくれ」 "+pchar.name+"、それで必要な材料を用意しておくよ。";
			link.l1 = "それじゃ、お邪魔しないよ。じゃあ、また明日！";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "「明日来い」 "+pchar.name+"、それと必要な材料も用意しておくよ。";
			link.l1 = "それじゃ、お邪魔しないよ。また明日！";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "さて、坊や、こんなに時間がない中で君が頼んだものを全部見つけられたのは運が良かったんだぞ。感謝してほしいね！ さて、最後の支払いだ。前金と同じ額をきっちり払ってくれ、それで武器を持っていきな。";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "７５ドゥブロン受け取れ。俺の部下に武器を船まで運ばせる。お前がいなかったらどうなってたか……ファディ、俺がどれだけ助けられたか、お前には分からないだろう！";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "4万ペソ受け取れ。俺の部下に武器を船まで運ばせる。お前がいなかったらどうなってたか……ファディ、どれだけ助けられたか分かってないだろうな！";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "くそっ、金を忘れるなんてありえねえ！すぐ戻るぜ。";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "すまない、ファディ、俺はすっからかんだ。手付金は取っておいてくれ。この取引の経費をまかなえるといいんだが、 あとは自分でなんとかしてみるよ。またな！";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "困っている人を助けるのは名誉なことだ。報酬をくれる人を助けるのは楽しいことだ。\n次にバステールに来る時は、ぜひ挨拶に立ち寄ってくれよ。";
			link.l1 = "ばかばかしいな――バステールにいて親友のファデイに会わないなんて！また今度だ！";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "困っている者を助けるのは名誉だ。だが、報酬をくれる者を助けるのは喜びだぜ。\n次にバステールへ来たときは、ぜひ俺のところに挨拶に来てくれよ。";
			link.l1 = "馬鹿げてるぜ――バステールにいて親友のファデイに会わないなんてな！また今度な！";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "なんてとんでもない企みを仕掛けたんだ、 "+pchar.name+"！志は高潔でしょうが、それが実現可能かどうか……二十年もあれば人は何にでも変わってしまうものです……";
			link.l1 = "その通りだ、ファディ。しかし、俺たちは多くの時間と労力を費やし、長い道のりを歩んできた――そして、もうすぐ目標にたどり着くところだ。彼についてはほとんどすべてを突き止めた。名前、 国王陛下の王立海軍での勤務、乗っていた艦の名前……そして他にもいくつか経歴の詳細が分かった。足取りは1638年6月、カトーチ岬沖で起きた難破で途切れている。\n";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "カトーシュ？おお、旦那、俺なら棒で追われてもあんな場所には行かねえよ――あそこには呪われた野蛮人どもがうようよしてるんだ。もし奴がそこに辿り着いて、海で死ななかったんなら、 神に誓って間違いなく、あの忌々しい土人どもに食われちまっただろうさ……";
			link.l1 = "この男が難破から生き延び、その後キューバにたどり着いた証拠がある。\nおそらくそこで命を落としたかもしれんが、聞くところによれば、異端審問官の手から逃れるほど狡猾だったらしい。\nキューバに留まったとは考えにくい――むしろ諸島のどこかの集落に身を落ち着けた可能性が高い……";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "この世には多くの不思議が起こるものだ、友よ、何があってもおかしくはない。\nだが、それでも君がなぜこんな話をしたのか、私にはまだ分からない。";
			link.l1 = ""+npchar.name+"、お前は一部の総督よりもよほど顔が広いじゃねえか。きっと身の回りに、 簡単な仕事くらいこなせる腕利きの連中がいるだろう…";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+"、あなたは尊敬され、影響力のある方です。上流社会で活躍し、幅広い人脈をお持ちでしょう。 きっとビジネスの利権もグアドループをはるかに超えているはず。これほどのことを一人でこなすのは不可能ですから、 信頼できる代理人や、あまり複雑でない任務を遂行できる賢い者たちを使っているのでしょう…";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "「あなたは賢くて洞察力のある男ですね」 "+pchar.name+"。確かに、それは以前にも言われたことだ。腕も知恵もある男たちは揃っている、その通りだ。だが、 はっきり言ってくれ――お前は彼らに何をさせたいんだ。";
			link.l1 = "諸君には、探している男について何か情報を得るため、諸島のいくつかの植民地に使者を送ってもらいたい。\n誰かが彼のことを聞いたことがあるか、あるいは実際に知っているかもしれないからな。\nもちろん、費用はすべて私が負担しよう。 "+npchar.name+"、これはメアリーにとってとても大事なことなんだ、他に頼れるところがないんだ。";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "「あなたは賢くて洞察力のある男ですね」 "+pchar.name+"。確かに、それは以前にも言われたことだ。腕の立つ者や知恵のある者は揃っている、その通りだ。だが、 はっきり言ってくれ——お前は奴らに何をさせたいんだ。";
			link.l1 = "諸君には、我々が探している男について何か情報を得るため、諸島のいくつかの植民地へ行ってもらいたい。\n誰かが彼のことを聞いたことがあるか、あるいは実際に知っているかもしれん。\nもちろん、費用は全て私が負担しよう。 "+npchar.name+"、これはメアリーにとってとても大事なことなんだ、他に頼れるところがないんだ。";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "「君のような良き友を断れるだろうか、」 "+pchar.name+"？特にあなたがこの神聖な件に金を使う覚悟があるのならなおさらだ。では、探したい男の名前を教えてくれ。";
			link.l1 = "名前については確かじゃないが、ルパート・キャスパーかジョシュア・ノースウッドと呼ばれていたような気がする。";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "よし、その名で呼ばれていた奴なら探し出してやるさ…";
			link.l1 = "「素晴らしい」 "+npchar.name+"。あなたの働きへの報酬について話し合いましょうか？";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "不愉快なことだが、残念ながら必要なことだ。";
			link.l1 = "それでは始めよう。奴がスペイン人やオランダ人の中に飛び込むような危険を冒すとは思えん。 アンティグアでは厄介ごとを起こして出ていったから、そこを探しても無駄だし、バルバドスにも多分いないだろう。 西インド本土や、スペイン人が追い出された後のジャマイカ、フランス領の植民地、 そしてもしかしたら海賊の集落に身を落ち着けているかもしれん。";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
				case "WildRose_Fadey_11":
			dialog.text = "はっきり言わせてもらうよ、親友よ。俺がバステールで暮らしてきた間、 そのどちらの名前の紳士も聞いたことがないんだ。だから、ここで探す必要はないぜ。\nマルティニークやセントクリストファーならイギリス紳士を何人か知ってるが、そいつもその中にはいないよ。";
			link.l1 = "それなら捜索範囲はかなり絞られるな。";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "トルトゥーガは必ず調べねばならん——同じ者にラ・ベガ、プエルト・プリンシペ、ポルトープランスも回らせよう。 腕の立つ部下たちをベリーズとブルーベルト、それにジャマイカとイスラ・テソロにも派遣するぞ。";
			link.l1 = "「で、全部でいくらかかるんだ？」";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "彼らは知識もあり勤勉な男たちだ、だから一人につき百五十ドゥブロン払ってもらうぞ。\nトルトゥーガとイスパニョーラ、さらにキューバへ派遣する使者には特別報酬をやろう――金貨五十枚を上乗せだ。\n何しろ、四つの植民地は一つじゃないからな。";
			link.l1 = "それでは合計で800ドゥブロンですね……お勘定の精算に進みましょうか？";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "そうだな、時間を無駄にすることはないだろう？必要な金額は持っているのか、旦那？";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "もちろんだ。ほら、受け取れ。";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "ふむ……全額は手元にありません。";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "素晴らしいですな、親愛なる友よ！すぐに私の代理人たちに書面で命令を出しましょう、彼らはすぐに動き始めます。 向こうへ向かう船を探す必要がありますので、少々時間がかかります。旅そのものも風の強さ次第でございますし、 それは我らが主のお導きにかかっております。しかし、私の部下たちは一ヶ月以内には戻るはずだと理解しております。";
			link.l1 = "「では、一ヶ月後に会おう。」 "+npchar.name+"。改めて感謝します。とても助かりました。それでは、また！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "「承知しました」 "+pchar.name+"、かなりの額です。用意できたら私のところでお待ちしています。";
			link.l1 = "すぐ戻る。";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "お前の件は覚えてるぜ、親友。八百ドゥブロンは用意できたんだろうな？";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "お待たせしました、Fadey様！こちらが約束通りの金貨です。すべて取り決め通りですよ。";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "まだ必要な金額を集めている最中だが、心配するな——そう長くはかからないさ。";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "うまくいったぞ、友よ――いや、本当に大成功だ！俺の部下たちは、たった一つのものだけを持って戻ってきた。 ベリーズに送り出したジェローム・ソヴェルニエだけは戻らなかったが、知らせをよこした。君にとって良い知らせだ。";
			link.l1 = "彼があなたに手紙を送ったのか？読んでもいいか？";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "「もちろん」 "+pchar.name+"。君が読みたがると思って特別に取っておいたんだ。どうぞ、友よ。";
			link.l1 = "ありがとうございます、今から読ませてもらいます。";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "「そんな笑顔を君の顔で見るのは久しぶりだな、いい男！」";
			link.l1 = "「なるほどな、」 "+npchar.name+"！こんなに長く待ったんだ！でもな、俺たちは成功を信じてたぜ！どう感謝すればいいかわからねえ、 お前がいなきゃ成し遂げられなかったんだ。";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "おやめなさいよ、勇敢な方！あなたは私の友人ですもの、友人同士は助け合わなくてはなりませんわ。 すぐに戻ってきてくださいね——ジェローム旦那もきっとすぐ回復して、最初の船に乗るでしょうから……";
			link.l1 = "事を急ごうと思う。俺たちで直接ベリーズへ行って、お前の代理人と話すとしよう。改めて礼を言うぜ、\n "+npchar.name+"。あなたが私たちにしてくれたこと、想像もできません！また会う日まで！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "あなたの船で働いている親愛なる友人、アロンソ・ピメンテルのことか？ははっ！もちろん知っているさ。 君の船が港に入るたびに、あの男は必ず一杯やりに寄ってくるんだ。私に残された友人は、もうわずかしかいないがね。 "+pchar.name+"。どれも私の宝物です。";
			link.l1 = "アロンソがあなたの戦争での冒険について素晴らしい話を聞かせてくれたわ。\nそれに、あなたの弾薬帯まで私にくれたのよ。";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "彼が最も素晴らしい話は自分だけのものにしておいたと、私は願い、信じております。しかし、 アロンソがあなたとも友情を分かち合った以上、私もあなたに興味が湧きました。\nさあ、ご覧なさい！";
			link.l1 = "それは……鎧か？";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "ああ、友よ。これは、あの忌まわしい戦争の時に私が着ていた鏡鎧の残り物だ。そして後に、 スモレンスク近くで私は機会があって\n"+
			" そうは言っても、この状態でも見事なものだし、防御力も抜群だ。\nそれに、もう俺にはまったく似合わなくなっちまった！";
			link.l1 = "異国情緒があるな……この辺りでも珍しいくらいだ。素晴らしい贈り物だ、ファディ。ありがとう。";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "お前のためなら、友よ、たった千ドゥブロンでいいぜ。";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "訂正させていただきますわ、親愛なるファデイ。千ドゥブロンなら鎧一式のお値段ですの。でも、胸当てだけなら？";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "お前とアロンソが気が合うのも無理はねえな。ほら、これが約束の金だ。";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "ははっ！危うく引っかかるところだったぜ、ファデイ！また今度にしようじゃねえか。";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "もちろん、急ぐ必要はありません。私の鏡の鎧はいつでもあなたを待っていますよ。";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "おお、なかなか鋭いな！よし、それなら六百金貨で譲ってやろう。";
			link.l1 = "お前とアロンソが気が合うのも当然だな。ほら、これが金貨だ。";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "良い取引だ。感謝する、そして私の鏡鎧をしかるべき手に託そう。アロンソのことも頼むぞ、船長。";
			link.l1 = "ここで誰が誰の世話をしてるんだか……";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "良い取引だ。感謝する、そして私の鏡の鎧をふさわしい手に託そう。アロンソのことも頼むぞ、船長。";
			link.l1 = "ここで世話してるのは一体どっちなんだ……";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "さて、商用で来たって疑う奴はいねえよ、友よ！残念だが、今はウォッカの振る舞いはできねえ、 全部飲んじまったからな。で、今度はどんな厄介ごとに巻き込まれてるんだ？";
			link.l1 = "ある私掠船乗りが自らの罪の許しを求めて、地元の教区に金製のラピスラズリ付き胸十字架を献上したそうです。 これは非常に珍しく貴重な品です。\nしかし問題なのは、この十字架が別の教区から盗まれたものであることです。それだけでなく、 強盗の際に神父が殺害されました。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ああ、無垢なる生神女よ！それは驚きだな！";
			link.l1 = "ああ。私は盗まれた信者たちを代表しており、十字架を本来の持ち主に返そうとしている。";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "高貴な行いだな、しかもずいぶん敬虔じゃねえか。全能の神にご機嫌取りでもしてるのか？";
			link.l1 = "だが、地元の神父は、俺が何を言っても返してくれねえんだ。\n理解できねえよ。どうして平然と、無実の男の血で汚れた盗まれた十字架を神の家に置けるんだ？\nそれは冒涜じゃねえか！";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "さて、厳密に言えば、聖別された聖杯にはすべて無垢なるキリストの血が注がれております……が、話が逸れましたね。私にご助力をお求めですかな？";
			link.l1 = "そうだ！バステールであんたの影響力は大きい。周囲からも一目置かれてるし、 神父もあんたの忠告なら耳を傾けるかもしれねえな。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+"「この盗まれた十字架の話を、うちの神父に正確に話したのか？」";
			link.l1 = "もちろんだ！俺はあいつの信仰心にも、キリスト教の連帯にも、くそったれな良心にだって神に誓って訴えたが、 やつは耳を塞ぎやがった。";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "ふむ……他に何か説得する方法を試してみたのか？";
			link.l1 = "賄賂を渡せってことか？俺は神父に賄賂なんか渡さないぞ。もし相手が銀行家とか商人とか、あるいは総督なら、 そうやって問題を解決しようとするかもしれないが、神父には無理だ！";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "親愛なるお人好しの友よ、もし神父の耳が本当に良心の訴えに閉ざされているのなら、 きっとその手は金には開かれているだろう……いや、もしかすると逆かもしれないな。手を貸そう。こんな穢れた財宝をここに置いておけば、 いずれもっと大きな厄介事を招くに違いないからな。だが、それには多少の出費が必要になるぞ。";
			link.l1 ="なぜ驚かないんだろうな？今回はいくらなんだ？";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "「明日また来てくれ」 "+pchar.name+"、まだ値段は言えません。しかし、その盗まれた十字架は必ず手に入りますので、ご安心ください。";
			link.l1 = "わかったよ、Fadey。これ以上邪魔しないさ。じゃあ、また明日な！";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "約束通り、十字架は手に入れた。詳細については……まあ、忘れてくれ……すべては尊き救世主の流された血によって赦された戯言さ\n";
			link.l1 = "「俺がいくら払えばいいんだ？」";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "二百五十ドゥブロンだ。俺の経費のためにな、もちろん正義の助けにちょっと上乗せしてくれたらありがたいが……";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "あいよ、Fadey旦那。ほらよ、あんたの金だ。";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "自分の船室から金貨を取ってこなきゃ。すぐ戻るぜ。";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "よし。これが盗まれた十字架だ。";
			link.l1 = "ありがとう、Fadey。君がどれほど助けてくれたか、想像もつかないよ！";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "親切で――いや、それ以上に気前のいい友人を助けるのは、いつだって嬉しいさ。\nもっとちょくちょく顔を出してくれよ。母国からウォッカが届いたら、一緒に飲もうじゃねえか。";
			link.l1 = "喜んで！";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "ほうほう、まだ海に呑まれてはいないようだな！さて、今回はどんな不運が俺のもとへお前を運んできたんだ？";
			link.l1 = "それが不運と言うべきかどうかは分からないが、とにかく俺はここにいる。\nファディ、初めて会った日にお前は俺に珍しい短剣、酋長の爪をくれたな。今では、 それがかつてアーチボルド・カルフーンという男の物だったと知っている。\n頼む、この男について知っていることを教えてくれ。";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "「あなたには何も隠せませんね。」 "+pchar.name+"。何もかもお見通しだな、君も兄上と同じだ。そう、この短剣はカルフーンからサイコロ勝負で手に入れたんだ。 彼が誰かって？俺にもさっぱり分からない。酒場で偶然出会って、話し込んで、何杯か飲んだら、 彼は自分の過去の罪について語り始めたんだよ……";
			link.l1 = "お前はあいつの告解者か？どんな罪だってんだ？";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "アーチボルドは、自分のせいで異端審問に拷問されて死んだ男や、 彼が殺した他の無実の魂たちの記憶に取り憑かれていた。自分のことをユダだと呼び続け、神が自分の罪を罰している、 異端審問が自分を追っていると言っていた。スペインの異端審問官ヴィンセンテ自身が彼の死を望み、 カリブ中に傭兵を差し向けて追わせているとも話していた。だが、やがて酒に飲まれ、 俺たちはこの古い短剣を賭けて博打をしたんだ。";
			link.l1 = "それだけか？もう二度と彼に会わなかったのか？";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "もちろん違う、今はもう死んでいる。哀れな海賊どもが彼のフリュート船をデイヴィ・ジョーンズの棺桶に沈め、 乗組員全員をミクトランテクートリのもとへ送ったんだ。実を言えば、 噂では彼らは海賊の格好をしたプロに襲われたらしい……異端審問官の手先だと。ヴィンチェント神父は必ず標的を仕留める、そう言われている。";
			link.l1 = "アーチボルド・カルフーンは生きている。つい最近、ウィリアム・パターソンとかいう男と一緒にいるのを見た。 彼はその男の副官を務めているんだ。";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "おお、これは驚いた！アーチボルドは少なくともパターソン船長の庇護下で一息つけるってわけだ。 いい仲間に恵まれたな。スペイン人どもはパターソンを疫病のように恐れている。パターソンの守りがある限り、 アーチボルドに陰謀を企むなんてできやしねえさ。";
			link.l1 = "「パターソンを知っているか？」";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "ウィリアム・パターソンを知らない奴なんているか！？あいつはお前と同じくカリブに来たばかりの新参者だ。だが、 お前と同じで、すでに名を轟かせているぜ。パターソン旦那はフォックス大佐の一番の親友で、 カリブ全英領植民地の総督であるウィンザー卿とも昵懇だ。 よくジャマイカのポートロイヤルにある総督宮殿を訪れているぞ。";
			link.l1 = "了解だ。情報ありがとう、Fadey！";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "おっと、そんなこと気にすんな、友よ。たまには遊びに来いよ！狩りの幸運を祈るぜ！";
			link.l1 = "間違いない！";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "「見てみよう」 "+pchar.name+"…そうだ！それはあいつらの一つだ！さすが俺の息子、今日は最高の日になったぜ！どこで見つけたんだ？";
			link.l1 = "問題ないさ。大事なのは、それがまたお前の元に戻ってきたということだ。";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "君の徹底的な調査には十分な報酬を払おう。三百枚の金のドゥブロンなら、苦労に見合うはずだ……";
			link.l1 = "前に俺からしぼり取ったドゥブロン金貨で支払うつもりか？まあ、もちろん断る理由はねえけどな。ほらよ、 お前のシャムシールだ。";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "ありがとう、友よ！剣と皮肉たっぷりの言葉に感謝するぜ。お前は年の割に賢いな。 "+pchar.name+"、だが人と人との友情の絆は金よりも価値がある。\n金といえば——君への支払いは全額済ませよう。ほら、ドブロン金貨を受け取ってくれ。";
			link.l1 = "ありがとう。";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "「ところで、友情の絆――特に君と私の間のそれについてだが、」 "+pchar.name+"。あなたが非常に興味を持つであろうものがあるんだ。";
			link.l1 = "当ててみようか、またウォッカか？";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "ははっ！ウォッカもうまいが、それだけが俺の国の自慢じゃねえ。ロシアだけが生産できる特別な素材があるんだ。 俺は本国のツテからこの素材を取り寄せて、ここで取引してる。どの船長も欲しがる代物さ、 どんな船でも性能が上がるからな。麻縄のことだぜ\n湿気にも海塩にも強いロープだ。艤装には最高の素材だって評判さ\n毎月、リーヴァルから一定量が届く。だいたい月の半ばには倉庫に何百巻かストックがあるんだ。さて、 "+pchar.name+"、五十巻のロープをまとめて売ろうと思っているんだ。一巻につき十ドゥブロンだぜ\n条件は二つだけだ。まず、お前のロープは毎月二十日まで俺が預かること。次に、まとめて全部買うことだ。 五十巻で五百ドゥブロンだ。ここだけの話だが、 "+pchar.name+"、あの縄をもっと高値で転売できる場所があるって話もあるが、俺には関係ねえさ！\n今の商売のやり方に十分満足してるし、自分で転売先を探す必要もねえ。いい商人を見つけたら、 きっと大きな儲けになるぜ。";
			link.l1 = "了解だ。いい提案じゃねえか、ファディ！せっかくだから、その機会を利用させてもらうぜ。つまり、 毎月二十日に五百ドゥブロンで五十枚ってことでいいんだな？";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "はい。購入品を受け取ってきなさい。しかし、待って、待ってくれ、親愛なるお方！このシャムシールの他にも、 あなたが善意で私に返してくれたもの以外に、あと二振りあったのです。どうかお願いです、もしそれらを見つけたら、 私のところに持ってきてください。返却してくれたら、正当な額以上のお礼をお支払いします。";
			link.l1 = "もちろんだ、ファディ。もし見つけたら、必ず連れて戻るよ。";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "朗報だ。もう一本ペルシャのシャムシールを手に入れたぞ。";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "おお、親愛なる友よ！君のおかげで涙が消えたぞ！ちょっと見せてくれ……ああ！これだ、私の大切なシャムシール！さあ、約束通り、報酬として三百ドゥブロンを渡そう。";
			link.l1 = "「ありがとう！」";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "どうか私の感謝と、ささやかですがとても役立つ贈り物をお受け取りください。私には必要ありませんが、 あなたや船の船大工にはきっと重宝するでしょう\nさあ、この立派な指輪をご覧ください！今やあなたのものです。ただの指輪ではありません、これは魔法の指輪です。 大工仕事や船の修理が得意になります。多くの職人が欲しがる品ですが、特別な時のために取っておきました。 どうぞ受け取ってください、友よ。あなたの負担が少しでも軽くなることを願っています！";
			link.l1 = "お前は本当に面白い遺物をたくさん持ってるな。ありがとう、ファディ！";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "俺の失われたコレクションの中で、残っているシャムシールはあと一本だけだ。頼りにしてるぜ。 "+pchar.name+"、そして運にもかかっている。もし見つけたら、ためらわず私のもとへ急いで戻ってきてくれ。";
			link.l1 = "もちろんだ！またすぐ会おうな…";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "急ぐ必要があるか？剣は俺の手元にあるんだ。";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "「ああ、助けを頼んで本当によかった」 "+pchar.name+"。お前は奇跡の人だな、友よ！見せてくれ……おおお！これは、これは彼女だ。愛しい人よ！クラサヴィーツァ！ありがとう、いい奴だ、礼を言うぞ！ほら、 これがお前の金だ。四百ドゥブロン、コペイカ一つまけないぞ！ケチったりしないさ。";
			link.l1 = "ありがとう、Fadey。お手伝いできて嬉しいです。";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "俺のシャムシールのコレクションがまた全部揃ったぜ！もう誰にも盗ませやしねえ、俺がしっかり守るからな！ お前さんには特別なご褒美があるんだ、いい男だな。二週間後、 商人がヨーロッパから素晴らしいフェンシング用の鎧一式を持ってくる。貴族の注文品で、かなり珍しい鎧だぞ\nだから、もし欲しけりゃ七百枚の金ドゥブロンで買えるぜ。貴族には「輸送中に紛失した」と伝えておくさ。";
			link.l1 = "この鎧の何がそんなにいいんだ？";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "とても着心地が良くて丈夫なのに、鉄の胸当てと同じくらいの性能を持っているんだ。それに見た目も素晴らしい！ 二週間後くらいにまた見に来るといいよ。\nでも、一ヶ月以上経ったら元の客に売っちまうから、それまでには来てくれよ。";
			link.l1 = "取引成立だ。二週間後にお前の家に寄るぜ。";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "はい、すでに届けてありますし、あなたをお待ちしています。金は持ってきましたか？";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "はい。こちらが七百ドゥブロンだ。";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "くそっ。金を船に置いてきちまった。すぐに持ってくるぜ！";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "ああ、いい男だな！ほら、受け取れ。この籐の鎧はきっと役に立つぞ、保証する。カリブ中探しても、 こんなものは他にないからな！";
			link.l1 = "ええ、分かります。ありがとうございます！早く着てみたくてたまらないです…";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "なぜ待つ必要があるんだ？先に進めよ。どれだけ合うか見てみよう。";
			link.l1 = "承知しました。また後でお会いしましょう、Fadey様！";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "どうぞお入りください、親愛なる友よ。商品はご用意できております。二百五十個で二千百二十五ドゥブロンです。";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "すべて約束通りだ。金を受け取れ。";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "ちょっと自分の船室から金貨を取ってくるよ。";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "どうぞお入りください、親愛なる友よ。商品はご用意できております。五百ドゥブロンで五十個です。";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "すべて約束通りだ。金を受け取れ。";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "「ちょっと自分の船室から金貨を取ってくるよ。」";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "ファディ、俺たちの取引量をもっと増やせないか？お前から今の五倍の商品を買う用意があるんだ！ お互いにとって得になると思うぜ。どうだ？";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "ファディ、金を持ってきたぜ！約束通り三千枚の金ドゥブロンだ。";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "「取引できて光栄だ」 "+pchar.name+"。俺の部下に命じて、お前の船にロープを運ばせる。";
			link.l1 = "ありがとう！";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "もしまだ縄がもっと必要なら、ひと月後にまた来てくれ。";
			link.l1 = "よし、Fadey。また後で会おう！";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "おや、親愛なる友よ、私に何か御用かな？";
				link.l1 = "ファディ、あなたは影響力のある男ですね。総督の友人で、噂によれば宮廷にもコネがあるとか。 もし私が法に触れて困った時、当局に嘆願してもらえますか？";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "どうした、友よ？何か手伝えることがあるか？";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "私にはイギリス当局との問題がある。";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "フランス当局とトラブルになっちまったんだ。";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "「密輸業者たちに深刻な問題を抱えている。」";
				Link.l5.go = "contraband";
            }
			link.l9 = "すまないが、自分で何とかできると思う。";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "おほほ、旦那、誰がそんなことを言ったんです？みんな嘘ばかりですよ。でも、あなたはミシェルの弟で、 私の良き友人でもあるから、何とかしてあげましょう。私が口利きできるのはイギリスとフランスの当局だけですが、 私のコネにも限界があります。スペイン人やオランダ人とは取引しませんよ\nそれに、私の影響力で助けられるのは軽い違反だけです。ちょっとした不始末なら、彼らの態度を和らげたり、 怒りを鎮めたりできるかもしれません。でも、戦争でも起こしておいて、私に尻拭いを期待されても困りますよ！\nそれに加えて、一度に手を貸せるのはフランスかイギリス、どちらか一国だけです。 二つの仕事を同時にこなすほど器用じゃありませんからね。もちろん、賄賂には金貨も必要になります。 私の条件が気に入ったら、遠慮なく相談に来てください。";
			link.l1 = "ありがとう、ファディ。覚えておくよ。";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "もちろんです。あなたの冒険――いや、むしろ災難の数々は確かに耳にしておりますよ。あなたのちょっとした問題なら私が何とかしましょう。 適切な額の金貨で適切な手のひらを潤せば、解決できないことなどありませんから。 " + sTemp + " それでお前を鍋から引っ張り出してやるさ。";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "素晴らしい！ほら、金貨だ。";
					link.l1.go = "agree";
				}
				link.l2 = "じゃあ、ちょうど俺がコインを取りに行くタイミングだな。";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "もちろんです。あなたの冒険――いや、失敗談も――確かに耳にしておりますよ。あなたのちょっとした問題も私が何とかしましょう。適切な額の金さえあれば、 解決できないことなどありませんからね。 " + sTemp + " それでお前を鍋から引っ張り出してやるぜ。";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "素晴らしい！ほら、金貨だ。";
						link.l1.go = "agree";
					}
					link.l2 = "それなら、ちょうど俺がコインを取りに行くタイミングだな。";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "ああ、まったく困った状況だな！この事態を完全に解決することはできないが、 これからお前の罪深い頭上に落ちる雷の衝撃を少し和らげてやることはできるぜ。\nそれに、あとで金とその気があれば、またいつでも賄賂を差し出すこともできるからな。 " + sTemp + " それで、あなたの問題を解決し始めることができます。";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "海賊狩りに追い回されるのはもううんざりだ。ほら、金貨だ。";
						link.l1.go = "agree";
					}
					link.l2 = "それなら、ちょうど俺がコインを取りに行く時だな。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "よし、だいたい十日から十五日ほどくれ。その間に段取りをつけて、色々と手配しておく。二週間もあれば全部片付くさ。  ";
			link.l1 = "ありがとう、Fadey！待ってるよ……";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "なぜわざわざ奴らを怒らせたんだ、旦那？この辺りじゃ密輸業者はそんなに悪い連中じゃないし、 うまくやれば儲けにもなるんだぜ。まあいい、助けてやるよ、奴らの機嫌の取り方は知ってるからな……さて、料金は\n " + sTemp + "、値切りはなしだ。";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "よろしい、ファデイ、同意しよう。金を受け取れ。";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "今はそんなに金貨を持っていないんだ。後でまた来るぜ！";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "よし、俺が仲直りさせてやるから心配すんな。昔みたいにまたあんたと取引するさ。";
			Link.l1 = "ありがとう！";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "ほっほっ、商売繁盛で食欲も増してるようだな！確かに、うちの品は上等で値段も悪くねえ。だがな、投資が必要だぜ！ こういう商売は、すべてを完璧にするために本気で取り組まなきゃならねえんだ。\n";
			link.l1 = "俺がそんな申し出をするのに、手元に二百枚ほどのドゥブロン金貨を用意せずに来ると思うか？";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "お前の金庫にコインが詰まってるのは知ってるぜ、しかも二三枚どころじゃねえ、五十枚は余裕で入るだろう！だが、 俺たちの商売は普通じゃねえ――ただの物の運びじゃなくて、そうだな……目立たずにやる方法を探すんだ。これだけの規模なら、ただ払うだけじゃなくて、しっかり投資しなきゃ儲けにならねえ！ それに、お前の金が煙のように消えちまわないようにな。もし三千枚の金ドゥブロンを用意できるなら、 俺の言葉を信じてくれ、友としてきっちりやらせてもらうし、値段でも損はさせねえさ。";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "三千ドゥブロン！いやはや、これほどの気前のいい申し出は、どんな裕福な商人でも、どんな空想話の中でさえ、 めったに耳にしませんぞ！こんな事業にこれほど惜しみなく投資する者は、そう多くはありません。しかし、 幸いにも私はその一人です。さあ、これがあなたのお金です、ファディ旦那。";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "三千枚の金ドゥブロンか！そんな大金、俺には用意できねえよ、ファディ。残念だが、また後で来るぜ。";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "三千だと？うーん……正直、その額にはお前の野心を感じて敬意を表するよ。だが、認めざるを得ない――これは俺には向いてねえな。";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "なんて展開だ！お前は取引を持ちかけてきたかと思えば、すぐに手を引くのか！正直、がっかりだが、 だからといって俺たちの友情まで壊す気はねえ。今まで通りにしよう。前の約束はそのままだ――毎月20日に、コイル50本を1本10ドゥブロンで。\n";
			link.l1 = "わかってくれて嬉しいよ、ファディ。気持ちは変えたいけど、そんな出費は俺には無理だ。残念ながら、 この件に関しては俺の手に余るんだ。";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "そうか、それが君の決断なら、もう話すことはないな。これで俺たちの友情が変わることはない。ぜひ遊びに来てくれ。 "+GetSexPhrase("旦那","麗しきご婦人")+".";
			link.l1 = "さらば。";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "それは賢明だな！無駄話はしないが、行動力はあるってわけだ。あんたみたいな商売人には、いつだって割引があるぜ！ 今後すべての納品が15％オフだ！取引の内容はこうだ――毎月、麻縄250巻を用意しておく。今まで通り、20日に受け取りに来てくれ。支払いは全部で2125ドゥブロン、残額なしだ。\n";
			link.l1 = "完璧だぜ、ファディ！お前とは本当に商売がしやすいな。きっと俺たちは成功するさ。では、また会おう！";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}