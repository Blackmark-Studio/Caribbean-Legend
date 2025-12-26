// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "何を探しているんだ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "はじめまして、船長！";
			link.l1 = "私もお会いできて嬉しいです、フォルジェ旦那。こんな荒野で本国からの客人に会えるなんて、滅多にないことですよ……";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "この航海であなたの船に乗れることを嬉しく思います、船長。 シュヴァリエ・ド・ポアンシーがあなたについて興味深い話をたくさん聞かせてくれました。\n食堂での夕食の後には、きっと語り合う話題が尽きないでしょう。ワインを一杯いただくのも悪くありませんね。";
			link.l1 = "腹が満たされている時は、のんびり語り合うのも大歓迎だ。バロン、喜んであんたの相棒になるぜ。 ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "完璧だ。植民地に着いたら、お前に総督のところまで案内してもらいたい。そして俺が直接、何をすべきか説明する。 お前は俺の用事が終わるまで待っていればいい。いいな？";
			link.l1 = "ああ、フォルジェ旦那。乗船を歓迎するぜ！";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "トルトゥーガは小さな植民地です、船長。私がこの島で必要なものをすべて調査するには、 およそ三日かかると見積もっています。";
			link.l1 = "承知しました、バロン。では三日後にここへ迎えに来ます。ご武運を！";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "トルトゥーガでの仕事は終わった、いよいよ錨を上げる時だ。";
			link.l1 = "承知しました、バロン。すぐに出航いたします。";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "はい、はい、この件は必ずキャップスターヴィルで報告します。これほど重要な植民地が征服される脅威など……考えられません。シュヴァリエ・ド・ポワンシーが厳格かつ容赦ない措置を取るよう、私が直々に手配します！\n船長、私はこの島に一週間滞在します。ここには多くのプランテーションがあり、少し時間がかかりますので。";
			link.l1 = "了解だ、バロン。七日後に総督の宮殿の前で待ってるぜ。楽しんで、無理しすぎるなよ！";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "いたな、船長。ヒスパニョーラでの仕事は終わった、そろそろ錨を上げる時だ。";
			link.l1 = "承知しました、バロン。すぐに出航いたします。";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "船長、この島、見覚えがあるぜ。セントクリストファーじゃねえか？";
			link.l1 = "はい、男爵、まさにその通りです。もうすぐ到着します。";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "もうすぐ着くのか！？サン・マルタンにも寄るはずじゃなかったのか？あそこもフランス領の一部だぜ。";
			link.l1 = "シント・マールテンのことか？オランダの植民地だよ、フォルジェ旦那。";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "そうか？パリではフランス風だとされていたぜ。どうしてだ？";
			link.l1 = "分かりませんな、バロン。俺がこの諸島に初めて足を踏み入れた時から、 シント・マールテンはずっとオランダの植民地でした。俺の知らない何かがあるのかもしれません。 この件についてはシュヴァリエ・ド・ポワンシーに相談してみてはいかがでしょうか。";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "わかったぜ、船長、そうしよう。どうせもうすぐキャップスターヴィルに着くからな。";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+"、船長。お会いできて嬉しいです。昇進されたと聞きました、おめでとうございます！正直に申し上げて、 あなたは本当にド・ポワンシーの配下で最も分別があり、才能ある士官の一人ですよ。";
			link.l1 = "ありがとうございます、旦那。";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "ついに残る植民地はサン・マルタンだけだ。正直言って、もうこの巡回にも飽きてきたよ。この検査を終えて、 次のフランス領西インド諸島の交易遠征の準備に取りかかれるのが楽しみだ。\n出航の準備はできているか？";
			link.l1 = "ああ、男爵。乗り込め。";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "船長、今何が起こったのか教えてくれませんか？\nこれは戦争の始まりってことですか？\n一体全体、なぜオランダ人に沈められかけたんだ？";
			link.l1 = "バロン、俺自身も何も分からねえ！これはきっと何かの誤解に違いねえだろう。";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "船長、この「誤解」にはきっと名前があるはずだぜ！サン・マルタンのいわゆる「借り主」、 そして我らが親愛なるド・ポアンシー騎士殿の相棒、ピーター・スタイフェサントだ！";
			link.l1 = "分かりません、バロン。急いでキャップスターヴィルへ行き、この件を総督に報告した方がいいでしょう。";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "間違いなく、それをやるつもりだ！そして俺は説明を求めるぜ！ オランダ人に島を貸すなんて大きな間違いだと分かってたんだ！誰かに追われる前に、できるだけ早くここを出ようぜ、 船長！";
			link.l1 = "まさに、その通りだ、旦那……";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "旦那、まずはご昇進おめでとうございます！ 私はモンセニョール・ド・ポワンシー閣下があなたに副提督の地位を授ける決断を心から支持しました。あなたこそ、 この称号にふさわしい方です！さて、私は最近サン・マルタンから戻ったばかりです。 フィリップスブルグの倉庫で検査を行い、すべてのオランダの品は没収され、今やフランスの財務省の所有となりました。 作戦の指揮官であるあなたには、戦利品の分け前が与えられています。シュヴァリエも申しておりましたが、 これは当然のことだと私も思います。あなたの品はセントクリストファーの店の倉庫に移されておりますので、 いつでもお受け取りいただけます。";
			link.l1 = "ありがとうございます、バロン。品物はしばらくそこに置いておいてください。キュラソーから戻ったら受け取ります。";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "次の遠征でも幸運を祈ります、副提督！あなたなら必ず勝利して、 あの悪党スタイフェサントを正当に罰してくださると信じております。";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "ここにいるのは誰だ！シャルル・ド・モール副提督じゃねえか！会えて嬉しいぜ！何の用でポルトープランスに来たんだ？ ";
			link.l1 = "私もお会いできて光栄です、バロン。私は任務のためにここに来ました。 ジェレミー・デシャン・デュ・ムサカ旦那にご挨拶に伺わねばなりませんでした……";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "この出会いはまことに幸運です。というのも、私はあなたに直接お会いできる日を長い間待ち望んでおりました。 お話ししたいことがございますが、ここではなく別の場所でお願いしたいのです。";
			link.l1 = "じゃあ、酒場へ行こうか？";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "ここには余計な耳はない、自由に話せるぞ……";
			link.l1 = "聞いてるぜ、バロン。";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "副提督、あなたは名誉を重んじる男のようだな。そんな勇敢な海軍士官なら当然そうでなくてはな…";
			link.l1 = "ふむ……あなたの言っていることが、俺にはいまいちよく分からねえな、旦那……";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "ド・モール旦那、ちょっとお聞きしたいんだが、 あなたの主君であるフィリップ・ド・ポワンシー総督についてどう思っているんだ？";
			link.l1 = "士官の務めは自分の上官について考えることではなく、命令に従うことだ。";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "ああ、やめてくれよ、副提督。ここは兵舎でもなけりゃ、ド・ポワンシーの館でもねえんだぜ。こう言わせてもらうが、 ド・ポワンシー旦那……権力を乱用してると思わねえか？サン・マルタンの砦の大砲で、俺たちが沈みかけたこと、まだ忘れられねえよ。 オランダ野郎の裏切りにも、きっと理由があったはずだ。";
			link.l1 = "奴らは島を征服したがっていた。";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "ああ、そうだ、そうだが、だがなぜ俺がちょうど調べようと決めたその瞬間だったんだ？なぜ一ヶ月前じゃなかった？ それとも二ヶ月後でもよかったはずだろう？これは偶然とは思えん、モンセニョール。お前にも何か疑いはないのか？ あそこで俺たち二人とも命が懸かっていたんだぞ。";
			link.l1 = "俺は毎日命を懸けてるんだ、フォルジェ司教。あんたも分かってるだろう…";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "あなたの勇気には疑いの余地がありません。しかし、それが言いたかったことではないのです。実は……あなたが解放したサン・マルタンで仕事をしていた時、島の奥深くにある鉱山について地元の人々 がひそひそ話しているのを何度も耳にしました。それについて尋ねようとしたのですが、 皆とぼけたふりをするばかりでした。彼らは怯えていたのです……私があまり信用できそうに見えなかったのは明らかでしたが、それがかえって私の疑念を強めました――この謎めいた鉱山こそが、すべての原因ではないかと、ド・モール旦那？戦争は金のために起こるもの、そうでしょう？\n";
			link.l1 = "この諸島には多数の鉱山がある。ほとんどは掘り尽くされて、今では価値がなくなっている。 俺が知っている現役の大きな金鉱は一つだけで、南米本土のスペイン人が所有しているやつだ。だが、 サン・マルタンで金鉱があるなんて話は聞いたことがねえな。";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "副提督殿、あなたは話術の達人ですね！わかりますよ――あなたは私を信用していない。私はここでは新参者です……モール旦那、ですがパリでは私は有力者です。財務大臣は私の親しい友人で、国王にも定期的に謁見しています。 私の権威はフィリップ・ド・ポワンシーよりも遥かに大きいのです、形式的には、もちろん。 ここでは総督が最も権限を持つ人物ですからね。しかし、正直に言えば、この植民地では強き者こそが唯一の掟なのです。 ";
			link.l1 = "俺もまったく同感だぜ。";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "しかし、パリでは違います。あそこでは最も影響力のあるのは国王と財務大臣……私の親しい友人です。ド・モール旦那、あなたは優秀な軍人ですが、 私はフィリップ・ド・ポワンシーがあなたを自分の私的な目的のために利用していると思います。 あなたは賢い方ですから、きっと疑念を抱いているはずです。私を信じてください。 パリ当局の全面的な匿名性と支援を保証します。私の爵位にかけて誓います。";
			link.l1 = "***ポワンシーに忠誠を誓え***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***バロン・フォルジェ側につく***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "分かりますよ、フォルジェ旦那。土地の考え方に慣れていない者には、 ド・ポワンシーの行動は確かに奇妙に見えるかもしれません。私が最初にこの諸島に来たとき、 本当にここで起きていることに衝撃を受けました。今でも最初に言われた言葉を覚えています――「無防備なスペイン船に出会ったら、拿捕を試みてもいい」。裏切り、背信、欺瞞――ここでは至る所にあります。海賊行為、略奪、強盗……";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "ヨーロッパではスペインと和平を結んでいるが、ここでは俺たちは激しい敵同士だ。\nオランダ人は今日こそ友好的で無害に見えるが、明日には会社の役人が「輸入禁止だ」と突然宣言して、 お前の品を没収する――たとえ事前に知る術がなかったとしてもな。\nイギリスの士官は堂々と海賊行為を働き、会社の船を沈めているし、 会社は今度は幽霊船に化けた殺し屋を雇ってイギリスの商人たちを震え上がらせている……";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "この狼の巣窟では、時に外部の者には理解しがたい奇妙な決断を下さねばならんこともある。 君にとって怪しく思えることこそ、実は唯一正しい道なのだ。いくつもの椅子に同時に座りつつ、 本国に利益を送り続けるのは難しいことだが、シュヴァリエ・ド・ポワンシーはそれを完璧にこなしている。 彼は経験豊かな行政官であり、先見の明を持つ政治家だ。もちろん、彼も間違いを犯すことはあるが、 それは誰しも人生のどこかで経験することだろう…";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "そして、お前はすべてのこと、すべての者と渡り合わなきゃならねえ。 新世界のすべてが自分たちのものだと信じているスペイン人の野望、オランダ商人の欲深さ、 イングランド人の冷徹な用心深さと容赦ない残酷さ、そして――海賊どもとも、だ。";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "海賊と一緒に！？";
			link.l1 = "ああ、その通りだ。オランダ人もイギリス人も、実は海賊と積極的に協力している……もちろん非公式に、だがな。カリブの海賊同盟は、この地域のどんな国にも挑めるほどの強大な勢力だぜ。 出会う相手とは常に争いを起こし、誰にも止められねえ。唯一、やつらが少しだけ危険度を下げている理由は、 バラバラに行動し、それぞれが自分のために動いているからだ。トルトゥーガの元総督ルヴァスールが、 実は完全に海賊に頼った「国家の中の国家」を作り上げたって知ってたか？";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "それについて何か聞いたことがある気がする……";
			link.l1 = "トルトゥーガの港には、島を守る数隻の強力な私掠船が常に停泊していた。\nルヴァスールはフランスを裏切り、地元の権力者のような存在となった。\nそして今、トルトゥーガの海賊の巣とその主が滅ぼされたことで、海賊たちはフランス人に対してひどく怒っている……";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "そりゃ驚いたぜ！";
			link.l1 = "ああ、そうだ。我々はやらざるを得なかった、さもなければトルトゥーガは失われていただろう。だが、 得られた結果は決して最良とは言えない。今やカリブ海では、フランスの商船はどれも安心できない状況だ。 スペイン人もまた海賊男爵たちと協定を結んでいないが、少なくとも強力なガレオン船や戦艦の艦隊を持ち、 フィリバスターどもを撃退できる。オランダ人も東インドマンやシーベックで同じだ。しかし、我々 にはそんな自慢できるものはない、残念ながらな。そしてフランスの海賊はしばしばフランスの商人を襲うのさ。";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "こんなの狂気だ！これを終わらせる方法はないのか？";
			link.l1 = "多くの者が挑戦したが、結局のところ戦う代わりに金で忠誠を買うんだ。私掠免許状を発行するってわけさ。";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "ふむ……";
			link.l1 = "だから、経験から言わせてもらうと、この諸島でフランスの交易会社を作るなんて、とんでもなく悪い考えだぜ。\n今になって、お前が直面する困難がわかったか？ここで稼ぎにありつこうとする野郎どもがどれだけいるか知ってるか？ しかも、そいつらは簡単には手を引かねえ。\nそれに海賊ども、あいつらは常識じゃ考えられねえことをやってのける。狂ってると言いたきゃ言えよ、 だが奴らはほとんどの場合、汚い目的を達成しちまうんだ。\n商船を守るためには、でかい軍艦隊を維持しなきゃならねえが、それで本当に儲かるのか？";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "しかしフランスの商人たちはここで何とかやっているのか？";
			link.l1 = "そうだ、何とかね。特に今はな、トルトゥーガのルヴァスールの海賊要塞が奪われちまったからな……";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "お前の言葉はド・ポワンシーの話と一致しているな。";
			link.l1 = "本当のことだ。ここ諸島じゃ、そういうもんさ、昔からずっとな。";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "お前の話しぶりはずいぶん熱心だな。俺ですらこんなことはあまり知らなかったし、確かにその通りだ――今もよく分かっちゃいない。ポワンシーへの疑いは見当違いだったようだ。目を覚まさせてくれて感謝する、副提督殿。 だがフランスの大臣は会社の設立を頼みにしている。国王も金を必要としているんだ……";
			link.l1 = "承知しました。しかし、今申し上げたことをぜひご考慮ください。 もしフランス領西インド諸島の建設が避けられないのであれば、それを守るための強力な軍艦隊を必ずご用意ください。";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "副提督殿、そのご威光には本当に感服いたします！なんと高貴なお人柄でしょう！これほど長くここに滞在され、 故郷に急いで戻られないのも納得です。\nですが、またお会いしましょう。半年後にここへ戻ります。フランス交易会社は必ずや隆盛いたします。そして、 海賊についてですが、少々大げさにおっしゃっているのでは？何と言っても、我々 にはあなたのような勇敢な船長や軍艦がいるのですから。";
			link.l1 = "申し訳ありません、バロン。しかし私はただの一人の人間ですし、フランスには私以外にこの諸島で強い船は 「エクラタン」一隻しかありません。それだけでは足りませんし、得るものよりも失うものの方がずっと多いでしょう……まあ、仕方ありません。とりあえず何か考えましょう……ところで、バロンはいつフランスへ発たれるのですか？";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "二週間後にはサン・クリストファーへ戻り、そこから故郷へ向かうつもりだ。ド・ポワンシー旦那が立派な船――「ファヴォリー」というブリッグと素晴らしい船長を与えてくれた。船は速く、船長も経験豊富だが、 やはり君と一緒のほうが安心できたよ。諸提督、君と群島を巡った旅を今でも覚えている。本当に素晴らしい経験だった。 ";
			link.l1 = "ご親切なお言葉、ありがとうございます、バロン。さて、そろそろお別れの時のようですね…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "ここでは、誰もが互いを利用しているんだ。シュヴァリエは、俺が海軍の士官になるずっと前から、 自分の取引で俺を利用していたんだぜ。";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "それでいいのか？どう思う？";
			link.l1 = "いいえ。しかしシュヴァリエに選択肢を奪われたんだ。命令に従うか、さもなければ俺の兄貴は一生牢獄に閉じ込められ、 家族の名誉も地に落ちることになっていた。";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "ひどい！これはまさにテロ行為だ！そんな脅しをする理由があったのか？";
			link.l1 = "俺の兄貴はあいつの信頼を得た男だったんだ。不運にもな。今の俺と同じようにな。";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "今、お前の兄貴はどこにいるんだ？";
			link.l1 = "俺は奴を解放することに成功したが、翌日には失ってしまった。もう誰の下にも仕えないと奴は決めたんだ。";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "ポワンシーが自分の正体を偽っていると俺は知っていたぜ！羊の皮をかぶった狼だ！副提督、俺を信じてくれ。 俺は名誉を重んじる男だ。そして、もしあいつの犯罪行為の確かな証拠を見つけられれば、あんたをその『後ろ盾』 のくびきから救い出してやる。スタイフェサントとのこの退屈な話について、何か知っているか？率直に話してくれ、 心配はいらねえ――あんたはただの軍人で、命令に従う義務があっただけだ。";
			link.l1 = "知っている。サン・マルタンには確かに鉱山があるんだ。だが、あそこでは金じゃなくて塩が採れるんだよ。 スペイン人の間で大変な需要がある。ポワンシーはスペイン人と直接取引できなかったから、 スタイフェサントが仲介役を務めたのさ。";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "ポワンシーとスタイフェサントは商売仲間ってことか？";
			link.l1 = "昔はそうだった。お前がサン・マルタンを調査したいと言った後、 スタイフェサントはポワンシーを排除して塩鉱山の利益を独り占めしようと決めたんだ。 ポワンシーは誰にも言えなかった……だが、見ての通りスタイフェサントの計算違いだったな。";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "鉱山はまだ稼働していると思うか？";
			link.l1 = "間違いない。どうやらポワンシーには新しい交易の同盟者ができたようだ。しかも、 その相手は他でもないドイリー大佐本人だ。";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "我々は何か証拠を省庁に提出できるか？";
			link.l1 = "ふむ。ちなみに、鉱山の襲撃はオランダ人じゃなくてスペイン人がやったんだが、その時に俺たちは鉱山主を捕まえた。 今も俺の船にいるぜ。話したければ会わせてやる。もしかしたら、 自由と引き換えに面白い話をいろいろ聞かせてくれるかもしれねえぞ。";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "すぐにお前の船へ行こう。囚人をお前の船室に連れて行くよう命じろ。俺がそいつと話をする。";
			link.l1 = "よし、行こうぜ。";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "素晴らしいですね、副提督。俺が彼と話してくる。ここで待っていてくれ。";
			link.l1 = "もちろん……";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "お前の捕虜から得た証拠はすべて書き留めて、本人にも署名させた。これで俺が約束したことを果たさなきゃならねえ。 都合のいい機会があれば、カルタヘナに寄って奴を上陸させてやれ。ただし、お前も全部聞いていただろう。\nさて、うちのポワンシーはなんて悪党なんだ！あいつはオランダ人に島を貸し出し、そこで違法なことをやらせて、 スペイン人まで行かせて鉱山を管理させていたんだ！あいつの身勝手のせいで、 王の財務庫からどれだけ金が消えているか、想像するのも怖いぜ！";
			link.l1 = "その証拠でポワンシーを告発するには十分か？";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "残念だが、そうはならないと思う。証拠はとても重要だが、それだけでは足りないんだ。しかし、 俺たち二人とも分かっている理由で、君にはこれ以上関わってほしくないんだ。";
			link.l1 = "スペイン人は、あなたの委員会がここに到着した際に証言することに同意した。";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "これは今から半年以上先のことになるだろうし、このスペイン野郎がどうなるかも、 後でカルタヘナで見つけられるかどうかも分からねえ……。もっと価値のある証拠が必要だ。つまり――鉱山が今も秘密裏に稼働していて、我らが総督閣下の懐を潤し続けているという証拠だ。";
			link.l1 = "つまり、俺たちがサン・マルタンまで行くってことか？";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "ああ。鉱山への行き方を知っているか？";
			link.l1 = "そうだ。";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "それから夜になったら、俺とお前でこっそりあそこに忍び込むんだ。誰にも見つからないようにして、 中で何が起きてるか確かめようぜ。";
			link.l1 = "「よし、いいだろう。」";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "「だが、シュヴァリエのことはどうするんだ、え？今になって、あいつがなぜあんなに堂々と、 群島にフランス東インド会社を設立するのは儲からねえってほのめかしたのか分かったぜ……そりゃ、あいつにとっちゃ一番損な話だからな！」";
			link.l1 = "今や俺たちは同盟者だ、バロン。だから本当のことを全部話そう。ポワンシーが俺に頼んだんだ……あんたにここで商会を作らないよう説得してくれとな。";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "そういうことか！少なくとも、あいつはお前に俺を剣やピストルで始末しろなんて頼まなかっただろうな？";
			link.l1 = "いいや。お前には別の方法で納得してもらう必要があったんだ。";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "ポワンシーの仕打ちは必ず報いを受けさせるが、今はすぐにサン・マルタンへ向けて出航しなきゃならねえ。 スペイン野郎は後で本土に送り届ける。\n出発するぞ、副提督！";
			link.l1 = "俺の船で島を離れるなんて、ちょっと変に思われるんじゃねえか？";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "そうは思わねえな。お前が俺を説得するはずだったんじゃねえのか？まさにその通りにやったじゃねえか、はは！ああ、 ヨーロッパへ出航する前に、シュヴァリエには「お前の意見に賛成だし、商会は作らねえ」と伝えてやるさ。 今は嘘の安らぎの中でのんびりさせてやろうぜ……さあ、行くぞ！\n";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "案内してくれ、副提督。夜の闇が俺たちを覆い隠してくれるだろう。";
			link.l1 = "ついて来い…";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "（ひそひそ声）見たんだ！見たんだ！お前も見たか？赤い軍服だ！あれはイギリス兵だぞ！";
			link.l1 = "言っただろう、今はポワンシーがドイリー大佐と取引してるんだ。";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "お前の言う通りだった。もう十分見た。今すぐ見つかる前にここから逃げよう！";
			link.l1 = "同意だ……";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "ご覧の通り、我らが親愛なるシュヴァリエの「商業計画」がどこへ行き着いたか！ イギリス野郎どもがフランスの島でまるで主人面しやがってる！こんなの、許せねえぜ！";
			link.l1 = "動かないと誰かが必ずここに来るぞ。\n俺たちは顔が割れるわけにはいかねえ。";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "副提督、サン・マルタンへの航海中ずっと考えてきましたが、決心がつきました。 ピーテル・スタイフェサントとの面会を手配していただけますか？";
			link.l1 = "スタイフェサントと一緒に？しかし、なぜだ？";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "かつての商売仲間が重要な手がかりや、シュヴァリエたちの関与を裏付ける確かな証拠を持っているかもしれねえ。 スタイフェサントはポワンシーにかなり不満を持ってるはずだし、特に最近の出来事の後じゃ、 きっと復讐を企むだろうな……";
			link.l1 = "そう思います、バロン。私自身はスタイフェサントの宮殿へ行く勇気はありません。私が彼らにしてきたことを考えると、 あまりにも危険すぎます……";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "もう考えてある。俺たちはキュラソーへ行き、町から離れた入り江で上陸する。それから、 鉱山にいた捕虜のスペイン人を手紙と一緒にスタイフェサントのもとへ送るつもりだ。そこでお前のことは触れない。 その代わり、ポワンシーを調査しているとか、そんな内容を伝えるつもりだ。 オランダ野郎はきっと指定の場所に来るだろう。";
			link.l1 = "ふむ。これはいい考えじゃないと思うぜ。スタイフェサントは馬鹿じゃねえ、取れるものは何でも取るし、 お前を投獄して莫大な身代金を要求するかもしれねえ。だが、すべての出来事がポワンシーのせいだと信じ込ませれば、 あいつが俺たちの味方になる可能性もある。まあ、そこまで決意してるなら、やってみようじゃねえか。";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "ド・モール旦那、どうか私の愚かさをお許しください。スタイフェサントについてはあなたが正しかったです。 ド・ポワンシーに挑めるのは、さらに大悪党だけだと気づくべきでした！";
			link.l1 = "ははっ！百万か……ポワンシーは百万欲しがり、ストイフェサントも百万欲しがる……まるで堂々巡りじゃねえか……";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "何を言っているんだ、副提督？";
			link.l1 = "カリブに着いた時、ポワンシーは俺の兄弟の身代金として百万払えと言ってきたんだ。";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "それでそんなに払ったのか？";
			link.l1 = "俺が稼いで、俺が払ったんだ。もちろん一ヶ月でじゃねえよ。正直言うと、あの頃の俺はただの陸の者だった。でもな、 シュヴァリエはミシェルを放さなかったんだ。";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "「それでその後、ポアンシーの下で働くことにしたのか？正直、お前の考えがわからねえな。」";
			link.l1 = "俺はフランスと愛する者たちのために志願したんだ。王以外には誰にも頭は下げねえ。";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "失礼します、ド・モール旦那。もちろん、あなたはフランスと国王に仕えているのですね！ ポワンシーはすべての責任を取るでしょう！あなたに与えた苦しみも含めてな。";
			link.l1 = "よろしい、バロン、何とか都合をつけて百万用意しよう。乗船しろ……この問題は俺が解決する。";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "俺に会いたかったのか、副提督？";
			link.l1 = "ああ。スタイフェサントと会談した。これが彼の台帳だ。";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "信じられねえ！うーん、どれどれ……（読みながら）";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "これで終わりだ！我らが親愛なるシュヴァリエはもうおしまいだぜ。財務大臣がこの帳簿を全部見たら……あいつがどうなるか想像もつかねえ。カタルヘナのスペイン野郎を探す必要すらねえよ。モール旦那、 本当にこの本に百万も払ったのか？\n";
			link.l1 = "やったさ。もし他の手を打てば、フランスは内戦でカリブの植民地を失うかもしれない。俺が勝つこともできるだろうが、 自分の同胞と戦う提督なんて、どんな提督だっていうんだ。";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "お名前にふさわしいお方ですね。副提督殿、必ずやお取り戻しすることを誓います。 ポワンシーの金庫や高利貸しどもから、かなりの金額が見つかるはずです。\nただ、私がヨーロッパから任命状を持って戻るまで、半年だけお待ちいただきたいのです。";
			link.l1 = "それから、訓練された武装兵士の一隊を連れてくるのを忘れるなよ。それと『エクラタン』のような船もな。俺は『 エクラタン』の船長も、いざという時には俺たちの味方になると信じてるぜ。";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "疑うな、彼もまた立派な男だ。私は道徳的価値観が自分自身の決断に大きな役割を果たすことに気づいた。 俺を信じてこの国家犯罪者を暴いたお前の判断は見事だったぜ。さあ、カプスターヴィルまで案内してくれ。 そこでポワンシーにお前の任務の成功を報告するつもりだ――お前は俺を説得することに成功し、俺は交易会社設立の考えを捨てることにした。 もしかしたらポワンシーはお前に褒美を与えるかもしれん――その時は胸を張って受け取れ、何も心配することはない。お前ほどふさわしい者はいないからな。 お前がこの件に巻き込まれることもなければ、上司の悪事で名が汚れることもない。むしろ、 王に会った時にはお前のことを最大限に褒めておくつもりだ。バロン・フォルジェは名誉と約束を守る男だ。";
			link.l1 = "嬉しいです、バロン。さあ、出発しましょう！";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "さて、副提督、ついに到着しましたな。あなたの任務はこれで終わり、あとは私の役目です。自分の仕事に戻り、 これまで通りフランスの利益を守ってください。およそ半年もすれば、この卑劣な事件も終わります。 必要な時はこちらから使者を送ります。\nさらばです、ド・モール旦那、ここで誠実な男に出会えたのは本当に幸運でした！ 大臣も国王もあなたのことを耳にするでしょう、それは約束します。そして、彼らが聞くのは良い話だけです。";
			link.l1 = "ありがとうございます、バロン。良い航海を！";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "お会いできて嬉しいです、副提督。約束通り、また参りました。そしてご一緒しているのは、 財務大臣第一補佐官のオリヴィエ・ブルダン男爵です。";
			link.l1 = "シュヴァリエ・ド・ポワンシーはどこだ？";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "あいつは本来いるべき場所、つまり牢屋にいる。逮捕されてフランスに送られ、捜査と裁判を受けることになる。 立場を考えれば、処刑は免れるだろうが、莫大な罰金と降格、そしておそらく投獄は避けられないだろう。";
			link.l1 = "逮捕は平和的だったか？";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "いや、そうでもない。シュヴァリエはこの邸宅に忠実な兵士たちを大勢従えていた。しかし、 俺たちはこうなることを事前に想定して準備していたんだ。";
			link.l1 = "さて、それではおめでとうございます、バロン！これでフランス商会に取りかかるつもりですか？";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "俺か？ああ、そうだ。閣下ボルダン旦那はポワンシー騎士と共にフランスへ戻ることになる。\nそれに、お前もだ、副提督。変化があるはずだぜ。今や新しい役職がある。詳しいことは閣下から聞くといい。";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "モール旦那！ちょっと待ってくれ！";
			link.l1 = "はい、バロン。聞いております。";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "スタイフェサントに支払った百万についてだが……私はこの件を省庁には報告しなかった。\nなぜなら、フランスの士官がどうやってそれほどの大金を手に入れたのか、といった質問を避けるためだ。\nこれはお前にとって不利だったかもしれん。なぜなら、 彼らはきっとお前自身の金で国王の財庫を増やすよう求めただろうからな。";
			link.l1 = "承知しました、ありがとうございます。";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "カステルヴィルでポワンシーが所持していた金はすべてバルダン男爵に没収された。しかし、 実はポワンシーにはイギリスの金貸したちが隠していた隠し財産もあったのだ。私は彼に投資金の返還について話し、 それから君への補償方法を考えよう。";
			link.l1 = "イギリスの金貸しどもから何かを奪うのは、そう簡単にはいかねえだろうな。";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "同感だ。しかし、これから取り組んでいくし、結果については随時報告するぜ。";
			link.l1 = "ご希望通りに。";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "副提督、顔色が優れないようだが、俺の気のせいか？植民地で最高位を得たばかりじゃねえか！";
			link.l1 = "いや、いや、全然そんなことは……ただ、すべてがあまりにも突然で、ちょっと戸惑っているんだ。";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "心配するな。新しい立場にもすぐ慣れるさ。それに、半年間もサン・マルタンの総督として立派にやってきたんだ、 今回のことなんてお前には朝飯前だろう。";
			link.l1 = "ああ、そのうち慣れるさ。カリブに来てから、もっとひどい目にも遭ってきたんだ。今回もなんとかなるだろうよ。";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "まあ、いいだろう。それに加えて、もうひとつ君へのサプライズがあるんだ。きっと気に入ると思うよ。\nだがまずは、邸宅に戻ってくれ。誰かがそこで我々を待っているはずだ。";
			link.l1 = "興味をそそられましたよ、Forget旦那。さて、戻りましょう。";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "大丈夫ですよ、侯爵。真の船長はまず自分の船を気にかけるべきですからね。\nシャルル、戦列艦『エクラタン』の船長ユベール・ダシエ侯爵を覚えていますか？";
			link.l1 = "もちろん覚えているさ！あいつがいなけりゃ、今の俺は生きていないだろう。海軍士官同士の最も強い友情は、 肩を並べて戦った戦場で生まれるんだ。ダシエ旦那は信じられないほど経験豊富な船長だと証明してくれたよ。";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "副提督殿、以下の件をご報告申し上げます。\n諸島内フランス植民地の臨時総督へのご就任に加え、閣下の旗艦についても取り上げました。";
			link.l1 = "旗艦か？";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "その通りです。私の知る限り、あなたがフランスの任務に就いた際、重コルベット艦『グリフォンドール』 が与えられましたね。確かに素晴らしい船ですが、やはり士官向けであり、副提督、 そして今や総督であるあなたにはふさわしくありません。あなたはここでフランスの顔なのです。 旗艦もそれに見合うべきでしょう。そこで、カリブで最初の戦いを経験したあの船を、 あなたの艦隊に加えることに決めました…";
			link.l1 = "フォルジェ旦那、あなたは言おうとしているのか……";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "これより、フランス海軍の誇りである六十六門戦列艦『エクラタン』があなたの指揮下に入る！ この決定は国王陛下のお許しを得ているぞ！";
			link.l1 = "しかしバロン、俺はただ受け取るわけには……";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "できるさ、シャルル。これは議論の余地はない。フランスでは、「エクラタン」は特別にお前のために改装されたんだ。 なぜなら、結局のところ、カリブにはヨーロッパのような大規模な海戦はなく、その分、個々の船への要求が高いからだ。 ここでは、船の性能と船長の経験がすべてを決める。「エクラタン」は船体が強化され、積載量と乗組員数が増やされ、 帆装も少し手直しされて風上に近づけるようになった。そして、すべての大砲が完全に取り替えられ、我々 が持つ中で最も強力な四十二口径砲が装備されたんだ。";
			link.l1 = "ああ、今やこの船は本当に海の支配者だ……だが、旦那フォルジェ、この船の船長はユベール・ダシエ侯爵だ。俺には彼から奪えねえ……";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "まだお伝えしていなかったのですが、マルキ自身があなたの指揮下で仕えたいと強く望んでいるのです……ダシエ旦那？";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "はい、ダシエ様、これ以上お引き止めはしません。";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "俺たちだけの話だが、チャールズ、お前はマルキを引き続き雇ったほうがいいぜ。 あんな経験豊富な船長は他にいないって、俺が保証する。";
			link.l1 = "信じてください、バロン。私はスペインやオランダとの戦いの中で、これを自ら目撃する栄誉にあずかりました。 ダシエ旦那は本当に優秀な戦闘士官であり、私の友人でもあります。";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "さて、それではこれにて失礼いたします、総督閣下！事は待ってはくれません――商会設立の仕事は初日から始まるのです。また近いうちにお会いしましょう！";
			link.l1 = "ご武運を、Forget様。商売のご成功もお祈りします！";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "副提督殿、心より感謝の意を表します！あの忌々しい海賊どもから私を解放し、命を救っていただきました。 あなたとフィリップ・ド・ポワンシーにも感謝します。正直に申し上げますが、 私は彼について完全に誤った判断をしていました。そのことをどうかお許しください。 あなたとシュヴァリエの言う通りでした――フランス東インド会社はここで大いに苦労するでしょうし、結局は損をするだけのようです。ここにいる島々 の狼どもに立ち向かえるのは、ポワンシーのような経験豊富な者と、あなたのような勇敢な兵士だけです。 私は宮殿へ行かねばなりません。その後、できるだけ早くヨーロッパへ戻り、この悪夢を忘れるつもりです。";
			link.l1 = "すべてうまくいって良かったです、バロン。さようなら！";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+"、旦那。何の用で『エクラタン』の甲板に来たんだ？";
			link.l1 = TimeGreeting()+"、旦那。自己紹介させていただきます――シャルル・ド・モール船長です。私は群島にあるフランス植民地総督、シュヴァリエ・ド・ポワンシー殿から参りました。 あなたの船を私の戦隊に編入し、私の指揮下に置くよう命じられております。こちらがその書簡です…";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "何かの間違いだ、旦那。あなたはフランス海軍の戦列艦の上に立っているんだ。 俺が命令を受けるのは王立海軍に仕える者だけだぜ。だが、あんたはその艦隊の徽章も持っていないし、 所属しているようにも見えねえ。もしかして、俺たちの船を他の船と間違えたんじゃないか。";
			link.l1 = "しかし…";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "ほう、この制服じゃお前だと気づかなかったぜ、船長。さて、その手紙を見せてくれ、中身を確認したいんだ。";
				link.l1 = "「ほら。」";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "もうすべて話し合っただろう、旦那……";
				link.l1 = "ふむ……";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "さて、と……（読みながら）面白いな。つまり、俺と俺の船はお前の指揮下に入るってことか、ド・モール船長？";
			link.l1 = "「それが総督の命令だ。」";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "ああ、ああ、命令には逆らえん。よろしい。自己紹介しよう。私はユベール・ダシエ侯爵、フランス海軍の66門戦列艦『エクラタン』の船長だ。この精鋭の乗組員と共に、そして名誉にかけて誓うが、 これはフランスが誇る最高の艦の一つだ。";
			link.l1 = "それは良かった、総督から与えられた任務には航海術と砲術の知識が必要になるからな。";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "このこれから行う作戦の詳細を教えてくれるか？";
			link.l1 = "もちろんだ。俺たちはここから南東へ一週間ほど航海した先にあるスペイン領トリニダード島へ向かう。 サンホセ植民地を守る砦に奇襲をかけて、徹底的に破壊するつもりだ。その後、つい最近フランス領サン＝ ピエール入植地が襲撃された件について、スペイン側と補償交渉を行う。";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "なるほど。いつ出発するんだ？";
			link.l1 = "できるだけ早く頼む。今月中にこの任務を終えなきゃならないが、時間は十分にある。";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "わかった、de Maure船長。あなたの号令で出航する。";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "何かご命令、あるいはご質問でもございますか、de Maure船長？";
			link.l1 = "「まだだ……」";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "しかし、ド・モール船長、まずは艦隊を小さくしないといけません――私の船が加わると、艦隊が大きくなりすぎてしまいます。";
			link.l1 = "ふん。お前の言う通りだ。ここ港に一隻残しておくぜ。";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "まだ戦隊を減らしていないのか、旦那？";
				link.l1 = "ああ、ああ、覚えてるよ、今やってるところだ。";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "それでは、「エクラタン」はあなたの艦隊に加わる準備ができました、旦那。";
				link.l1 = "それじゃあ俺は自分の船に戻るぜ、あんたも出航の準備をしておけよ。";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "ごきげんよう、コモドール。これからまた戦いが待っているのか？";
			link.l1 = "ああ、その通りだ。また力を合わせる時が来た。これからフィリップスブルフを攻めるぞ。 総督からサン・マルタンのオランダ人どもを一掃するよう命じられたんだ。";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "ええ、船長、でももう少し後になります。時が来たらお伝えします。「エクラタン号」 はいつでも出航できるように準備しておかねばなりません。";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "すべて了解しました。これは厳しい任務になりますぞ、閣下。私の聞いたところによれば、 フィリップスバーグの砦には大砲がたくさんあるそうです。";
			link.l1 = "間違いないさ、相棒。でも何とかなるぜ。出航の準備をしろ、もうすぐ出発だ。";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "『エクラタン』の甲板でお会いできて嬉しいです、副提督！ご命令は？";
			link.l1 = "『エクラタン』号の出航準備をしろ。まずジャマイカ沿岸へ向かい、 その後ドイル大佐の艦隊と共にキュラソーを攻撃するぞ。";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "命令は後で出す、船長。いつかは私が知らせる。「エクラタン」はいつでも出航できるように準備しておけ。";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "「エクラタン号」とその乗組員は準備万端です、副提督！";
			link.l1 = "素晴らしい。では、すぐに出発するぞ。";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "失礼します、旦那方。先ほどは船で指示を出すのに手間取って、合流が遅れてしまいました。 すでに邸宅でお会いできなかったので、かなり遅れたと思い、船に戻ろうとしていたところです…";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "あなたと共に戦えたことは、私にとって光栄でした、ド・モール様！これほど有能で腕の立つ士官には、 滅多にお目にかかれません。あのトリニダードのスペイン植民地の砦を、あんなに素早く攻略することは、 私には到底できなかったでしょう！";
			link.l1 = "自分を過小評価しているな、ダシエ旦那。俺たちは一緒に解決したじゃねえか。";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "その通りです。私は侯爵でありながら、今もなお一人の船乗りです。私にとってカリブ諸島は新しく、未踏で、 冒険に満ちています。前回ここにいたのはほんの数か月でしたが、ヨーロッパに戻ったとき、 この地が恋しくなったのです。ここで祖国に尽くしたいと考えております。そして、あなたは非常に才能があり、 経験豊富な船長です。あなたのおかげで私は心からの敬意と友情を抱くようになりました。副提督、 あなたの指揮下で仕えることができれば光栄です！";
			link.l1 = "まあ、俺にはできねえし、しかもな！それに断りたくもねえんだ、ダシエ旦那！";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "エクラタン号が今やあなたの旗艦になったことも承知していますので、あなたが自らその指揮を執ると決めても、 私は十分に理解できます。その場合、私を士官として残しても、別の船を与えても、 あるいは単に職務を解いていただいても構いません――フォルジェ旦那が親切にも、 その際はフランス西インド会社艦隊で私にふさわしい地位を見つけてくださると約束してくれました。";
			link.l1 = "安心しろ、友よ、そんな事にはならないさ。お前は俺が今まで会った中でも最高の船長の一人だ。 お前が俺のそばにいれば、俺たちは無敵だぜ。";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "私の能力をそこまで高く評価していただき、ありがとうございます。それともう一つ、副提督。 今のところあなたの戦隊の規模は存じませんので、念のため、 カプスターヴィルの埠頭に停泊中のエクラタン号の艦長ブリッジでお待ちしております。 艦を指揮下に置くご決断をされた際は、どうぞご一報ください。";
			link.l1 = "かしこまりました、Dassier様。";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "それでは、ここで失礼させていただきます。副提督閣下、男爵閣下……";
			link.l1 = "また会いましょう、Dassier様。";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "副提督、乗船を歓迎します。エクラタン号をあなたの指揮下に置きたいですか？";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "まだです、マルキ。指示をお待ちください。";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "はい、マルキ殿、あなたに私の艦隊に加わっていただきたいのです。 この美しい船はカリブにおけるフランスの偉大さと力の象徴となるでしょう！";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "まったく同感でございます、閣下！";
			link.l1 = "…さて、俺たちの本当の力を見せてやろうじゃねえか！";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "おや、なんて知り合いだ！あれはシャルル・ド・モール船長ご本人じゃねえか！？ 今じゃフランス海軍で地位を得たって聞いたぜ。前は誰のために“働いて”たかを考えると、いやはや驚きだな……";
				link.l1 = "ごきげんよう、旦那。イスラ・テソロの件をおっしゃっているのですか？\nああ、しかし、あの島が発見者の遺言に従って、 その相続人に受け継がれるというイギリスの法律を書いたのは私ではありません。\nですから、私に非はありません。私はただシャープ嬢が正当に受け継ぐべきものを手に入れる手助けをしただけです。";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+"「船長。フランス海軍の代表が重要な目的を持ってアンティグアに到着したのでしょうか？」";
				link.l1 = "確かに、旦那。私はフランス植民地総督フィリップ・ド・ポアンシー閣下からここへ派遣されました。 サン・クリストファーはスペインとオランダの艦隊に包囲されています。 シュヴァリエはあなたとジョナサン・フォックス旦那にも助けを求めています。こちらが大佐への彼の書簡です。";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "気になるんだが、船長、この件でいくら稼いだんだ？かなりの額だろうな、 あのならず者ロクスリーの雇い賃を払えるくらいなんだから、安くはないはずだ。海賊の大物どもも、 島を手中に収めているお前に、定期的に上納金を払っているんだろう？\n俺たち二人とも、ヘレン・シャープなんてただの仮面にすぎないってことはよく分かってるさ。";
			link.l1 = "大佐、我々もよく知っている通り、海賊の大物たちは主にイングランドの利益のために動いているんだ、 もちろん公式にはそうじゃないが……。彼らがいなければ、この地域でスペインの覇権に対抗するのはかなり難しかったはずだ、そう思わないか？だから、 政治家たちの視点からすれば、「コーストの兄弟団」が島を自分たちだけで保ってきたという事実は、 もしかするとイスラ・テソロがイングランドの海軍基地になった場合よりも、ずっと利益になったかもしれないな……。";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "それは確かに一理ありますな、船長。しかし……まあ、そういうことにしておきましょう。あなたが何か重要な目的を持ってアンティグアに来たのだと思いますが？ もしかして、かつての同盟国であるフランスとオランダの関係が著しく悪化したことと関係があるのでは？";
			link.l1 = "まったくその通りだ。私はフランス植民地総督フィリップ・ド・ポワンシーから派遣された。\nサン・クリストファーはスペインとオランダの艦隊に包囲されている。\nシュヴァリエがあなたの助力を求めている。これが彼からの手紙だ、大佐。";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "見せてくれ……（読んでいる）";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "ふむ……実に興味深いな！船長、君の上官は確かに俺の興味をそそる術を知っているようだ。 奴が狡猾な狐と呼ばれるのも無理はない。オランダ人と親しくなろうとするより、 こんなことはもっと早くやるべきだったんだ。我々はオランダ会社とその総督が何者か、よく知っているからな。さて、 こうなった以上、包囲されたカスターヴィルを助けるのを断る理由はないし、兵も十分に揃っている。\nさて、彼らの戦隊の艦船の数と種類はどうなっている、船長？";
			link.l1 = "俺が数えたのは六隻だ。三等戦列艦の八十門艦が一隻、四等艦が五隻。フリゲートやガレオンもいるかもしれねえ。";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "ふむ……我々の戦隊を出撃させることができるな。百門搭載の一等戦列艦一隻、四等艦二隻、 そして重フリゲート艦一隻で構成されている。\n彼らの艦隊に対抗できるぞ。";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "旦那、我々には66門砲の戦列艦『エクラタン』もございます、 グアドループの沿岸からサン・クリストファー防衛の援軍として航行中でございます。";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "これからの戦いでは、一等艦が大いに役立つだろう。";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "完璧だ。その場合、俺たちは敵の砲撃範囲を十分に離れている。勝利は俺たちのものだぜ。";
			link.l1 = "それに俺自身の船も忘れるな、旦那。こんな戦いを見逃すつもりはねえ、考えるまでもねえさ。";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "それは本当だ。カスターヴィルの砦の助けがあれば、勝利は俺たちのものだ。";
			link.l1 = "それに俺自身の船も忘れるな、旦那。こんな戦いを見逃すつもりはねえ、考えるだけ無駄だぜ。";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "もちろんでございます、ド・モール旦那。いずれにせよ、あなたの航海の腕前は群島中に知れ渡っております。 あなたの旗艦が艦隊を率いることになります。";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "俺は自分の戦隊の残りの船を待機させてから戻る。それで一緒に包囲された者たちの救援に駆けつけようぜ。";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "すぐに俺の船を準備して、包囲されている者たちの救援に駆けつけるぜ。";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "それで、出発する準備はできたか？";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "「ちょっと待ってくれ、旦那。」";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "「はい、旦那。」";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "それでは始めよう、神のご加護を！";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "他に何か質問はありますか、旦那？";
			link.l1 = "いいえ、Colonel…";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "スタイヴェサント宛の手紙を受け取れ、旦那。私のことをご存じないなら、自己紹介させていただこう。 私はエドワード・ドイリー大佐、ポートロイヤルの総督であり、この遠征の指揮官だ！\n正直に言えば、ウィレムスタッドと呼ばれる盗賊の隠れ家を地上から消し去りたい衝動に駆られている。 カリブで最も卑劣で裏表のある、忌まわしい組織――オランダ西インド会社。彼らは諸島のすべての交易が自分たちの独占権だと信じ、 ジェイコブ・ファン・ベルクのような連中や他の海賊どもを雇って、イギリス商人の船を拿捕し沈めているのだ……";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "俺はこの無法な行為に終止符を打つために来たんだが、運のいいことに、今回は外交的な解決策を提案してやる。 今のところはな……だが、この忌まわしい組織の責任者が話し合いのためにここに来なければ、奴の商売は徹底的に潰してやる。 俺たちが街を襲撃した後は、灰しか残さねえし、見つけた火薬は全部お前らの砦の地下にぶち込んで吹き飛ばしてやる。 同じ運命がプランテーションにも待ってるぜ、 そしてスタイフェサント自身は俺の旗艦のヤードアームに吊るされることになる……\n";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "お前の植民地を再建するには一年以上かかるだろうし、その後は陰謀や策謀に費やす時間なんてなくなるぞ。 今言ったことを全部、その「ミネール総督」に伝えろ。これが冗談や口先だけの約束じゃないことも忘れるな。 俺の我慢はもう限界だ、だからしっかり理解しろよ。わかったか、役人！？";
			link.l1 = "「すべて完璧に理解しました、Colonel。」";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "よし。ならば出て行け。この件について考える時間をちょうど一日やろう。\n二十四時間後にピーター・スタイフェサントが今のお前のようにここに立っていなければ、それはすべて奴自身の責任だ。 ";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "あの薄汚い犬のスタイフェサントはここに来ると思うぜ。もし来なけりゃ、自業自得ってやつだ！";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "砦の件はよくやったな、ド・モール旦那。これからは陸路で城門に近づくぞ。ここからは俺が大砲を運ぶ。 道が短くて楽だからな。お前はサンタ・マリア岬で海兵隊を上陸させて、ウィレムスタッドへ進軍しろ。 途中で敵に遭遇したら、どうすればいいか分かっているだろう。背後に誰一人残すな。";
			link.l1 = "もちろんでございます、大佐。門でお待ちしております！";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "さて、どうやら我々の任務は見事に成功したようだな。おめでとう、船長！いや、失礼、副提督！さあ、船に戻ろう。 俺の部下には警戒態勢を取らせておくぜ――あの愚か者スタイフェサントも撤退中に攻撃してくる度胸はないだろうが、用心するに越したことはねえからな。";
			link.l1 = "オランダ人が今しがた結ばれた条約を破るなんて、きっとしないはずだ。";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "ご一緒に仕事ができて光栄でした、de Maure旦那。\nまたポート・ロイヤルかキャップスターヴィルでお会いすることになるでしょう。";
			link.l1 = "間違いありません、大佐。さて、部下たちに撤退を命じましょう。";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "どうやらオランダ野郎どもは、砲火の下であの狭い道を砦から俺たちに近づく手立てがねえって、 ようやく気づいたらしいな。街に閉じ込められてる連中も、よっぽどの阿呆じゃなきゃ突撃なんざしねえだろう。さて、 ちょいとパニックを撒いてやるか。大砲で街を砲撃するぞ。俺の船の連中もそれを見て、 上陸の準備をしてるふうに見せかけるんだ。一、二時間もすりゃ、スタイフェサントの野郎もズボンを汚して、 停戦の使者を寄越す気になるだろうさ。";
			link.l1 = "全て我々の計画通りですよ、大佐！やりましょう！";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "交渉を始めるためにここへ来た。要求は何だ？";
			link.l1 = "我々は会社の代表であるピーター・スタイフェサントとの面会を要求する。\n特に、彼の会社の怠慢、そして彼自身の怠慢によって、 現在ウィレムスタッドが壊滅の危機に瀕しているという事実について話し合いたい。";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "承知した、スタイフェサント旦那にこの件を伝えて、あなた方の使節団が市内へ安全に入れるよう手配しよう…";
			link.l1 = "「安全な脱出はどうするんだ？」";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "俺にはわからねえ、旦那？";
			link.l1 = "俺が言ったのはこうだ：俺たちのために安全に街から出られるよう手配してくれるか？それについては自信がない。 スタイフェサント旦那が使者たちを捕らえると決めてしまうかもしれないのが心配なんだ。だからこそ、 交渉のためにスタイフェサント旦那をここに招待する。";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "しかし……";
			link.l1 = "士官、ここでは俺たちが条件を決めるんだ。お前の艦隊は壊滅し、守備隊は町から孤立している。 俺たちが本気で攻め込めば、ウィレムスタッドの防御なんざフリゲート艦が小舟を突き破るように突破できるぜ。さて、 これからスタイフェサント旦那宛ての書状を渡すから、俺たちからの招待状と一緒に必ず届けてもらうぞ…";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "それで、船長、要求を突きつけたくて休戦の使者を呼んだのか？";
			link.l1 = "まったくその通りだ、旦那。簡単に俺がトリニダードに来た理由を説明しよう――これはお前が最近サン・ピエールを襲撃したことへの我々からの返答だ。お前は町に大きな損害を与えた、その償いを今、 強制的にさせてもらう。賠償金は三十万ペソだ。それも、 マルティニークでお前の兵士どもがやった卑劣な行為を考えれば、決して高くはねえぞ。";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "失礼ですが、旦那、サンホセとサン・ピエールに何の関係があるんです？なぜ我々の植民地が支払わなきゃならないんだ？ ";
			link.l1 = "攻撃者はオランダ人やイギリス人ではなく、スペイン人だったからだ。だから、 請求書はドン・デ・メンドーサ宛てにプロビデンスへ送り、私の心からのご挨拶も添えてくれ。 ご理解いただけると思うが、もし賠償金の支払いを拒否するなら、俺の部下に上陸を命じるつもりだ。その場合、 サン・ホセはもっと大きな損失を被ることになるだろう。君たちの植民地の総督なら、 きっと正しい判断をしてくれるはずだ。返答は一日以内に頼む。ご多幸を祈るぜ、旦那方。";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "つまり、俺の理解では、総督は正しい決断を下したってことか？";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "三十万持ってさっさと俺たちの植民地から出て行け。";
			link.l1 = "素晴らしい、旦那たち。断言しますが、これが最善の方法でした。これでドン・デ・メンドーサや他の者たちが我々 の植民地を攻撃するのを思いとどまってくれることを願っています。 プロビデンスと彼本人にも必ず伝言を送るのを忘れないでください。ご健闘を祈ります、諸君。";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "シャルル・ド・モール船長、報告させていただきます。\nシュヴァリエ・フィリップ・ド・ポワンシーが、バロン・ノエル・フォルジェがサン・マルタンへの出発準備が整い、 桟橋であなたをお待ちしているとお伝えしたいとのことです。";
			link.l1 = "素晴らしい！ありがとうございます、旦那。";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "シャルル・ド・モール船長！ただいま総督閣下がお呼びです。サン・クリストファー沖に手強い敵艦隊が現れました！";
			link.l1 = "それじゃあ、時間を無駄にせず行こうぜ！";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "お前は誰だ？ここで何してるんだ？";
			link.l1 = "ううっ…";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "ここは部外者立入禁止だ！お前ら、何者だ、間者か？司令官の執務室まで連れていくぞ、そこで裁いてもらうからな。";
			link.l1 = "しかし、司令官の執務室には行けないんだ……";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "自分で行かねえなら、力ずくで引きずってやるしかねえな！武器を渡せ！";
			link.l1 = "取引はなしだ……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "それで、全部わかったか？";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "はい、旦那。手紙はミニール・ピーター・スタイフェサントかマティアス・ベック本人に直接渡すようにとのことです。";
			link.l1 = "ウィレムスタッドからカルタヘナ行きの船を見つけるのは難しくないはずだ。 旅費と宿代に必要な資金はすべて渡してある。\nそれと、もし必要になった場合――六か月後のフランス委員会の前に報告内容を確認してくれるか？";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "旦那、私は約束を守る男です。";
			link.l1 = "よし、わかった。それじゃあ幸運を祈るぜ。この道はウィレムスタッドへ続いてる、ついて来な。 ここからそう遠くねえぞ。";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "シャルル・ド・モール副提督、だろ？";
			link.l1 = "その通りだ。さて、どちら様とお話しできる光栄にあずかっているのかな？";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "バロン・ノエル・フォルジェからあなたへの伝言だ。できるだけ早くカスターヴィルの総督宮殿に来るようにとのことだ。 ";
			link.l1 = "おお！素晴らしい知らせだ！ありがとう、すぐに出発するぞ！";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "ごきげんよう、副提督殿。フォルジェ男爵からあなたのことをいろいろと聞いております。たくさんの話を伺いました。 植民地におけるフランスのための忠実かつ見事なご奉仕、そして詐欺師ド・ポワンシィの陰謀を暴くご協力に、 心より感謝申し上げます。これからは財務大臣と私が彼に直接対処いたしますので、 あなたには以前の上官の地位についていただきます。少なくとも、しばらくの間は。";
			link.l1 = "しかし…";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "「言い訳は無用だ、副提督！この決定はすでに下され、国王陛下の承認も得ている。ここに、 陛下自ら署名した命令書がある。これにより、貴殿はアルキペラゴにおけるフランス植民地の事実上の総督に任命された。 この役職にふさわしい候補は他にいない。貴殿の卓越した戦争経験、この地域やここの責任者たちに関する知識、 そしてその技能と才能、いずれもこの高く尊敬される地位にふさわしいものだ。率直に申し上げれば、いずれ『事実上』 という言葉抜きで再びこの職に正式に任命されることを私は期待している。」";
			link.l1 = "でも、俺はパリに戻る夢を見てたんだ……";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "フランスはここであなたを必要としている！今まさに財務大臣がヨーロッパで海軍を編成中だし、我々 がこの諸島にいることも見過ごされはしない。あなたの主な任務は、植民地を強化・要塞化し、 艦隊の軍事力を高めることだ。フォルジェ男爵とフランス西インド会社は貿易と内政の発展に専念する！そして、 フランス海軍の準備を手伝えるのは、他でもないあなたしかいないだろう？\nさあ、仕事に取りかかってくれ、総督閣下！一日中部屋にいるのは好きじゃないのは知っているが、 今回の任務はそれすら必要ないのだ！";
			link.l1 = "かしこまりました、閣下！命令には逆らえません！";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "私の言いたいことを正しく理解してくれて嬉しいよ。 ついでにシュヴァリエ・ド・ポワンシーにも会いに行ってくれないか？ 彼がどうしても君に会いたいと強く望んでいたんだ。彼がパリへ発つ前に、その楽しみを奪うわけにはいかないだろう？ 彼は牢獄にいるから、そこで会えるよ。";
			link.l1 = "かしこまりました、閣下……";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "…作業が止まっちまうんだ、わかるだろう？この資材は数か月前に注文したんだぞ！";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "「それで、最初の船に何を積んで、二番目の船に何を積むか、どうやって決めたっていうの！？ あたしは田舎の仕立て屋なんかじゃないんだよ――総督閣下シュヴァリエ・ド・ポワンシー殿からの命令書まで持ってるんだからね！」";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "さて、今さら他に何ができるってんだ……待つしかねえよ。だがな、これだけは覚えとけ。未達の命令については俺は責任取らねえからな！";
			link.l1 = "挨拶だ。どうやら面倒ごとに巻き込まれてるようだな？";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "「トラブル？それどころじゃねえぜ！ああ、見覚えがあるな……お前が新しい副提督だろ？」";
			link.l1 = "飲み込みが早いな。その通り、今お前の前に立っているのはフランス植民地で二番目の地位にある男、 フランス艦隊の副提督、シャルル・ド・モールだ。";
			link.l1.go = "Tailor_06";
			link.l2 = "堅苦しい挨拶はやめてくれ、ここは船の上じゃないんだ。\nそれに心配するな、俺のことをすぐに気づかなかったからって衛兵を呼んだりしないさ。\nただ「シャルル・ド・モール」と呼んでくれ。";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "閣下、すぐにお見受けできず申し訳ございません！はい、おっしゃる通りで、予期せぬ事態に遭遇いたしました。";
			link.l1 = "「それはどんな事情なんだ？俺の理解では、パリからは何の資材も持ってこなかったんじゃねえか？」";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "ああ、どうもありがとうございます。おっしゃる通り、思いがけない事態に遭遇していたので、 目の前に誰がいるのかすぐには気づきませんでした。";
			link.l1 = "「それはどんな事情なんだ？俺の理解では、パリからお前に何の物資も届けられていないんじゃねえか？」";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "はい、その通りです。数か月前に私が注文しました。当時、総督があなたの任命の命令書に署名し、 首都で承認されると確信して新しい提督の制服に必要なすべての材料を用意するよう私に強く指示したのです。";
			link.l1 = "「それで、資材は届けられなかったんだろうな？」";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "考えてみてくれよ！どれだけ重要か説明して、ちゃんと注文も出したのに……あいつらはもっと急ぎの荷物があるんだとさ！俺はどうすりゃいいんだ？一年も前から注文して、 やっと材料を持ってきてくれるのを祈るしかないのか？";
			link.l1 = "具体的に何が足りないんだ？もしかしたらカリブで見つかるかもしれねえぞ？";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "たとえ可能だとしても、どこにあるか全く見当がつかない……ここじゃいい素材は手に入らねえよ。\nただ……もし許してくれるなら、お前の古い士官の上着を土台に使えるぜ。提督の制服を手に入れたら、 もうその上着はいらねえだろ？";
			link.l1 = "もし俺が提督の制服を持っているなら、もちろん普通の士官の上着なんて必要ねえさ。他には何がある？";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "制服用のカフスボタンとカラーを探さなくてはならない。\n普段はパリの工房に直接注文しているんだ。\nたとえごく普通のものでも、私が手を加えればもっと見栄え良くできる。\nただ、その場合は数がもっと必要になるな……";
			link.l1 = "カリブにはパリの仕立屋がないから、代わりに現地の服をまとめて用意してやるよ、襟や袖が取り外せるやつだ。 他に何かいるか？";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "仕上げのためには、非常に高品質な布地が必要なんだ。俺には粗い繊維からでもそんな布を作れる紡ぎ手がいる。だが、 そのためには材料――できれば綿が欲しい。一梱包あれば十分すぎるほどだ。";
			link.l1 = "それも手配できるぜ。次はどうする？";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "パリから提督用の三角帽を届けるはずだったんだが、材料さえあれば自分で作れるさ。\nお前のための三角帽は本来布製の予定だったが、カリブの塩風と灼熱の太陽には革の方がいいぜ。\nその方が長持ちするからな。";
			link.l1 = "革は俺が用意してやる、心配すんな。エスパニョーラのジャングルで雄牛を追い回す必要もねえさ。それだけでいいのか？ ";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "リヨンから最高級の絹も届けるはずだったんだ。\n軽くて通気性がよく、湿気をすぐ吸ってさらに早く乾く。\nそして何より、伸びたりせず形を保つんだぜ。";
			link.l1 = "ああ、どの絹のことか分かってるぜ。だが、植民地じゃ手に入れるのは難しいかもしれねえな。";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "材料はこれで全部だ。それから、フランスの最高勲章を授与されたと聞いたぞ……サン・ルイ勲章は、腰にぶら下げるような飾りじゃねえ。本来の場所があるんだ。だから、 それを俺のところに持ってきてくれ。ちゃんと縫い付けてやるからよ。";
			link.l1 = "わかった、俺もそれを持っていくぜ。絶対に無くすんじゃねえぞ！";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "とんでもねえ！命をかけて守るぜ！";
			link.l1 = "よし、それだけなら、材料を取りに行くぜ。";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "もう一つお願いがあるんだ……仕立て道具が使い物にならなくなってしまってね。パリに新しい道具を注文したんだが、残念ながら……もし必要な材料を全部集めて、道具を貸してくれるなら――もし持っていたらでいい、貸してくれれば後で新しいのを手に入れるから！――すぐにでも縫い始めるよ。";
			link.l1 = "さて、どうしようか？必要なものは全部持ってきてやるよ。どこで会えばいい？ まさか港役所で待ってるわけじゃねえだろうな？";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "俺の工房は桟橋のすぐそばの建物にある――上陸したら右手に見えるぜ。";
			link.l1 = "取引成立だ。材料を用意してやる。";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "ごきげんよう、副提督！新しい制服に必要なものはすべてお持ちになりましたか？";
			link.l1 = "まだだ、時間がなかったんだ。待ってろ、全部用意するぜ。";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "ああ、全部持ってきたぜ。これが俺の古い上着、勲章、それと仕立て道具だ。\n残りの材料は、俺の船乗りたちがすぐにお前の工房へ運ぶからな。";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "素晴らしい！正直なところ、君がこれを全部手に入れられるとは思っていなかったよ。 私はいつもパリの布地しか扱っていないが、どうやら地元の素材でもなかなか立派な服が作れるようだな。";
			link.l1 = "俺の新しい制服ができるまで、あとどれくらいかかるんだ？";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "通常なら最低でも一週間はかかるが、依頼主が植民地のフランスで最も高位の二人の役人だということを考えれば……三日後にまた来てくれ、最高の仕上がりを約束するぜ！採寸は必要ねえ、あんたの古い上着を元に全部仕立ててやるよ。";
			link.l1 = "よし！じゃあ三日後に戻ってくるぜ。";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "副提督！お会いできて光栄です！";
				link.l1 = "さて、約束通り新しい制服を受け取りに来たぜ。";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "ごきげんよう、副提督！申し訳ありませんが、制服はまだ準備できておりません。";
				link.l1 = "「なあ、せめてちょっとだけ様子を覗いてもいいか？」";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "いや、いや！今は全然見せられる状態じゃないんだ、君の期待を裏切りたくないからね。どうかもう少し待ってくれ。";
			link.l1 = "わかった、待ってるぜ。";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "はい、もちろんです！正直に言いますと、出来栄えはパリで作ったものにも劣りませんでしたよ！あなたの言う通り、 植民地でも探し方さえ分かれば、ちゃんとした素材が見つかるものですね。\n少々お待ちください。はい、こちらです！どうぞ、ご確認の上、お試しください。";
			link.l1 = "ありがとうございます。素晴らしい品質ですね！しかも、ぴったり合います。";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "上出来どころじゃねえ！これを植民地のフランス副提督として誇りを持って身につけられるぜ！それに、 約束通りお前の勲章も今や本来あるべき場所にある、もう腰からぶら下げてるだけじゃねえぞ。";
			link.l1 = "よくやった！シュヴァリエ・ド・ポワンシーに会ったら、私が満足していると伝えてくれ。";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "必ず伝えます！その制服が役に立ちますように！幸運を祈ります！";
			link.l1 = "ありがとうございます！さようなら。";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "どの剣を強化したいんだ？";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetItemName(rItem) + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "考えが変わった";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
