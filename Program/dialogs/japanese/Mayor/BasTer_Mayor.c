// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お話を伺いましょう、ご質問は何でしょうか？"),"二度目のお尋ねでございますね…","もう三度目のご質問でございますね……","いつになったら終わるのですか！？私は植民地の業務で忙しい身ですのに、 あなたはまだ何か尋ねようとしているのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを改めました……","今は駄目だ。場所も時も間違っている。"),"「確かに……しかし、今ではなく後で……」","聞いてみます……でも、少し後で……","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "あなたに繊細な案件を任せたいのです。つい最近、 ある私掠船の者がラズライトの石がはめ込まれた金の十字架をバステール教区に寄贈しました。\nしかし問題なのは、その十字架がサンティアゴ教区から盗まれたものであり、盗難の際に聖職者が殺害されたことです……";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "私はフィリップ・ド・ポワンシー総督閣下の命により、あなたの武装フリゲート艦の指揮を執るために参りました。";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "私（わたくし）はフリゲート艦を戦隊に加える準備ができております。";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "ここで誰かと会う約束があるんだ……";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "旦那、私はこの町で商業活動を行うつもりでございます。\n特に、安定した大規模な酒類取引に興味がございます。";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでに全てを奪ったではありませんか。まだ何を望むのですか？","まだ手を付けていない物が何か残っておりますか？");
            link.l1 = RandPhraseSimple("少し見て回っているだけです……","念のため確認しているんだ、何か持っていくのを忘れるかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "ふむ。それはなかなか興味深いですな。\nしかし、なぜ私がスペイン人の問題など気にかけると思うのです？";
			link.l1 = "スペイン人のことではありません、旦那。宗教は人々を国籍で分けるものではございません。 あなたの教区には聖なる従者の血に染まった品があり、サンティアゴの教区では冒涜行為が行われました……";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "正義を示し、聖職者に十字架を本来の持ち主へ返すよう命じていただきたく存じます。";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "「それで、いつからそんなに真面目な信者になったんだ、はっ、」 "+pchar.name+"？スペイン人は我々の友人ではありませんし、この件で聖下に圧力をかける理由も見当たりません。 十字架は贈り物であり、それで十分です。我々の神父はその盗難や殺人とは無関係ですから……";
			link.l1 = "「そして、あなたには私を助けることができないのですね？」";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "「正直に申しますと、」 "+pchar.name+"、私にはその必要性を感じません。あのカトリック狂信者たちに対して愛情などありませんから。";
			link.l1 = "なるほど。ご迷惑をおかけして申し訳ありません、旦那……";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "船は準備できておりますが、艦隊に空きのバースがございません。\n船長、艦隊を減らしてからお戻りください。そうすれば、すぐにフリゲート艦をお渡しいたします。";
				link.l1 = "「よろしい。」";
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
			dialog.text = "素晴らしい。新しい船を迎える準備をなさいませ。\nその船の船長は承知しており、あなたのすべての命令に従います。";
			link.l1 = "それでは出発いたします。ごきげんよう、閣下。";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "ああ、シャルル・ド・モール旦那、ちょうど良い時にお越しくださいました！ 私の古い友人があなたにお会いするのをとても楽しみにしており、ご到着を知らせてほしいと頼まれておりました。 どうぞ、私の居間へお入りください。すぐにアンジェランに知らせます。\nところで、お二人はどのようにして知り合われたのですか？";
			link.l1 = "一緒に賭けをしたんだ。彼が負けて、ちょっとした揉め事になった。 旦那デ・シェヴーは私たちの仲を修復したいと思っているのだろうな。";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "間違いありません！お二人の間でうまく解決されることを願っております。 アンジェランは決して付き合いやすい人物とは申せませんが、聡明で高潔な方でございます。あなたと同じく、 実に稀有な存在ですわ。";
			link.l1 = "お世辞を言っていただき、恐れ入ります、閣下。もしご迷惑でなければ、応接室で彼をお待ちいたします。";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "しかしもちろん、ご自由に、くつろいでください。少々お待ちいただくことになるかもしれません。 飲み物を運ばせますので。";
			link.l1 = "ありがとうございます、閣下。しかし、私は遠慮いたします。ただ座って、我々の共通の…友人を待つことにいたします。";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "船長、私に接触されたのは賢明なご判断です。この島での不正取引撲滅のため、我々はあらゆる努力を尽くしております。 \n合法的な手段で商いを志す誠実な船長を、私は心より歓迎いたします。";
			link.l1 = "それでは、取引を開始するための条件と手順を教えていただけますか？";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "至って単純でございます。酒類の取引を行うには、毎月百ドゥブロンの税を財務官に納め、適切な記録を保持し、 定期的に活動報告を提出しなければなりません。\n資金が納入され次第、本格的に取引を開始してよろしいです。";
			link.l1 = "素晴らしい。条件はまったくもって妥当です。地元の住民クリスチャン・デルースが私の代理を務めますが、 問題はありませんね？";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "かしこまりました、船長。しかし、よくお考えください――あなたの庇護下にある者の全責任はあなたにございます。もし彼が過ちを犯せば、 その報いもあなたが共に受けることになります。";
			link.l1 = "かしこまりました。ご説明いただきありがとうございます、総督閣下。手配は私どもでいたしますし、 クリスチャンが納税の手続きをいたします。";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "素晴らしいです。これほど勤勉な姿勢を拝見できて嬉しく思います。貴殿の事業のご成功をお祈りいたします。";
			link.l1 = "感謝いたします。我々の協力がこの街の利益となることを信じております。それでは、御機嫌よう。";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
