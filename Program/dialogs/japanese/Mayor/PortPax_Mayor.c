// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？何でも聞くがいい。","お話を伺いましょう、ご質問は何でしょうか？"),"これで二度目のご質問でございますが…","これで三度目のご質問ですね……","いつまで続くのだ！？私は植民地の案件で忙しい身なのに、まだ私を煩わせるつもりか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も間違っている。"),"確かに……しかし、今ではなく、後で……","聞いてみます……でも、もう少し後で……","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" 旦那。私は総督シュヴァリエ・ド・ポワンシー閣下の命により参上いたしました。私の任務は、 本国から植民地視察の任を受けて到着したノエル・フォルジェという名の男爵をトルトゥーガまでお連れすることでござい ます。彼の主な目的は、フランス西インド交易会社の設立でございます。お引き合わせいたしますので……詳しいことはご本人からご説明申し上げます。\n";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "ご公爵様、私にお目通しをご所望でしたか？";
				link.l1.go = "PZ_1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "閣下、極めて機密性の高い情報をお持ちし、御前に参上いたしました。";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("あなたはすでにすべてを奪いました。これ以上何を望むのですか？","まだ手を付けていない物は何か残っておりますか？");
            link.l1 = RandPhraseSimple("ちょっと見て回っているだけです……","念のため確認しているんだ、何か持っていくのを忘れるかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "お会いできて大変光栄でございます、シャルル・ド・モール船長、そしてバロン殿。 フォルジェ旦那の当植民地での滞在が快適なものとなるよう、私も万全を尽くします。\nそして、かかる高名な旦那にご来訪いただいたこの機会に、一つご相談を申し上げたく存じます。";
			link.l1 = "これは興味深いですな！ご用件をお聞かせくださいませ、閣下。";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "ここ数か月、我が植民地には総督代理の使者が一人も訪れておりません。まるでセントクリストファーの我々 のことなど完全に忘れ去られたかのようです！\nその間にも、イスパニョーラ全土を純然たるスペイン領にしようと目論むスペイン人たちが、 西部のフランス人入植者やバッカニアを大きな障害と見なし、攻撃の準備を進めております！\n私の巡察官や交易船の船長、さらには普通の漁師たちまでもが、サンティアゴに強力なスペイン艦隊が集結し、 ポルトープランスへの攻撃準備を進めていると報告しているのです！";
			link.l1 = "「証拠は十分に明白でございますか、陛下？」";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "正確な情報は持っておりませんが、まったく無関係な者たちからこれほど多くの話が出ている以上、 単なる噂とは思えません。\n我が植民地はフランスにとって非常に重要でございますし、 こちらには最高のプランテーションがございますことは男爵ご自身もご覧になれましょう。\nこの植民地を失うこと、あるいは略奪の危険にさらすことなど、到底容認できません！";
			link.l1 = "あなたの証拠を考慮し、シュヴァリエ・ド・ポワンシーに報告いたします。\nきっと彼は直ちに対策を講じることでしょう。";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "ありがとうございます、船長……";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ_1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "いいえ、私はあなたを呼んでおりません、旦那。何かご用でしょうか？";
			link.l1 = "どうして私がそんなことを？しかし、あなたの使者が私たちに会いに来て、 町の家の一つを私のために用意してくださったと申しておりました…";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "何の家だ、何の使者だ、これは何たる無礼か！？";
			link.l1 = "何だと、どの使者のことだと……彼の名はアンリ・ティボーで、そして……";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "何だと？お前はあいつが誰か知っているのか？どうやら知らぬようだな。だが、それは問題ではない。 レヴァスールの甥が私の町で何をしているのだ？";
			link.l1 = "「ああ、なんということだ……」";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "ド・モール、聞こえますか？旦那？";
			link.l1 = "...";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "「繊細なご用件と申されましたか？興味をそそられました、船長。どうぞ続けてください――全神経を傾けております。」";
			link.l1 = "件はあなたの姪ジュリーに関することでございます。彼女は自分の所持品から盗まれたネックレスを取り戻すため、 私に依頼をなさいました。";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "首飾り？妙ですね。彼女の持ち物の中にそのような品があった記憶はございません。";
			link.l1 = "順を追って事実をご説明いたします、総督。問題となっていた首飾りは無事に回収いたしました。調査の結果、 盗みを働いたのはご令嬢付きの侍女ジゼルでございました。盗品を購入した商人の様子から見て、 彼女のこのような悪事は初めてでも最後でもないと強く疑っております。";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "大変興味深いです。どうぞお話の続きをお聞かせください。";
			link.l1 = "私が注目したのは、閣下、ジュリーがこの件で閣下に助けを求めなかったことです。\nどうやらその首飾りは、閣下が彼女と交際することを明確に禁じている人物からの贈り物のようでございます。\n閣下のご制約は最も賢明で保護的なご配慮から生じていると信じておりますゆえ、この件を閣下にご報告し、 首飾りを直接お返しする義務があると感じました。";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "あなたのご判断は的確でございます"+GetSexPhrase("「、船長」","")+"。姪の若気の至りに付き合うことなく、直接私のもとへ持ち込んでくださったご配慮に感謝いたします。";
			link.l1 = "私はただ彼女の幸福のみを念頭に行動しております、総督殿。\n貴殿のご指導もまた、同じくご懸念とご賢慮から発せられていることに疑いはございません。";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "確かに、その通りでございます、船長。私は彼女の叔父であり後見人として、 彼女の幸福が最も重要な関心事でございます。あなたのご配慮に感謝の意を込めて、 この百五十ドゥブロンをお受け取りください。さらに、この航海用コンパスも差し上げます――危険な海を渡るあなたの旅路を、どうか安全に導きますように。";
			link.l1 = "ご寛大なお心遣い、閣下、誠に光栄に存じますが、このような褒賞は本来不要でございました。\n残念ながら、ここでお別れを申し上げねばなりません――潮は船乗りを待ってはくれず、私の船も私の手を必要としておりますゆえ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
