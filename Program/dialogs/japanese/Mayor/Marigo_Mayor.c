// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の御用ですか？ご質問があればどうぞ。","お聞きしましょう、ご質問は何ですか？"),"これは二度目のご質問でございます…","これで三度目のご質問ですね……","いつまで続くのだ？！私は植民地の案件で忙しい身なのだ、まだ私を煩わせるつもりか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も間違っている。"),"「確かに……しかし、今ではなく、後で……」","聞いてみましょう……しかし、少し後で……","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "閣下、まことに素晴らしく、かつ緊急のご報告がございます！バルトロメウ・ポルトガル人を捕らえました。 あのろくでなしは監視下にあり、公正な裁きを待っております！そして、 僭越ながら会社からささやかなご恩賞を期待しております……";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "「私にお目通りを強くご所望でしたね、総督旦那……」";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "イギリスの間諜の件で参りました、総督旦那……";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでに全てを奪ったではありませんか。まだ何を望むのですか？","まだ手を付けていないものが何か残っておりますか？");
            link.l1 = RandPhraseSimple("少し見て回っているだけです……","ちょっと確認しているだけだ、何か持っていくのを忘れるかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "バルトロメオ……ポルトガル人のバートが私の町にいるのか？！生きているのか！！";
			link.l1 = "はい、閣下、彼は確かにおりますし、信頼できる護衛の下にございます。 バートの首に対する報酬を会社から約束通り受け取った後で、彼をお引き渡しいたします。 金のドゥブロンでも構いませんが……";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "ビル、ドゥブロン金貨だと？正気か！？こんな化け物を私の町に連れてくるなんて、何を考えていたんだ！？ 奴がここにいるということは、奴のフリゲート艦も島の近くにいるはずだし、 その乗組員が今まさに町の中にいるかもしれんのだぞ！\n";
			link.l1 = "彼と一緒にいた者たちは私が討ち取りました。他の者については存じませんが、まあ、どうでもよろしいでしょう。 なぜならバルトロメオは……";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "そうだ！本当に自分が何をしたのか分かっていないのか！？「アルバトロス号」は島の近くにいて、 お前は自分の残忍さで血に飢えた部下さえも恐れさせる海賊を捕らえたのだ！ここから立ち去れ！島から離れろ！ そしてこの怪物も連れて行け！";
			link.l1 = "しかし、聞いてくれ、約束された報酬はどうなるんだ、それに…";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "私の町があなたの強欲と会社の復讐心のせいで焼かれるのを見たくはありません！私の砦には新兵しかおらず、 その半分は誰がなぜラヴェリンを攻撃しているか知った途端に逃げ出すでしょう！そうなれば虐殺が始まる……私はそんな危険を冒すつもりはありません、聞こえていますか？！さっさと出て行きなさい、 会社があいつの首をそんなに欲しがっているなら、自分でキュラソーまで連れて行きなさい！\nすぐにやりなさい、手遅れになる前に！それに、あいつに何をしようがあなたの勝手です、 船の甲板から突き落としても構いません、ただし私の町の中でだけはやめてください！\nハンス！ハンス、どこだ、この怠け者め！バレリアンの薬か何か持ってこい、そして誰か、 頼むからこの冒険者を私の屋敷から叩き出してくれ！";
			link.l1 = "「しかし閣下……」";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "承知しました！さて、船長、我が島に近づく際にイギリスの軍艦や商船と遭遇されましたか？";
			link.l1 = "いいえ、旦那。私はあなたの領海内でイギリスの旗を掲げた軍艦も商船も一隻も見かけませんでした。";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "なるほど。ここにはどれくらい滞在されるご予定ですか？";
			link.l1 = "「三日ほど……」";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "その場合、あなたに提案がございます。我々の情報によれば、ここにイギリスの間諜が潜んでいる恐れがございます。 島内や町、その周辺、海岸などで怪しい船や人物に関する情報を提供してくださった方には、 一万ペソの報酬を差し上げます。敵の拘束や排除に当局の協力をいただければ、報酬は大幅に増額いたします。\nすべての民間船長の方々に捜査への参加、 並びに地元の海岸やジャングルで間諜を捜索・巡回していただくことを歓迎いたします。\n我々の軍用コルベット艦「ジーパード」と遭遇する可能性がございますが、ご心配には及びません。 哨戒任務中でございますので、もしイギリス人を発見された場合は、その船長に自由にご連絡ください。";
			link.l1 = "あいにくでございますが、閣下、私の訪問はあくまで平和的な交易のためでございます。補給と用事を済ませ次第、 この島を立ち去らねばなりません。";
			link.l1.go = "FMQN_3";
			link.l2 = "魅力的なお誘いだな！俺も参加して、お前の島の海や岸辺を襲撃してやるぜ。しばらくここに滞在するかもしれねえな。";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "ただの情報でございます、船長。ご心配には及びません。何か怪しいことがあれば、 どなたにご報告すべきかはご存じでしょう。";
			link.l1 = "かしこまりました、旦那。承知いたしました。ごきげんよう！";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "素晴らしいです、船長！そこまで真剣でいらっしゃるなら、ぜひ我々の司令官にもお話しください。 彼はスパイ摘発の責任者で、追加の情報を提供できるかもしれません。";
			link.l1 = "承知しました、旦那。これから彼に会いに行きます。";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "お待ちしておりました、旦那\n "+GetFullName(pchar)+"。危険なイギリスの襲撃隊を排除してくださったご行動に、心より感謝の意を表します。 どうかこの一万ペソをお受け取りください。\nさらに、船倉には絹二百反が積み込まれ、特別な褒賞として、オランダ西インド会社の三年許可証が授与されます。 これは非常に貴重な書類でございますが、その価値はご存知でしょう？";
			link.l1 = "もちろんでございます！三年間の許可証――これは確かに大きなことでございます。";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "どうぞ、報酬をお受け取りください。それに、オランダ市民と当局すべての感謝もお約束いたします。 あなたはフィリップスブルフで話題の人ですし、またお越しいただければ幸いです。";
			link.l1 = "このような温かいお言葉をいただけるとは、免許状よりも価値がございます。ありがとうございます、光栄でした。 それでは、そろそろ失礼いたします。ごきげんよう！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "降伏いたします！どうか、聖なる御名にかけて、フィリップスバーグとその市民を略奪したり、掠奪したりなさらぬよう、 お願い申し上げます！ご要求をお聞きする用意がございます！";
			link.l1 = "市民のことはご心配なく、旦那。フランス王冠の臣民はフランス兵を恐れる必要はありません。";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "フランス王家でございますか？";
			link.l1 = "まさにその通り。この島はフランスの領土であり、あなた方はここで間借りしているだけです。 思い上がった借り主どもが、この島を自分たちのものだと信じていたのですね。本日をもって、 セント・マーチンにおけるオランダの権威は終焉を迎えました。\nお分かりですか？";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "しかし…しかし私たち、あなたに降伏したオランダ兵たち、そして負傷者たちはどうなるのですか？それに、何が…";
			link.l1 = "それはすべて、あなた次第でございます、トーマス旦那。もし私にご恩をお返しくだされば、 降伏した者たち全員が負傷者を連れて、我々が港で見つけた船でここを発ち、 キュラソーのスタイフェサント旦那のもとへ向かうことを許可いたしましょう。";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "さもなくば、私の船の船倉やセントキッツの地下牢に閉じ込められることになります。\nさらに、スタイフェサントが我々の植民地への関心を失うように、 重要なオランダの役人たちを何人か処刑しなければなりません……";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "（どもりながら）な、なに……ど、どんなお、お礼の……こと……ですか？";
			link.l1 = "島の奥深くには争いの種――塩鉱山がございます。そこには鉱夫や奴隷だけでなく、武装したオランダ兵もいると存じております。 彼らはきっとカンパニー・ガードの兵士でございましょう、そうではありませんか、旦那？ 私はまず降伏の機会を与えますが、拒めば武力を行使いたします。鉱山への道を案内できる案内人が必要です。 私にそのような案内人を探していただきたい。";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "し、塩……わ、私のもの？";
			link.l1 = "まさにその通りでございます。恐れることはありません、トーマス旦那。 もし鉱山の守衛たちが賢明にも武器を捨てるならば、私は彼らに島を離れる機会を与えましょう。 無用な流血は望みません。ご安心ください、あなたの良心は咎められません――たとえ鉱山の場所を教えてくださらなくとも、サン・マルタン島は十分に小さく、 私一人でも鉱山を見つけることはできます。ただ、藪や沼地をさまよって時間を無駄にしたくないだけなのです。 ですから、この取引は私よりもあなたにとって有利なのですよ。";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "わ、わかった……鉱山への行き方を教える、だが……ぜ、絶対に約束してくれ、こ、この島から……わ、我々全員が出られるようにしてくれ！";
			link.l1 = "私は士官として、そして貴族としてお約束いたします。";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "グラン・ケース湾で…その端のほう、水際の近くに…石があるんだ。そ、そこだ、石の裏、岸沿いに水際の通路があって…そこは浅い、腰まで、いやそれ以下の深さだ。岩を回り込んで行けば大きな浜に出る、そ、 そこは周りに礁があって船を着けることはできない。その浜から道がまっすぐ…鉱山へと続いているんだ。\n";
			link.l1 = "素晴らしい。私は出発します。そして、旦那、 あなたは私が戻るまで私の兵士たちの厳重な監視下でここに留まっていただきます。";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
