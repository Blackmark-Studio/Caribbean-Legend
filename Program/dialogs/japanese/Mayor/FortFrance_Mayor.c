// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？遠慮なく聞きたまえ。","お聞きしましょう、ご質問は何ですか？"),"二度目のご質問でございますね…","あなたが再び尋ねようとするのは、これで三度目でございます…","いつ終わるのですか！？私は植民地の案件で忙しい身なのに、あなたはまだ何かを尋ねようとしているのですね！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを改めました……","今は駄目だ。場所も時も間違っている。"),"確かに……しかし、今ではなく、後で……","尋ねます……ですが、少し後で……","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "旦那、私はジャングルで盗賊の死体を見つけました。彼はインディアンに殺されていました。 遺体にはイヤリングがありましたが、どうやらヨーロッパから持ち込まれたもののようです。もしかすると、 貴町の貴族の誰かの持ち物だったのではありませんか？";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "閣下、ご命令は果たしました！しかしながら、残念ながら犯罪者は戦闘で命を落とし、 処刑にかけることはできませんでした。";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "閣下、ご命令の任務は完了いたしました！囚人は私の監禁室で運命を待っております。";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "私はフィリップ・ド・ポワンシー総督の命令で参りました。貴殿の武装フリゲート艦の指揮を執らせていただきます。";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "私の戦隊にフリゲート艦を編入する準備ができております。";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "ご招待いただきまして参りました、旦那……";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "それは不運でした、旦那";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "閣下、私めは近日中にこの地で行われる不正取引に関する情報を入手いたしました。この件、 貴殿のご関心に値するものと存じます。";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "閣下、先日お話ししたあの密輸船についての消息を伺いに参りました。";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "さて、何を持ってきたのか見せてくれ……信じられない！本当に信じられないぞ、チャールズ！これは妻のイヤリングだ。 私がヨーロッパを離れて植民地に来る前に彼女に贈ったものだ。数か月前、謎の事情で消えてしまったのだ。 盗まれたに違いないと思っていた！\nチャールズ、君がまっすぐ私のところに来て、この大切な品を商人に売らなかったことをとても嬉しく思う。 君の厚意には必ず報いよう。聞くところによると、君は船を買うつもりなのだとか？航海を始めるなら、 きっとこの諸島の地図が必要になるだろう。さあ、これを持っていきたまえ。きっと役に立つはずだ！";
			link.l1 = "「ありがとうございます、閣下！」";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "それは残念ですわ、チャールズ。でも、今の状況でやっていくしかありませんわね。\nこちらがあなたの報酬です――税引き後で五千ペソですわ。";
			link.l1 = "私はサン・ピエール、そしてあなた様にお仕えできることを嬉しく思います。戦いは困難でしたが、 多少の楽しみも見出せました。";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "困難な戦いでございました、閣下。私の船は大きな損傷を受けました。損失の補償をしていただくことは可能でしょうか？ ";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "お見事です、チャールズ！あなたが我々の階級で大いに出世されること、疑いようもありません。";
			link.l1 = "「またお目にかかる日まで、閣下。」";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "正直申し上げて、あなたのご要望には少々驚いております、チャールズ……よろしい、私個人からさらに二千ペソを親善の印として差し上げましょう。ごきげんよう。";
			link.l1 = "「ありがとうございます、閣下。」";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "素晴らしいです、チャールズ！あなたの成功がマルタのご友人たちの繊細な作戦に役立つことをお知りになれば、 きっとご満足いただけるでしょう……こちらが報酬です。税引後で八千ペソになります。";
			link.l1 = "私はサン・ピエールと騎士団、そしてあなた様ご自身にお仕えできることを嬉しく思います。戦いは困難でしたが、 そこにある種の満足を見出しました。";
			link.l1.go = "TK_Plen_3";
			link.l2 = "激しい戦いでございました、閣下。私の船はかなりの損傷を受けました。損失の補償をお願いしてもよろしいでしょうか？ ";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "見事だ、チャールズ！あなたならきっと大成すると確信しています。";
			link.l1 = "またお会いできる日まで、閣下";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "貴殿はそれに値すると思います。私からの好意として、さらに二千を個人的に差し上げましょう。ありがとう、友よ。";
			link.l1 = "「ありがとうございます、閣下。」";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "船は準備できておりますが、艦隊に空きの船席がございません。船長、艦隊を減らしてからお戻りください。そうすれば、 すぐにフリゲート艦をお渡しいたします。";
				link.l1 = "よろしい。";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "はい、もちろんでございます。船は出航の準備が整っております。船長も承知しており、すべてのご命令に従います。";
				link.l1 = "それでは出発いたします。ごきげんよう、閣下。";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "素晴らしい。新しい船を迎える準備をしなさい。船長にはすでに伝えてあり、あなたの命令に従います。";
			link.l1 = "それでは出発いたします。ごきげんよう、閣下。";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "シャルル・ド・モール船長、ついにお越しくださいましたか！心待ちにしておりましたぞ！どうぞ、 お入りになってご一緒ください。";
			link.l1 = "ごきげんよう、閣下。閣下がこれほどご丁寧なのには、必ず何か理由がございますね。今回は何でしょう？海賊か、 スペイン人か、それとも赤い肌の食人族ですかな？";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "皮肉を言わないでくださいよ、船長。私とあなたがいつもトラブルに巻き込まれるのは私のせいじゃありません。でも、 どうかご心配なく、今回は撃ち合いにはなりません……たぶん。";
			link.l1 = "興味深いですね、続けてください。どのようにお力になれますか？";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "マダム・ボトーの素晴らしい店のことを聞いたことはありますか？\n包囲戦の際に、我々の……娼館は灰になるまで焼かれてしまいました。ある日、とあるご婦人が再建を申し出てくださったのです。";
			link.l1 = "娼館で火事があったのに俺がいなかったって？\nそれにしても、あの日はスペイン人にも撃たれたんだぜ。";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "くそっ、チャールズ、今日は一体どうしたんだ？お前の冗談は場違いだぞ！これは国の問題ではないが、 私にとっては個人的に重要なことなのだ！お前の助けが必要なんだ！頼むから、しっかりして私の話を聞いてくれ！";
			link.l1 = "お許しください、閣下。安堵の気持ちが大きくて、つい…。正直申し上げて、絶え間ない戦いや争いにはもう疲れております。 閣下がまた私を新たな暴力の渦に巻き込むのではと覚悟しておりました。どうぞお話を続けてください。 マダム・ボトーという方については存じ上げません。";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "なるほど、このご立派なご婦人のおかげで、この店はまったく新しい高みに引き上げられたのです。\n今やここは、かつてのような鼠の巣ではなく、高貴な社交界の場となりました。\n洗練された悪徳、高価なワイン、そして無限の賭博が楽しめる場所です。\nすべてご自身の目でお確かめください！";
			link.l1 = "閣下、私は堅物ではございませんし、閣下のご説明は実に鮮やかでしたが、 なぜそのようなことを私にお話しになるのですか？";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "お前が名簿に載ってるからに決まってるだろ、他に理由があるか？！\nほら、マルキーズの件で俺も後ろめたさがあるし、明日の彼女のパーティーでお前を紹介するって約束したんだ。\nジュリアナはこんなこと滅多にしないから、ぜひご一緒してくれ。\n今回は喧嘩も発砲も追いかけっこもなしだ、約束する。\nすべて礼儀正しく、品位あるものになる――ワイン、美しい女性、カード、そして他の貴族の楽しみも用意されているぞ。";
			link.l1 = "カードと女か。昔の話だな、別の人生のことさ。\nだが、まだお前の言いたいことが分からねえ。\nなぜ俺なんだ？";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "耳が遠いのか？ジュリアナ・ボトットは……華やかで有名な顔ぶれを集めている。彼女の宴が特別で新鮮なのはそのおかげだ。あなたは大変な評判を築いたし、 侯爵夫人も長い間あなたを客人として迎えるのを待っていた。私の失態が彼女に好機を与えてしまい、 もし再び私の訪問を断られたら、私はもう受け入れてもらえないだろう。あなたを彼女のもとへ連れて行けなければ、 私が得られるのはこれだけだ！";
			link.l1 = "閣下はご立派な未亡人であり、総督でもいらっしゃいます……なぜご自身が娼婦の意見など気にされるのですか？本来なら、彼女たちこそ閣下のご機嫌を伺うべきでございますのに、 逆ではありませんわ。";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "マルキーズ・ボトは、カウント・アンリ・ド・レヴィ＝ヴァンタデュールの庇護下にございます――陛下のご恩寵により、彼は北アメリカにおけるヌーヴェル・フランスの諸州の長でございます。\n信じてください、シャルル、ここで彼に逆らいたい者などおりません。";
			link.l1 = "もう少しで騙されるところでしたわ――最初はただの情欲と恋の話かと思いましたのに、結局はずっと政治だったのですね。取るに足らないことですが、 予想はしておりましたわ。よろしいですわ、お手伝いしましょう。たった一夜でも、 若き日の思い出に浸れるのは甘美なことですもの。";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "船長、あなたは経験豊富な方であることに疑いはありませんが、老人のふりをなさらないでください。\nこれは単なる政務の話ではございません。私はジュリアナ殿のご同席を大変重んじておりますし、 あなたのご助力にも感謝しております。\nこれは私個人にとっても、誠に大切なことなのです。\n明日の夕暮れ後、マルキーズ・ボトーの邸宅へお越しください。\n今宵は政務ごときに邪魔はさせませんと、お約束いたします。";
			link.l1 = "ワイン、カード、女たち。まるで昔の良き時代のようですな。ごきげんよう、閣下！";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "チャールズ、どうしたんだ、ひどい顔をしているじゃないか！";
			link.l1 = "アンジェラン、あの忌々しいチーヴァスめ、閣下。昨夜、私のフリゲート艦を奪い、 戦利品の乗組員を皆殺しにして霧の中へ出航しました。";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "不愉快な展開であることは承知しておりますが、ご安心ください――この結果は十分に満足できるものでございます。貴殿は船や人手に切実に困っているわけではございませんし、 ド・ルヴィ・ヴァンタドゥールは、最近のある決闘の真相を隠すために多額の金を支払うでしょう。あるいは、我々 が無償で隠蔽に協力したことを覚えているかもしれませんが、それもまた大きな価値がございます。 ド・シェヴィウスは二度も不正を働きましたが、今や遠く離れておりますし、我々 にはまだ彼に対して切れる好手が残っております。";
			link.l1 = "三度目でございます、閣下。アンジェランは我々のカード遊びで不正を働いたことを認めました。しかし、 もしお金で解決するという意味でしたら、彼はそれをするつもりはありません。彼は一線を越えました。今朝あの船には、 ある人物が乗っておりました……彼女は私にとって非常に大切な方なのです！あの野郎に彼女を傷つけさせはしません！聞こえていますか、ジャック、 私は絶対に許しません！";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "誰のことを言っているのか、私には分かる気がする……君が誰かと一緒にいるのを見た覚えがあるよ……男のような格好で、まるで海賊のように武装した娘だったな。\nチャールズ、馬鹿な真似はやめろ！君は運が良かった、あの大きな災難を避けられたんだ。なのに、 また自分から首を突っ込もうとしているのか？やめておけ。デ・シェヴィウスは逃亡中だ――神に感謝だ！\nそれに、君の“武装した恋人”については――友人の忠告を聞け――ジュリアナに会いに行って、すべて忘れるんだ。";
			link.l1 = "論外でございます、閣下。いくら閣下でも理解できぬこともございますのでしょう？さて、 その悪党について知っていることをすべて話してください。サン・ピエールからどこへ向かったのでしょうか？ もうこれ以上、私を止めようとしないでください――私はオランダ東インド会社とも渡り合い、海賊の男爵や総督、果ては聖なる異端審問とも対峙してきました！ 私を脅して追い払うのは容易なことではありません。どんな犠牲を払っても、必ず彼女を取り戻します！";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "シャルル、総督を誰が任命するかについて考えたことはあるか？これはまったく別世界なのだ！ お前はその表面をかすっただけで、理解の及ばぬ領域だ。まるで火薬庫の中の子供のようなものだぞ。 そしてお前は私に火のついた蝋燭を渡せと言うのか。総督について言えば、 ド・ポワンシー自身でさえ伯爵には決して逆らわない――金銭のことでも、政治のことでもだ。庶民の間でよく使われる「副王」という呼び名は、 アンリ・ド・レヴィ・ヴァンタドゥールにはまさにふさわしいだろう。";
			link.l1 = "そして私は今、彼の唯一の男の後継者を殺そうとしているのです。 自分がどれほどの危険を冒しているかは承知しています。\nさあ、教えてくれませんか？私の助けになるような有益な情報を何かご存知ですか？";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "他の日であれば、ピストルに手を伸ばす君の行為を、我々の友情の終わりと受け取っただろう、チャールズ。しかし、 今の君の心情は理解している。だからこそ、今回は大目に見るつもりだ。君の役に立つことは何も知らない。 フリゲート艦は今朝早く西へ向けて出航した。侯爵夫人のもとを訪ねるといい……待て、そんな風にじゃない！ジュリアナは君の敵について多くを知っているし、彼の父親とも個人的に……しばらく親しかった。彼女に尋ねてみるといい。私と違って、彼女は君を止めようとはしないだろう。";
			link.l1 = "そのつもりでございます。それでは、閣下。お時間をいただき、感謝いたします。";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "密輸品だと申されますか？ふむ……これは実に興味深い。どうか、その発見の詳細をお聞かせ願えますか。";
			link.l1 = "三日前、密輸品を積んだ船がル・マラン湾に投錨する予定でございました。その船は約束の場所に現れませんでしたが、 いずれ必ず入港すると確信するに足る理由がございます。閣下、もしよろしければ、 貴殿の部下にこれらの賊どもを迎える準備を整えさせてはいかがでしょうか。\n";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "名もなき船が、正体不明の積荷を運んでいる……そのような曖昧な情報で、陛下の軍勢を派遣すべきだとお考えですか？";
			link.l1 = "閣下、ご報告できる詳細は乏しゅうございます。\nしかし、どうかこの情報が私の手に渡った経緯をお聞き入れくださいませ。（カットシーン）";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "よろしい、あなたの知恵を試させていただきましょう。 もし本当に密輸品を積んだ船がル・マランの岸辺に錨を下ろすならば、王冠へのご奉仕に対し十分な報酬を与えましょう。 \n三日後に再び私のもとへ戻りなさい。その頃には、不確かな霧も晴れているはずです。";
			link.l1 = "素晴らしい。では三日後にお会いしましょう。";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "ああ、船長！またお越しいただき光栄でございます。あなたの情報はまことに有益でした。私の部下が、 まさにご指示いただいた場所でその船を拿捕いたしました。こちら――百五十枚のスペインドブロン金貨、新たに鋳造された重みのある品でございます。感謝の意を込めてお受け取りください。 ";
			link.l1 = "謹んで感謝申し上げます、閣下。私の些細な情報が王冠の御利益となりましたのは、まこと幸運にございます。 再び機会が訪れました折には、私の剣と慧眼、いつでも閣下のお役に立てる所存でございます。";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
