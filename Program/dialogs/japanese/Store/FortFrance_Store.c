// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、用件は何だ？","ちょうどその話をしていたところだ。忘れてしまったのか……","今日はこれで三度目だぞ、何か質問を持ち込んできたのは……","聞け、ここは店だ。人はここで物を買うんだ。邪魔するなよ！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったんだ……","「ああ、本当にこれで三度目だな……」","ふむ、俺はしない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "聞いてくれ、旦那。俺は仕事を探してるんだ。常勤や荷物運びじゃなくて、いわば使い走りみたいなものさ。 何か手伝いが必要だったりしないか？";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "お使いは済ませたぜ。グララム・ラヴォワを見つけた。";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "新しい助手を紹介します、旦那。";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "また私です、旦那。報酬を受け取りに来ました。";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "これらのイヤリングを見てください、旦那。ジャングルで討たれた山賊の死体から見つけたんです。 これは明らかに腕のいい宝飾職人の作で、きっとこの辺りのものじゃありません。\nこのイヤリングについて何かご存知ですか？";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "失礼ですが、旦那、剣はどこですか？刃物なしで町を出るのは危険ですよ。\nジャングルで何が起こるかわかりませんからね！";
				link.l1 = "くそっ、すっかり忘れてた！全部持っていかれちまった！";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "仕事か？ふむ。お前が興味を持ちそうな仕事があるかもしれんな。私の助手が行方不明なんだ。倉庫で働いていた奴だが、 もう一週間も姿を見せていない。おかげで私が奴の仕事までやらされて、本当に迷惑しているし時間も足りん。\n頼む、この間抜けを探し出して、なぜ仕事を放り出したのか理由を突き止めてくれ。いや、 できればそのまま連れ戻してくれ。報酬は八エスクード銀貨千枚払おう。";
			link.l1 = "よし、引き受けた。そいつの名前と特徴を教えてくれ。どこを探せばいいか心当たりはあるか？";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "たった千のために、神のみぞ知る場所で男を探せって？冗談じゃねえよ！";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "おい、旦那。仕事を探してるのはあんたか、それとも俺か？やりたくないなら、無理に勧めやしねえ。良い一日をな。";
			link.l1 = "ふむ……港湾当局を見に行ってみるか。あちらならもっと実のある話があるかもしれん。";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "名前はグララム・ラヴォワだ。見た目か？三十五歳くらい、ひげと口ひげ、長い茶色のコートに白いシャツ。それから、 いつもあの間抜けな三角帽をかぶってる。まるで尻に錨を突っ込んだ提督気取りさ\nサン・ピエールにはいないぞ、町中くまなく探したからな。きっとジャングルか、 レ・フランソワであそこにたむろしてる海賊どもと一緒に隠れてるんだろう\nいや、たぶん島の東にある海賊の集落ル・フランソワにいるはずだ。あそこで海賊たちと話してるか、 酒場で時間を潰してるか、店で地元の商人と口論でもしてるかもしれん\nル・フランソワへの行き方か？町の門を出てジャングルに入り、分かれ道で左の道を進め。 それから道なりに行って右に曲がり、岩の間の左側の通路を通ればル・フランソワに着く。迷うことはないと思うぜ";
			link.l1 = "わかった。すぐに捜索を始める。何か分かり次第、すぐにお知らせしよう。";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "ああ、そうか？で、そいつはどこにいるんだ？";
			link.l1 = "ル・フランソワで彼を見つけた。もうあなたのためには働かないそうだ。それに、 あなたについてかなり辛辣なことも言っていたが……聞きたいかい？";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "いいや。詳しい話は聞きたくない……なんてこった！助手がいなくなって、これからどうすればいいんだ？";
			link.l1 = "他の誰かを雇えばいいだろう。もしくは、本当にグララムが言ってたほど大きな問題なのか？";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "まったく運が悪いな。それで、あの怠け者は何て言いやがった？";
			link.l1 = "「さて、まず第一に、あいつは明らかに暇を持て余してるわけじゃねえな、へへ。あいつが言うには、 サン・ピエール中の誰もあんたの下で働こうとしないってさ……理由は、あんたが労働者に十分な給料を払ってねえからだとよ。ああ、ちなみに、」 "+npchar.name+"、約束通り千ペソの借りがあります。";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "どうぞ、お金を受け取ってくれ。はっ！これじゃ全然足りないな！まったく、誰も俺のために働きたがらねえ。 あの野郎がありもしねえ噂を広めやがって。どうしろってんだ？全部一人でやれるわけねえだろう！\n荷物を一つ一つ数え終わるまで寝ることもできねえ、あのクソ働き手どもはいつも何か盗みやがるからな。 前回の積み込みの後、ラム酒の樽が五つ足りねえ。きっとあいつらが“うっかり”持っていきやがったんだろうよ…";
			link.l1 = "うーん、何を助言したらいいかわからないな。\nまあ、とにかく幸運を祈るぜ。\nそろそろ俺も行く時間だ。";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "待て！お前なら俺を手伝えるかもしれねえ。その野郎を追い詰められたなら、きっと他にも……";
			link.l1 = "「この町の誰もあなたを信じていないとしたら、私に一体何ができるのでしょうかね？私はここに来たばかりで…」";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "最後まで聞いてください、旦那。あなたはル・フランソワに行ったことがありますね。もう一度そこへ行って、 私のために従業員を探してきてほしいのです。もしかすると、 グララムがあの海賊の巣で私の評判を完全に台無しにしたわけではないかもしれません\n仕事は簡単です――貨物を数え、港の労働者たちが盗みを働かないよう見張ること。それから、 私が不在のときは代わりにここで私の仕事をしてもらいます、もちろん追加報酬も出します\n住み込みの部屋と、週に五百エイト銀貨を提供する、と伝えてください。旦那、私は事業拡大を計画しており、 ようやく物事がうまく回り始めたところです。助手が必要なのです！\nちなみに、従業員探しは地元の酒場の主人、チェザーレ・クレイグに頼むのが一番です。あの悪党なら、 ただでは済みませんが、私のために働きたい者をきっと見つけてくれるでしょう。";
			link.l1 = "ふむ。やってみてもいいが、正直自信はないな……その仕事、いくら払ってくれるんだ？";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "それは雇える職人次第だな。腕のいい者を連れてきてくれれば、その分だけ報酬も多く払おう。公平だろう？";
			link.l1 = "俺に目隠しで乗れって強要してると思わねえか？どうやってあんたが労働者を評価するのか分かるはずがねえだろう？ 誰だって悪いと烙印を押せるんじゃ…";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "旦那！私が少々けちだと言われても仕方ありませんが、不誠実だなんて誰にも言わせません！ 結果次第で報酬を支払うと申した以上、私はその言葉に嘘はありません。私の立場からも考えてみてください。 あなたが連れてくるのが、怠け者のジプシーで、何もしないどころか夜中に私を盗むような輩かもしれないのですよ！";
			link.l1 = "わかった。承知した。君の言葉を信じよう。 "+npchar.name+"。ジプシーは絶対に連れて帰らないようにします。";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "私のために労働者を見つけてくれたのか？素晴らしい。彼と少し話をさせてくれ、君の報酬は一時間後に取りに来てくれ。 ";
			link.l1 = "わかった。1時間後に戻ってくる。";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "君が見つけてくれた労働者にはかなり満足しているよ、まあ口ばかりで手が動かないところもあるが、心配はいらん、 そのうちおしゃべり癖は叩き直してやるさ。\n報酬は三千エイト銀貨だ。さあ、受け取ってくれ。";
					link.l1 = "ありがとうございます！旦那、教えていただけますか、 この町で他に何か重要な用件で助けを必要としている方をご存知ですか？";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "本当に貴重な働き手を見つけてくれましたね！あの悪党グララムよりも優秀ですよ。私はとても、とても満足しています、 旦那。さあ、報酬を受け取ってください――八千枚のエイトです。";
					link.l1 = "ありがとうございます！旦那、教えてください、この町で他に何か重要なことで助けを必要としている人をご存知ですか？ ";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "いい働き手を見つけたな。それに、まだ商売のコツをすべて知っているわけじゃないが、すぐに覚えるだろう。旦那、 私はあなたに満足している。さあ、報酬だ――四千枚のエイトを受け取ってくれ。";
					link.l1 = "ありがとうございます！旦那、教えてください、この町で他に何か重要なことで助けを必要としている人をご存知ですか？ ";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "ふむ……ついさっき、港長が明らかに不機嫌な様子で港役所へ向かうのを見かけたよ。彼に聞いてみな、 何があったのかわからないからな。";
			link.l1 = "そうさせてもらうよ。ありがとう、旦那。";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "さて、何と言えばいいかな、見事なイヤリングだ。そうだな……四千枚のエイトを出そう。他にもっと出す奴はいないだろう。どうだ、取引成立か？";
			link.l1 = "取引成立だ！あんたのものだ。";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "いや、これらの宝石は俺が自分で持っておくつもりだ。";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "それでは困ります。総督に相談して、助力を求めてはいかがでしょうか。";
			link.l1 = "助言ありがとう。そのつもりでいる。";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
