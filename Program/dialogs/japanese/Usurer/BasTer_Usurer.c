// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","ご用件は何でしょうか？"),"あなたはつい最近もその質問を私にしようとしましたね……","ああ、当ててやろうか……また堂々巡りしてるんじゃないか？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことが何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","お察しの通りです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "俺が船長だ "+GetFullName(pchar)+"。あなたの部下が、私にお会いしたいと伝えてくれました。何なりとお聞かせください。";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "また私でございます、旦那 "+GetFullName(pchar)+"。ベルトラン・ピネットを連れてきた。今は俺の貨物室にいる。";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "また私です、旦那 "+GetFullName(pchar)+"。お話ししましょう。";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "また私です、旦那 "+GetFullName(pchar)+"。少しお話ししましょう。";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "また私です、旦那 "+GetFullName(pchar)+"。私にまた会うとは思っていなかったでしょう。";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "あ、ああ、船長 "+GetFullName(pchar)+"！お会いできて本当に嬉しいです！あなたをずっとお待ちしていました……さて、質問があります。少し前、バートランド・ピネットという名の男が港であなたに近づき、 乗船を頼んできたはずです。豪華なカツラをかぶった裕福そうな男です。心当たりはありますか？";
			link.l1 = "はい、その通りです。彼はまさにこの目的で私に接触してきました。";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "彼はあなたとあなたの船を雇いたがっていたのですか？船長、この件の詳細をすべて教えていただければ、 私にとって大変ありがたいことでございます。必ずお礼はいたします。どうぞ、 このコインの詰まった財布をお受け取りください。これはあなたのものです。さあ、 ベルトラン・ピネについてお話しください。";
			link.l1 = "承知しました。ピネット旦那が私の船を雇い、 彼と友人二人をグアドループからスペイン領本土まで運ぶよう依頼されました。より具体的には、 ポルトベロ近くのモスキート湾です。私は任務を果たし、 彼らは私の船を降りてそのままジャングルへと歩いて行きました。";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "なるほど。それで、ピネット旦那は最終目的地について何か言っていましたか？それと、同行者についてはどうですか？";
			link.l1 = "本人の話によれば、彼らはパナマへ向かっていたそうだ。仲間もなかなか興味深い連中でね――一人はスペイン人将校、もう一人はフランス人将校だ。何が彼らを結びつけたのかは未だに分からないが、 俺は詮索するために雇われたわけじゃないからな。";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "スペインの将校？それにフランスの将校も？おお！そりゃすごいな！やるじゃないか、ピネット旦那！ なんて抜け目のない奴だ！こんな所でも金儲けの手を見つけるとはな！パナマだって？";
			link.l1 = "ああ、知っていることは全部話したぜ。もう行ってもいいか？";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "お待ちください、船長。あなたに商談があります。少し稼いでみる気はありませんか？その前に、 あなたの乗客について少しお話ししましょう。";
			link.l1 = "では、お聞かせください。";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "ベルナール・ピネット旦那は二年前に我々の植民地へやって来て、すぐに船長たちと取引を始めました。 その取引というのも、まあ、いかがわしいものでして……彼らはここで非常に不足している品――貴重品や密輸品、時には奴隷まで――を彼に届けていたのです。彼は違法な事業のために、私の事務所で組織的に融資を受けていましたが、 利息も含めて必ず返済していました。\nあなたの寛大なご協力で島を離れる前、彼はいつもよりはるかに大きな融資を受けました。彼は……いえ、彼は信頼できる顧客であり、信用履歴も申し分なかったので、私は融資を認めたのです。大きな過ちでした。 ピネット旦那は逃亡し、明らかに私の金を返すつもりはありません。";
			link.l1 = "「お伺いしてもよろしいでしょうか、金額はいかほどでしょうか？」";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "とてつもなく大きいです。約十五万ペソ分のドゥブロン金貨です。十個の箱、 それぞれに百五十枚のドゥブロンが入っています。しかも、それは利息を含めていない額です。";
			link.l1 = "ふむ……彼は二年間も君に返済を続け、君を油断させてから、多額の借金をして逃げ出したのですね。賢いやり方です。";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "まさにその通りです、船長。だからこそ、あなたに仕事を依頼したいのです――その悪党を見つけて、ここに連れてきてください。総督と司令官、そして私で、 彼の借金をきれいにさせる方法を見つけます。あなたはその男を見たはずですし、彼はあなたの乗客でした。つまり、 誰よりもピネット旦那を見つける可能性が高いのです。もちろん、賞金稼ぎのプロも雇いますが、 あなたの協力のほうが効果的だと私は感じています。";
			link.l1 = "報酬はどうなりますか？";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "仕事をしてくれたら、ドゥブロン金貨がぎっしり詰まった箱、百五十枚を渡そう。";
			link.l1 = "スペインの町で生きている人間を追い詰めて誘拐したのに、これが報酬だなんて、まったく情けない話だぜ。";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "船長、私の提案をそんなに安く見積もるということは、ピネット旦那が私の金でたっぷり支払ったのでしょうな。ですが、 ご安心ください、それだけの価値はございます。当然、あなたにはお断りになる権利がございます……しかし、どうしてもお伝えしたいことがありまして、それを聞けばきっと考えが変わるはずです。";
			link.l1 = "「それは何ですか？」";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "ピネットがグアドループから脱走する数日前、バステールの監獄から囚人が一人脱走しました。 名前はドン・カルロス・デ・ミリヤール、スペインのグランデであり士官です。彼はフランス軍の士官、 海兵隊の中尉の裏切りによって脱走に成功しました……私の言いたいことがわかりますか？";
			link.l1 = "ふむ……それが私に何の関係があるのですか？私はただ乗客を運んでいただけです。";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "もちろん、そうでしたとも！私個人としては、あなたがドン・デ・ミリヤールの脱走に関与していないと確信しています。 しかし、我々の総督や司令官はそうは見ないかもしれません。運が良ければ共犯の罪、悪ければ……これ以上は言いたくありません。ご自身でお考えください、あなたは逃亡したスペインの士官を船に乗せたのですから、 おそらくどこかの隠れ入り江で……違いますか、船長？";
			link.l1 = "なるほど。脅迫しているんだな。ここに来たのは間違いだった……";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "どうだい、船長！？俺は脅迫なんてしてないぜ！頼みたいのは、ちょっとした手助けと、それに見合う報酬だけさ。 ピネット旦那を見つけてバステールまで連れてきてくれないか？君の帰りを待っているよ。 パナマまで行って戻るのに二ヶ月もあれば十分だと思うが。";
			link.l1 = "仕方ありませんね。しかし、そのような商売のやり方で我々が友人になれるとは思えません。さようなら、旦那。";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "素晴らしい知らせだ、船長！すぐに部下をお前の船に送り、この野郎を引き取らせよう。この鳥野郎、 今度こそ逃がさねえ……報酬はお前のものだ、この箱を受け取れ。どうか怒らないでくれ、これはお前へのお守りだ。贈り物だぜ。";
			link.l1 = "感謝いたします。あなたの沈黙も私への報酬の一部だと解釈してよろしいのでしょうか？";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "沈黙？何についてだ？あなたが私の顧客になってくだされば嬉しいですよ。沈黙と金についての格言をご存知でしょう？";
			link.l1 = "時には金よりもはるかに価値があるのですよ、旦那。教訓になりました。それでは、ごきげんよう！";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "お話を伺いましょう。バートランド・ピネットはあなたの船にいるのでしょうか？";
			link.l1 = "いいえ。しかし、あなたにもっと素晴らしいものがあります。これをお読みください。";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "これは何だ？";
			link.l1 = "読み続けてください、旦那。続きはまた後ほど。";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "（読み上げ）ゴホン……これは何だ、この熱病患者についての馬鹿げた話は？";
			link.l1 = "本気か？いいだろう、この「たわごと」を総督に持っていくぜ。「カレッジ号」 とそのダイヤの積荷が消えた真相を知れば、総督もきっと大いに興味を示すだろう……どうした、顔色が真っ青じゃねえか？";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "それで、結局ピネットを見つけたのですね…";
			link.l1 = "はい。そこで、あなたに取引を提案します。カルロス・デ・ミリヤールやジャン・デノ、 他の紳士たちのことは忘れてください。そうすれば、この手紙のことも私が忘れましょう。";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "承知しました、船長…。あなたの条件を受け入れましょう。";
			link.l1 = "素晴らしいですね。私にお怒りでなければよいのですが、これでお取引は終わりかと存じます。では、ごきげんよう。";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "はあ……おっしゃる通りです、船長。";
			link.l1 = "あなたに渡すものがある。これを受け取って読んでくれ。";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "それで、結局ピネットを見つけたのですね……";
			link.l1 = "はい。そこで取引を提案します。フランス植民地内で私の名誉を回復してくれれば、この手紙のことは忘れましょう。";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "しかし……";
			link.l1 = "どうやってやろうが俺は知ったこっちゃねえ。明日までに俺の首への賞金が終わらなきゃ、 総督に全部ぶちまけてやるからな。";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
