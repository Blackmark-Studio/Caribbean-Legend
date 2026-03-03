// диалоги НПС по квесту 'В поисках Стража Истины'
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "どうなさいましたか？お手伝いできることはありますか？";
			link.l1 = "すみません、なんでもありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "何の用だ？また尋問か？くたばれ！\n";
			link.l1 = "旦那、お名前は？";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "お前がこれから絞首刑にするか撃ち殺す男の名前なんて、いったい何が気になるんだ？バスタードめ！結局、 俺はうっかりお前らの手に落ちちまったんだな…";
			link.l1 = "旦那、名乗ってください。名前も知らずに話すわけにはいきません。";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+"。これで満足か？さて、俺は誰と話してるんだ？";
			link.l1 = "私の名前は "+GetFullName(pchar)+"……俺のこと、聞いたことあるか？";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "いや、カラホ！俺が西インド諸島をうろつく浮浪者どもを全員知ってるように見えるかよ…";
			link.l1 = "もういい。侮辱はやめて、紳士らしく振る舞おうじゃないか。\n君の運命は、君が私に話せること次第だ。\nもし面白い話をしてくれたら、私の監督下での釈放を嘆願してやろう。\nそうすれば、今まさに待ち受けている銃弾や絞首刑から逃れられるぞ。";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "ディオス・ミオ、それは断れない申し出だ。何を知りたいんだ、旦那？";
			link.l1 = "誰がこれほど大規模なサン・ピエールへの攻撃を仕組んだんだ、そしてなぜだ？";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "プロビデンス島の守備隊長、ラモン・デ・メンドーサ・イ・リバ男爵だ。彼は分遣隊を送り込み、町を襲撃して略奪し、 見つけた貴重品をすべて押収した。";
			link.l1 = "襲撃の際、君の直近の任務は何だった？\n具体的に、どんな命令を受けていたんだ？";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "私は海兵大隊の指揮官だ。我々の命令は、上陸艇が町に近づく際に砲撃されないよう、 要塞を制圧し砲台を確保することだった。その後、私の部下たちはサン・ピエール自体への攻撃にも参加した。";
			link.l1 = "町にある貴重品について知らされていたのか？その量や質についてもか？";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "正確な量については分かりませんでしたが、メンドーサ・イ・リバ男爵が、要塞の地下には銀が保管されており、 港の倉庫には戦争遂行に不可欠な戦略的原材料――鉄木や船用の絹――があると教えてくれました。\n";
			link.l1 = "あの貴重品を見つけたか？";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "いいえ、どちらも見つかりませんでした。倉庫にはありふれた植民地の品物が詰まっていて、砦の地下には火薬や武器、 鉛がありました。しかし、もっと徹底的に捜索する時間が足りなかったのです……フランスの援軍が怒涛の勢いで押し寄せてきて、戦わざるを得ませんでした。";
			link.l1 = "貴重品が見つからなかったこと、不思議に思わなかったのか？";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "もちろんやったさ、でも俺は普段、命令にいちいち疑問を持ったりしねえよ。";
			link.l1 = "これから話すことをよく聞け。サン・ピエール砦には銀なんて一度もなかったし、 あの倉庫に鉄木や絹が保管されたこともない。よく考えてから答えるんだ、旦那。もしお前の答えが気に入らなければ、 俺は踵を返してここを出ていくぞ……お前を運命に任せてな……悲惨な運命にな。";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "聞いている。";
			link.l1 = "お前たちの襲撃の目的が単なる略奪だけだったとは思えん。サン・ピエールは目立たず、比較的貧しい植民地だ。 そんな場所に一等戦列艦率いる艦隊全体を送る理由があるはずがない。お前やお前の上官、あるいは他の誰かが、 他にも命令や指示を受けていたのではないか。何を言われていた？よく考えてから答えろ…";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "黙るつもりか？\nいいだろう。少し考えてみろ、待っててやる。";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "旦那、私の返答次第で命が左右されるのですか？";
			link.l1 = "「その通り。」";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "俺にはちょっとした情報がある……だが、ここから出してスペインに身代金で戻してくれると誓ってくれなきゃ話さねえぞ。";
			link.l1 = "もし俺の興味を引く話をしてくれたら、聖十字架に誓って、お前を身代金目的で俺の船に乗せてやる。 処刑は免除してやるぜ。";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "わかった。ドン・ディエゴ・デ・モントヤが我々海兵隊に極秘かつ至急で、 サン・ピエールのどこかにいて当局の保護下にあるミゲル・ディチョーソという男を探し出し、捕らえるよう命じたんだ。 ";
			link.l1 = "続けてくれ。ディエゴ・デ・モントーヤとは誰だ？";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "艦隊を指揮していた士官だ。お前の…劇的な登場のすぐ後に逃げ出したぞ。";
			link.l1 = "「彼は誰だ、ドン・ディエゴってやつは？」";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "私が知っているのは、彼がメンドーサ・イ・リバ男爵の公認代理人であり、 男爵の右腕として重要な任務を任されている人物だということだけです。";
			link.l1 = "面白いな……で、そのミゲル・ディチョソってのは誰だ？この大騒動が全部そいつを捕まえるために仕組まれたってわけか？ よっぽどの悪党なんだろうな、え？";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "「お前の誓いを覚えているか、旦那？」";
			link.l1 = "ああ。だがな、お前が話を続けるなら、証人として俺の船に連れて行くことを約束するぜ。そんで……後でスペインの植民地に送り届ける方法も考えてやるさ。だが、その前に知っていることを全部話してもらうぞ。";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "ミゲル・ディチョソは男爵のかつての戦友だが、ミゲルが裏切ったという噂もある。\nメンドーサ・イ・リバ旦那は彼を生かしておきたいそうで、どんな状況でもディチョソを殺すなと命じられている。";
			link.l1 = "「ディチョソもスペイン人なのか？」";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "ああ。ドン・ディエゴ・デ・モントヤが大まかな特徴を教えてくれて、 ディチョーソに似た者がいればすぐに彼のもとへ連れて来いと命じられた。だが、お前たちの反撃まで時間がなさすぎて、 捜索する暇はなかったんだ。";
			link.l1 = "「ディチョソと個人的に知り合いだったのか？」";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "いいえ、噂でしか知りません。その男には一度も会ったことがありません。 私の同僚の士官の中には彼と面識があった者もいましたが、全員もう死んでいます。";
			link.l1 = "ディチョソはどれほどひどくメンドーサ旦那を裏切ったんだ？旦那がわざわざ艦隊まるごと差し向けるほどとはな。";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "話してやろう。バロンはつい最近スペインからカリブ海にやって来たばかりだ。 命令はスペイン財宝艦隊の護衛を確実にすることだったが、奴は内陸に目を向けてしまった……インディオの黄金を探しに。隠された財宝の噂に心を奪われたのさ。 ユカタンの密林の奥深くに古代マヤの都市が存在すると信じ込んだ――伝説の黄金都市、タヤサルだ\nバロンはその都市を探すためにいくつもの探検隊を送り込んだが、全て野生のセルバで完全に壊滅した。間違いなく、 そこに住む武闘派のイツァ族によって皆殺しにされたのだろう\nやがて、ヴィンチェント異端審問官もドン・メンドーサの妄想と無駄死にする兵士たちに我慢できなくなった。 異端審問官はマドリードに状況を報告した。副王はドン・メンドーサに伝説の都市の捜索を禁じ、 本来の任務に集中するよう命じた。その時、ミゲル・ディチョーソが現れたのさ\n彼はバロンを説得して、もう一度探検隊を組織させた――驚いたことに、今度は成功した。古代都市の遺跡と宝石で飾られた金塊を発見したのだ。だが帰路、 モスキート族に襲撃された\nミゲル以外は全滅した；インディオの吹き矢には現地の毒が塗られていて、 かすり傷でも数日で激しい苦しみの末に必ず死ぬ。ディチョーソは持ち運べるだけの財宝を持ってプロビデンスに戻った\nカラホ！バロンは言葉にできないほど喜び、マドリードとサンティアゴのヴィンチェント神父に緊急の書簡を送った； きっと自分の成功を神父に見せつけたかったのだろう。そして財宝をスペインに運ぶためのフリゲート艦が用意された。 ディチョーソはその護衛を自ら申し出たのさ。";
			link.l1 = "当ててみようか。奴は金を届けなかったんだろう？";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "その通りだ、旦那！フリゲート艦は積荷も乗組員も、ディチョーソもろとも跡形もなく消えちまった。男爵は激怒したぜ。 エスコリアルの面前でまたもや恥をかかされ、ヴィンチェント神父はさぞかし満足だったろうよ。今やメンドーサ旦那は、 傷ついた誇りと失われた財宝、そしてミゲル・ディチョーソを取り戻すことに取り憑かれている男さ。";
			link.l1 = "フリゲート艦がただ嵐に巻き込まれて沈没しただけ、あるいは海賊に拿捕された可能性はないのか？\n";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "バロンはその場の勢いで、ディチョーソが自分を裏切ったと確信していると誓った。詳しいことは私も知らない。\n数週間後、ドン・ディエゴ・デ・モントーヤが新たな情報を持ってやってきて、 ミゲル・ディチョーソがサン・ピエールにいるかもしれないと言った。";
			link.l1 = "ふむ。面白いな。またあのインディアンの財宝か。どうも全てが怪しくそれに結びついているようだな……で、ディチョソは見つからなかったのか？";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "いいや。正直なところ、あいつがここに来たことがあるなら驚きだな。 バロンはディチョソを捕まえることに取り憑かれていて、どんな荒唐無稽な話でも信じちまうんだ。";
			link.l1 = "「教えてくれ、 "+npchar.name+"「で、どうやってドン・メンドーサはこの……ええと……タイアサルの都市のことを知ったんだ？夢で見たわけじゃねえだろうな？何か証拠とか他に手がかりでもあったのか？」";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "最初にテヤサルと黄金都市の存在を聞きつけたのはヴィンチェント神父だった。どこでその話を知ったのか、 私には全く見当もつかない……";
			link.l1 = "それは面白い展開だな。ヴィンチェント神父はタイアサルの存在について自分で理論を立て、スペインにも自ら知らせて、 男爵の計画に横槍を入れ始めたってわけか……";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "同じカトリック信者として、聖なる審問会の神父たちがどう動くかは分かるだろう…やつがマドリードに報告したのも、何か企みがあるからに違いない。ただ、男爵の到着はどうやら想定外だったようだ。 とにかく、それ以上のことは俺には分からない。異端審問官と関わりたいと思ったことなんて一度もないからな。";
			link.l1 = "「よし。面白い話をたくさん聞かせてくれたな。」 "+npchar.name+"……そして誓い通り、お前をここから連れ出す。後でまた迎えに来るが、今は……お前が話したことについて少し考えさせてくれ……";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "旦那？約束を守ってくれるのか？";
			link.l1 = "私はいつも約束を守るんだ。今日はお前の運がいい日だぜ、\n "+npchar.name+"。お前は俺と一緒にキューバのサンティアゴへ行くんだ。詳しい話は着いてから教えてやる。今は、 とにかく乗船を歓迎するぜ。港まで護衛されて、俺の船に連れて行かれるからな。";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "感謝します、船長。約束を守る紳士でいてくれて嬉しいです。";
			link.l1 = "感謝の言葉は後でいい。お前は俺の客人だが、監視付きだぜ。誤解するな、まだお前が必要なんだ。";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "分かりました、旦那。スペイン士官として誓います、逃げ出そうとは決してしません。";
			link.l1 = "用心深い者には神の加護がある。船で会おう。";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "船長、ここキューバで一体何をするつもりですか？\n私を降ろしに来たのですか？\nそんなこと、まさかと思いますが……";
			link.l1 = "まさにその通りだ。俺はお前を仲間の元へ送り返しに来たんだ。だが、ここに来た理由はそれだけじゃなくて、 もう少し複雑なんだよ。もっとも、それはもうお前には関係ない話だ。今すぐ身代金なしで解放してやる。ただし、 俺に二つの誓いを立てることが条件だ。";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "それは何だ？";
			link.l1 = "第一に、封印された手紙を君に渡す。その手紙をサンティアゴの異端審問官、ヴィンチェント神父に直接届けてくれ。\nもし彼が誰からの手紙か、どうやって手に入れたのか尋ねたら、正直に答えるんだ…";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "二つ目は、少なくとも一週間の間、私を探したり私の船を攻撃しようとする試みに手を貸したり助けたりしないことだ。\n同意するか？";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "「それだけか？」";
			link.l1 = "ああ、それだけだ。私の条件を満たせば、自由に行ってよい。";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "旦那、誓います、必ず自分の手でビンセント神父に手紙を届けますし、 サンティアゴ守備隊があなたやあなたの船に敵対するような行動は一切取りません。\nどうかご安心ください、約束は守ります。私はスペイン人であり、強く高貴な敵を敬う者です。";
			link.l1 = "わかったぜ、旦那 "+GetFullName(npchar)+"、お前の誓いを受け入れ、今すぐ解放してやる。ほら、この手紙を異端審問官に渡せ。これで自由の身だ。";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "さらばだ、旦那。二度と戦場でお会いすることがありませんように。そうなれば、私はひどく悲しみます。";
			link.l1 = "さらば……";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "ディオス・ミオ、なんて幸運な出会いだ！こんにちは、旦那 "+GetFullName(pchar)+"！サンティアゴではすっかり歓迎される客人になったようだな。聖なる異端審問所のために働いているのか？";
			link.l1 = "ごきげんよう、旦那 "+npchar.name+"。もう二度と会えないと思っていたよ、少なくとも友好的な状況ではね！いや、 ちょっとヴィンチェント神父に会いに立ち寄っただけさ。君はどうなんだ？今はサンティアゴで働いているのか？";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "あなたが私を逮捕から解放してくれた後、私はサンティアゴに留まらざるを得なかった。 プロビデンスに戻るのは危険なんだ……だが、ご覧の通り、約束は守ったよ。君を追いかけるスペイン船は一隻もいない……";
			link.l1 = "我々が共に約束を守る男であることを嬉しく思う。";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "聞いてくれ、船長、いわば俺たちの再会を祝ってラム酒で一杯やらねえか？ フランス野郎にこんなことを頼む日が来るとは思わなかったが、あんた、旦那は別格だぜ。";
			link.l1 = "もちろんだ！ちょっとラムで口をすすぐのも悪くねえな。酒場へ行こうぜ。";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "ああ、サルー！";
			link.l1 = "「何に乾杯するんだ、旦那役人？」";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "何か中立的だけど、俺たち二人に関係あることに乾杯しようじゃねえか。例えば、祖国への勇敢で見事な働きに！ みんな自分の国を持ってるからな！\n";
			link.l1 = "それから、我らの君主たちが互いに合意に達し、 フランス人とスペイン人が本国でもカリブでも争いをやめることにも乾杯しよう。";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "よく言ったな、船長！平和に乾杯だ！スペイン流の飲み方を見せてやるぜ！アリーバ、アバホ、アルセントロ、 イパデントロ！\n";
			link.l1 = "平和に……（乾杯）";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "ははっ！キューバ産のラムは本当にカリブで一番だな……";
			link.l1 = "同感だ。ところで、サン・ピエールで捕まったことで何か罰を受けそうになったか？";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "幸いにも、私は軽いお咎めだけで済んだんだ。あの災難はもう過去のことさ。結局、 この植民地じゃ士官が必要なんだからな。";
			link.l1 = "それで、お前の指揮官……名前は何だったか……ディエゴだろ？あの無駄な襲撃の結果、あいつはどうなったんだ？降格されたのか？";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "ああ、なんてことだ！我らが親愛なるディエゴ・デ・モントーヤは、 ドン・ラモン・デ・メンドーサ・イ・リバが後ろ盾についている限り、誰も手出しできねえよ。\nちなみに、ドン・ディエゴはつい昨日サンティアゴにいたぜ。サン・ホセから到着したんだ。";
			link.l1 = "そうかい？面白いな！道端で会わなくてよかったぜ。あの件、決闘で終わってたかもしれねえからな、ははっ！";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "今は"+pchar.name+"船長に構っている暇はドン・ディエゴにはない。今は命を賭けて決闘する余裕などないほど、 彼には大きな賭け事があるんだ。西インディアのメンドーサ男爵と何やら企みを立てているらしい。 ハバナで艦隊を編成して、いつでもスペインへ戻るつもりでいるぞ。\n";
			link.l1 = "お前もあいつの船員なのか？";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "いいや。明日にはプエルトリコのサンファン駐屯地へ発つんだ。ドン・メンドーサがいる限り、 もうプロビデンスには歓迎されないからな。";
			link.l1 = "では、お前の新しい任地に乾杯しよう。そこでは楽しい時と美しい娘たちだけが待っていることを願ってな。";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "ありがとうございます、旦那。あなたにもあらゆる幸運をお祈りします。\nさて、そろそろお暇いたしましょう。この酒を飲み干したら、失礼させていただきます。";
			link.l1 = "神のご加護を、旦那 "+npchar.name+"……また平和な時に会えるかもしれませんね。";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "言った通りだろう、ドン・ディエゴ。魚は餌に食いついたぜ、針も糸もオモリも全部な……\nおや、また会ったな、旦那。残念ながら、我々が望んだような平和な状況じゃないがな。";
			link.l1 = ""+npchar.name+"？ほう！これは予想外だな。なぜか君は正直で高潔な士官だと思っていたが、どうやら俺の勘違いだったようだ。";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "何を根拠に自分が正しいと思っているんだ？俺は約束を守ったし、お前に永遠の友情なんて誓っていない。 何も変わっちゃいないぜ、旦那。お前は今もスペインの敵であり、俺の個人的な敵だ。ここはサンティアゴじゃねえし、 ヴィンチェント神父もいない。あいつのちっぽけな通行証なんか、ここじゃ役に立たねえぞ……";
			link.l1 = "おや、そうかい？ラムを飲みながら親しげに会話しておいて、実は俺を罠にかけようとしてるなんて、 ずいぶんと卑怯だと思わねえか、旦那\n "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "俺を裏切り者呼ばわりするつもりか、このマリコン野郎！？";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "おい、そこのお前！そうだ、そうだ、お前だ！ "+GetFullName(pchar)+"?";
			link.l1 = "ああ、相棒。俺だ。";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "大事な人物から手紙を受け取った。もう誰かは分かっているだろう。";
			link.l1 = "分かってる、よこせ。";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "ほらよ。俺の手間賃に小銭をくれねえか？";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "少し銀貨を取っておけ。正々堂々と稼いだんだ。";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "俺にイカサマしようってのか、相棒？その配達の報酬はもう払ったはずだぜ。";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "ありがとう、坊や。気前のいい旦那と取引できて嬉しいぜ。";
			link.l1 = "よし、さっさと消えろ。ここで起きたことは一言もしゃべるんじゃねえぞ。";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "ハバナの狼はお前の友人だ…";
			link.l1 = "え？まだここにいるのか……";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "「アドミラーブル号」へようこそ、船長 "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"！驚いたな。俺のことを知ってるのか？";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "フランス植民地で"+pchar.name+"という偉大な船長の名を聞いたことがない者などいるか "+GetFullName(pchar)+"、サン・ピエールを攻撃した戦列艦率いるスペイン艦隊の歯を叩き折り、敵の襲撃部隊を全滅させたあの人だろう！ あんたは国の英雄だ！";
			link.l1 = "おいおい、「英雄」だなんて……俺はただフランスのために義務を果たしている兵士にすぎないさ。";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "あんたがやったことを、そんなに多くの兵士ができたとは思えねえよ、船長……ええと、本当は酒場でラムでも奢りてえんだが、残念ながら船長が乗組員にラムを一滴も飲むなって命じててな、 俺が悪い手本になるのはごめんだ……";
			link.l1 = "ふむ……つまり、お前自身は船長じゃねえのか？";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "俺が船長に見えるか？ほほっ！いや、俺はただの甲板長さ。名前はセルジュ・デガだ。うちの船長、 ガイウス・マルシェは一日中酒場に入り浸ってるし、俺たちはずっとここで「商人」 キャラバンを待ちながらゴロゴロしてる。船長は船員たちに給料を払ってないし、俺たちにもだ。乗組員全員、 すっからかんさ……。\n ";
			link.l1 = "どうした？スペインのバニラ・キャラバンが羽をむしられに来てねえのか？";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "とんでもねえ！うちの船長はこのガレオン船を手に入れてから海賊稼業をやめちまったんだ。聞いてくれよ、 ヨーロッパへ向かう交易隊がもうすぐグアドループに寄港するって話を聞いてな、そいつらがバニラを買うってんで、 ブリッジタウンで船倉いっぱいにバニラを詰め込んだのさ！一箱三百ペソで売れると思い込んでな――まったく、甘い考えだぜ！\nもちろん、着いてみりゃバニラの交易隊なんて影も形もねえし、地元の連中に売ろうとしたら大損だ。だからこうして『 商人』どもを待ってるってわけさ――まあ、いつかは来るだろうよ、三年後かもしれねえがな……船長は一日中酒場に入り浸って、王様気取りでみんなに迷惑かけてる。船に戻るのは酔いつぶれる時だけだ。で、 今じゃ損しないために二百ペソで売る覚悟ができたらしいぜ。\nありったけの金をその積荷につぎ込んじまった。いつか乗組員が船長を縛り上げて、 借金返済のためにバニラを安売りする日が来るだろうよ……マジで、もうすぐそんな日が来る気がしてならねえんだ。";
			link.l1 = "ああ…船長、何か悩みでもあるのか？";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "まあ、やるならきちんとやるべきだが、あいつはどっちもできてない。交渉も下手くそだ。 貨物の運送もしてれば話は違ったんだろうが、本人は本物の商人になったつもりでいたいらしい。 夜中にでも甲板から転げ落ちてくれればいいのにな…";
			link.l1 = "分かるよ、セルジュ。心配するな、きっといつか君の……キャラバンも現れるさ。";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "ああ、奇跡なんて信じちゃいねえよ、船長。いつかまた会ってラムでも飲めたらいいな……今すぐラムが飲めたら、どんなにいいか……";
			link.l1 = "幸運を祈るぜ、相棒。";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "ええ、船長、ラムを一口やりたいところだぜ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("おう！お前さん、商船の者じゃねえのか？違う？おっと、すまねえ。そりゃそうだよな……俺の勘違いだ。","今はそんな気分じゃないんだ、旦那。他の誰かに話しかけてくれ。","あっ、またお前か！？","「ゴホン……」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("気にすんなよ、相棒。そんなこともあるさ。","ラムをどうぞ、船長。少しは悩みも和らぐぜ…","緊張するなよ、相棒。体に悪いぜ。","わかった、わかった。もう行くよ。",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "ううっ…んん…なんだよ、これは一体……";
			link.l1 = "静かにしろ、相棒……音を立てるな……";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "えっ？なんだ？くそっ！";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "ああっ！誰だお前は？俺に何の用だ！？";
			link.l1 = "黙らねえと歯を叩き折るぞ、わかったか？この船を奪ったときに持ち去った聖なる器はどこだ？";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "何の船だって？何のことか全然わからない！これは俺の船だ！";
			link.l1 = "お前の船だと？つい最近まであれは「サンタ・マルガリータ」と呼ばれていて、スペインの旗の下を航海していたんだぞ……聞いているんだ、あの聖なる器はどこにある？金のモンストランス、ラズライトで飾られた十字架、そして金の香炉は？ どうしたんだ？まさか売り払ったんじゃないだろうな？";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "ああ神よ、耳を疑うぜ……お前、スペイン人か？いや、違う……フランス人じゃねえか！そりゃもっと悪い！あの卑劣なカスティーリャ野郎どもに魂を売ったのか！ 今どきフランス人の魂はいくらで売れるんだ？俺は何も教えねえぞ、この裏切り者め！その宝物は絶対に渡さねえからな！ ";
			link.l1 = "黙ってやがるな？それでいいさ。どうせここは尋問には向いてねえ場所だ……お前が騒がねえように口を塞いで、それから俺のロングボートに連れていくぜ……いずれ口を割らせてやる。俺はそう確信してるからな。";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "この裏切り者のスペイン野郎め！覚悟しろよ……";
			link.l1 = "黙れ、このろくでなし……俺のすぐ後ろについて来い。さもないとぶっ飛ばして、足を引きずって甲板を引き回してやるぞ。";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "「どうなさいました、旦那？」";
			link.l1 = "調子はどうだい、船長？何の用でバステールに来たんだ？俺の聞いたところじゃ、 あんたはオランダの旗の下で航海してるスペイン人だって話だが？";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "どうかしましたか、旦那？そう、私はスペイン人です。私の名前と船の種類を見ればすぐ分かるでしょうが、 ここにはちゃんと合法的に来ています。オランダ西インド会社の許可証も持っていますので……";
			link.l1 = "騒がないでくれ、旦那！実はあんたがスペイン人で本当に嬉しいんだ……さて、ここには輸入のためか、それとも輸出のためかい？";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "私はハバナから商品を持ってきて、現地の市場で売った。\n今は、空の船倉で帰るのを避けるために、儲かる貨物を待っているところだ。";
			link.l1 = "旦那、あんたに商売の話があるんだ！手伝ってくれりゃ、いい稼ぎになるぜ。どうだ、話を聞いてみるか？ところで、 あんたの名前は？";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "カルロス。カルロス・ゲバラ船長だ。で、あんたの提案は何だ？";
			link.l1 = "バニラの一括購入が必要で、それをキューバの「」という男に送らなければならない "+pchar.questTemp.Guardoftruth.LMname+"、サンティアゴ灯台の見張り番だ。しかし、重大な問題がある。まず第一に、 どの店にも俺が必要とする量のバニラがないんだ……";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "第二に、私はすぐにセントクリストファーへ発たねばならんし、どれだけ留守にするかわからんのだ。 日ごとに損をしているのがわかるか？まったく情けない話だ！";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "承知しました。残念ですね、旦那。世の中の金をすべて手に入れることはできませんからね。で、俺に何の用ですか？";
			link.l1 = "あそこを見ろ。あのガレオン船が見えるか？あいつは俺がどうしても欲しいバニラでぎっしりだ。\n問題は、そのガレオンの船長が、もうすぐここにスパイス・キャラバンが来て積荷を高く、 ほとんど一箱三百ペソで買ってくれるなんて馬鹿げた考えを持ってることだ。";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "ああ、最近は世間知らずの男が多いな。愚か者は金とすぐに縁が切れるものさ……";
			link.l1 = "世間知らずなのはまだしも、あいつは本当にただの馬鹿だ！俺がバニラを二百十ペソで買ってやるって言ったのによ、 ここじゃ店でも二百にもならねえのにさ。信じられるか？あいつ、俺に「どっか行け」って言いやがった！ 二百五十でしか売らねえってよ！";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "ははっ！なんて間抜けだ！";
			link.l1 = "そうだ！まさに俺があいつに言った通りだよ。もちろん怒られたけど……でもどうしてもバニラが必要なんだ！\nそこで提案なんだ、旦那。俺は商人じゃねえが、あんたは取引の達人だと思うぜ。それに、でっかい船倉もあるしな……";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "あの馬鹿をうまく言いくるめて貨物を売らせろ。俺が面と向かって侮辱しちまったから、もう俺には売らねえだろう。 箱ごとに二百十ペソ払うつもりだ。もし値段を下げさせたら、その差額はお前のものにしていい。そんで、 その見返りにお前の船をチャーターしてバニラをサンティアゴまで運んでもらうぞ。";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "その積荷のために、俺にいくら払うつもりだ？";
			link.l1 = "「いくら欲しいんだ？」";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "サンティアゴはかなり遠い……三万ペソだ。";
			link.l1 = "それは無理だぜ、アミーゴ。もう少し譲ってくれよ。";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "よし、どうせ俺の通り道だしな……二万五千だ、それ以下はまけねえぞ。";
			link.l1 = "それで構わない。ガレオン船の船長はガイウス・マルシェという名だ。あいつは一日中酒場でふてくされている。 君がうまく説得して、香辛料を手放させてくれるといいんだが。";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "俺はこれまでにもっと大馬鹿者と取引したことがあるぜ。誰が「キャラバンが法外な値段で商品を買う」 なんて噂を流してるか、全部詳しく話してやるさ。全部妄想だと納得させちまえば、あいつはきっと売るだろうよ、 間違いねえ。";
			link.l1 = "それで、取引成立か？";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "バニラと輸送費を払える現金があるなら、取引成立だ。\n魅力的なアイルランドのことわざにあるだろう、「金を見せろ」ってな。";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "ほら、見てみな。全部ここにあるぜ。";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "銀は俺の船にある。取ってきて、すぐ戻るぜ！";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "金は持ってきたか？";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "ほら、見てみな。全部そろってるぜ。";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "今すぐ持ってくるぜ！";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "素晴らしい！分別のある相手と取引するのは本当に楽しいね。また来てくれ\n "+sTemp+" 朝の十時までには。\nその頃には、我々の共通の友人ガイウスも正気に戻っていると思う。";
				link.l1 = "素晴らしい！また後で会おう！";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "素晴らしい！分別のある相手と取引するのは楽しいものだ。俺はこれから岸へ行く。三時間後に戻ってきてくれ。 その頃には、我々の共通の友人ガイウスも正気に戻っているだろう。";
				link.l1 = "よし！また後でな！";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "旦那、私の役目はよく覚えております。ご心配なく、あいつは手強いかもしれませんが、必ず落としてみせます。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "終わりました、旦那。あの哀れな男は、私がバニラを買いたいと言っただけで大喜びでしたよ。前金を数えている間、 彼の手は幸せで震えていました――いや、もしかしたらラム酒のせいかもしれませんが。税関の目を避けるため、 明日正午にキャプスタービーチで貨物を積み込みます\n貨物を積み次第、すぐにサンティアゴへ向けて出航します。灯台であなたの仲間に連絡し、 そこでバニラを引き渡して署名します。彼に伝えてほしいことはありますか？";
			link.l1 = "はい。これが手紙だ。取引は明日正午にキャプスタービーチで行うと言ったな？よし、 それなら岬の沖に錨を下ろして待つさ、何かあった時に島から離れていられるようにな。";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "俺を信じてくれ、旦那。俺は正直者だぜ。それに、あんたと揉める気なんてさらさらねえし、商人は信用が命だ。だが、 あんたが見張って確かめたいってんなら、俺は別に構わねえよ。";
			link.l1 = "感謝するぜ、旦那。明日は取引を見張っておくし、 あんたが出航したらすぐにセントクリストファーで自分の用事に取りかかるさ。";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "船長、ご安心ください。必ずあなたを失望させませんし、我々の取引の条件もすべて果たします。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("ひっく！ひゃっほー！やっと船長が俺たちに給料をくれたぜ！船長に三度の万歳だ！ひっく！","パイントで出てくるのか！？俺も一杯もらうぜ！","俺たちの財布がパンパンになって、女たちはそれ以上にふくよかでありますように！万歳！","そしてそこに横たわっていた、みんな立派な死人さ、ヒック！飲み屋の夜明けみたいによ。ヨーホーホー、ラム酒の瓶だ！ ","ヨーホーホー、ラム酒一本だ！");
			link.l1 = LinkRandPhrase("ああ、相棒。","もうラムは十分飲んだんじゃねえか？","酒と悪魔が他の連中をみんな地獄に送っちまった……");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "止まれ！誰だ！？警報だ！乗り込んできた奴らを撃退しろ！";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "ハッハッハ！お前もローリー・ザ・キャップの宝を狙いに来たのか？俺たちも探して探して探しまくったが、 どうしても見つからねえんだ。ここの間抜けどもが一人くらい滝の裏の崖まで泳いでみようと考えてくれりゃいいのによ！ ";
			link.l1 = "「お前はフォックス大佐の部下だろう？」";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "俺がシーフォックスと繋がりがあるかもしれねえ。お前が知る必要はねえし、意味もねえ。今は何も知る必要はねえんだ。 お前が俺の宝を見つけてくれた、そのことには今、でっけえ感謝をしなきゃならねえな…";
			link.l1 = "なるほどな。お前はシーフォックスじゃなくて、どちらかと言えば海の犬……いや、ジャッカルか。どっちが似合うと思う？";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "どうやら俺たちの中に博物学者がいるみてえだな、野郎ども。動物界の本物の専門家ってわけか！";
			link.l1 = "俺のサーベルの切れ味、試してみるか、ジャッカル野郎？";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+"、旦那。どうなさいましたか？";
			link.l1 = "こんにちは。あなたがベリンダ・デ・リベロ夫人ですか？";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "はい、私です。どなたとお話しできる光栄にあずかっておりますか？";
			link.l1 = "Captain "+GetFullName(pchar)+"、奥様。私のフランス姓に気後れなさらないでくださいませ。今はサンティアゴの高名なる異端審問官、 ヴィンチェント神父様からの任務を果たしている最中ですの。";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "「ほう、面白いな！聖裁判所やイエズス会には、身分も国籍も様々な大勢の人々が集まっていると聞いたことはあるが、 実際にそこで働く異国人と会うのは初めてだ。\nさて、旦那、私に何かご用かな？」";
			link.l1 = "あなたは神父様が非常に興味を持っている品をお持ちですね。\nそれは金の聖体顕示台――ウィレムスタッドの銀行家から最近手に入れたモンストランスです。";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "お前はずいぶん物知りだな、旦那。まあ、お前の雇い主を考えれば、驚くことじゃねえ。そうさ、 俺が聖体顕示台を買ったんだ。あんな貴重なものが、 盗品や質流れのガラクタと一緒に商人の店先で埃をかぶってるなんて、許せねえからな。";
			link.l1 = "モンストランスはお持ちですか、奥様？";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "はい。もともとは私たちの教区教会に寄贈するつもりでしたが、ここでいろいろなことがありまして……できませんでした……ああ、申し訳ありません……";
			link.l1 = "奥様、泣いておられるのですか？私の言葉があなたを悲しませてしまいましたか？もしそうなら、 どうかお許しくださいませ。";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "ああ、どうか旦那……話を元に戻しましょう。私の理解では、ヴィンチェント神父がこの聖体顕示台を必要としているのですね？ 私があなたにお渡ししましょうか？";
			link.l1 = "この貴重な聖杯はサンティアゴの大聖堂に納められるはずでしたが、下賤な海賊に奪われ、他のいくつかの聖なる品々 と一緒に高利貸しに売られてしまいました。\n私の務めは、盗まれた品々を本来あるべき場所に戻すことです。もちろん、あなたのご負担は全額お支払いします。";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "まあ、そんなことなさらないでください！このお金が私にとってそんなに大事だと思っていらっしゃるのですか？ この聖体顕示台は聖母教会のために購入したもので、正当な持ち主、 ましてやヴィンチェント神父に仕えるイエズス会の方にお渡しするのに、私は何のためらいもありません。でも、 私には他に深く悩んでいることがあるのです。どうか、教会に忠実な娘である私をお助けいただけませんか？";
			link.l1 = "あなたは貴婦人ですわ、奥様。何かお悩みでしょうか？私にできることはございますか？";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "「ああ、でも旦那……イエズス会の兄弟ご本人に助けを頼むなんて、とても恐れ多くてできませんよ。いつもとてもお忙しいですから……」";
			link.l1 = "もうやったじゃないか。どうしたんだ？";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "「私があなたに頼むことを、聖なる教会の代表として、誰にも絶対に知られないと約束できますか？」";
			link.l1 = "私は厳粛に誓います、セニョーラ。\nこれは告解の秘密ではありませんが、このことについて誰にも一言も漏らしません。";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "よろしい。あなたを信じます。私の親愛なる友人エステバン・ソサが困ったことになりました。旅の途中で盗賊に捕まり、 十万ペソの身代金を要求されています。私はそんな大金を持っておらず、 小遣いから何とか半分ほど集めることができただけです。この件で誰かに助けを求めることもできません。 もしそうすれば、やつらは彼を殺すと誓っているのですから\nそれに、私は親しい…友人の身を案じ、最悪の事態を恐れています。金を受け取ったら、口封じのためにすぐ殺してしまうかもしれません。 あなたなら、勇敢な船長であり、キリスト教徒であり、同志会の兄弟でもありますから、盗賊たちを説得して、 私の持っている金で手を打ち、彼に危害を加えないようにできるかもしれません…";
			link.l1 = "交換はいつ、どこで行われるんだ？";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "奴らの首領は「屠殺屋バーティ」という男だ。エステバンの身代金を毎晩、 夜十一時から真夜中までジャングルの洞窟入口で待っていると言っていた…";
			link.l1 = "それはやけに具体的な条件だな……";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "どうやら奴らは、俺に身代金をすぐに全額集めさせたかったらしく、誰にも助けを求めてほしくなかったみたいだ……でも、そんな大金どこにも見つからないし、俺には絶対無理だよ！";
			link.l1 = "泣かないでください、奥様。お助けできるよう努力いたします。イエズス会の兄弟が、 正しきキリスト教徒のご婦人を危険に晒したままにすることなど決してありません。";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "あなたを信じるしかない……だが船長、バーティ・ザ・ナッカーはこうも言っていたんだ。もし身代金を持ってくる者が一人で来なかったり、 私が衛兵に知らせたりしたら、可哀想なエステバンをすぐに殺すって！\n";
			link.l1 = "覚えておくよ。";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "ほら、これを持っていってくれ。五万ペソ、何とかかき集めた金だ。せめてこれだけでも受け取るよう、 あの野郎どもを説得してくれ。もう一ペソたりとも残っていないと伝えてくれ！エステバンを連れ戻してくれ！ そうしてくれたら、喜んでヴィンチェント神父に聖体顕示台を渡すよ。";
			link.l1 = "できる限りのことはいたします、奥様。\nうまくいくことを願いましょう。";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "神のご加護がありますように、勇敢な船長！あなたのために祈ります！";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "何か知らせはあるか、船長？";
			link.l1 = "まだだ。待っててくれ、旦那。必ず期待に応えるよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "何か知らせはあるか、船長？";
			link.l1 = "はい、奥様。残念ながら良い知らせではありません。";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "教えてくれ、待たせるなよ！盗賊たちに会ったのか？";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "ほら、五万を返すよ。必要なかったんだ。それと、この指輪も受け取ってくれ。見覚えがあるはずだ。";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "ほら、この指輪を受け取ってくれ。見覚えがあるはずだ。";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "それは…ああ、確かに覚えがある。エステバンはどうなった？";
			link.l1 = "あなたに言われた通り、洞窟で盗賊たちを見つけた。\n「屠殺人バーティ」とエステバン・ソサは同一人物だった。\n彼はあなたを脅すために誘拐事件をでっち上げたんだ。\nそれから、あなたとの…関係についても話してくれた。\nもうあなたには会いたくないとも言っていた。\n証拠として、あなたが彼に渡した指輪を預かってきた。";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "これ…ああ、そうだ、知っている。エステバンに何があったんだ？";
			link.l1 = "あなたの言った通り、洞窟で盗賊たちを見つけた。\n奴らは俺を襲い、縛り上げて、あんたの金を奪った。\n「バーティ・ザ・ナッカー」とエステバン・ソサは同一人物だった。\n奴は身代金目当てに誘拐劇を仕組んだんだ。\nそれから、あんたとの…関係についても話してくれた。\nエステバンは俺を解放し、この指輪を証拠として渡してくれた。\nもう二度と彼には会えないだろう、と言っていた。";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "ディオス・ミオ！信じられない！なんでこんなことが俺にばかり起きるんだ、なぜだ！？俺が一体何をしたっていうんだ……";
			link.l1 = "旦那、どうかご自分を責めないでください。あんなろくでなしのために、あなたが涙を流す価値なんてありませんよ。 "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "ああ……落ち着くようにします。旦那、助けていただき感謝いたします。さあ、こちらがあなたの聖体顕示台です。 "+sTemp+" 神のご加護を。";
			link.l1 = "ありがとうございます、奥様。ご安心ください、洞窟で起きたことは誰にも知られません。 イエズス会の私どもは常に約束を守ります。\nそれでは、失礼いたします。";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "そこで止まれ！";
			link.l1 = "俺はここに立ってるぜ。";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "金は持ってきたか？";
			link.l1 = "なんて馬鹿げた質問だ。いや、俺はマンガ・ロサスを摘みに来たんだよ……他にここへ来る理由があると思うか？";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "おほほほ！お笑い芸人さんね！さあ、洞窟へ行きなさい、バーティが待ってるわよ。";
			link.l1 = "どうやらお前はかなりのベテラン衛兵だな……その態度ならフィリップ王本人の護衛でも務まるだろう。自分で中に入るよ。";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "待たせたな……金は持ってきたのか？";
			link.l1 = "お前がバーティー・ザ・ナッカーか？俺にはただの野盗には見えねえな。";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "俺の見た目なんてどうでもいいだろ？金を持ってきたのか、それとも持ってねえのか？";
			link.l1 = "人質はどこだ？";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "人質はちゃんと渡すさ。さあ、金貨をよこせ。俺を怒らせるなよ、坊や。";
			link.l1 = "バーティ、俺が馬鹿に見えるか？エステバン・ソサが生きて元気な姿をこの目で見るまでは、 お前に一ペソたりとも渡さねえぞ。奴はどこだ？";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "おう、意地張ってやがるな？よし、たっぷり教えてやるぜ……\n野郎ども、このクソ野郎に新しい穴を開けてやれ！";
			link.l1 = "この野郎！";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "これで踊りは満足か？エステバン・ソサはどこだ？さあ、言えよ。 言わねえなら泡が消えるまで頭を水の中に沈めてやるぞ！";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "いや…やめてくれ、お願いだ！俺はエステバン・ソサだ。";
			link.l1 = "「何だ？」";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "ああ、ああ。俺はバーティー・ザ・ナッカーなんかじゃねえ。ただの……";
			link.l1 = "この野郎！自分で自分を「誘拐」してリベロ夫人から十万ペソを巻き上げるつもりだったのか！？";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "俺の気持ちを分かってくれよ、男同士でさ。\nベリンダはな……あいつの執着した愛には正直うんざりなんだ。昼も夜も、四六時中俺にベタベタしてくるんだぜ！\nしかも、あいつの旦那まで俺たちのことを怪しみ始めてるんだ、あいつは半分目が見えねえってのによ！";
			link.l1 = "へえ、そうなのか！つまり、お前たち恋人同士ってわけか？";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "もう違う。俺は彼女から逃げてきたんだ。";
			link.l1 = "それで道中のために小銭をくすねることにしたんだな、え？さて、これからお前をどうしてやろうか？ お前が俺にやろうとしたみたいに、ジャングルに死体を隠してやるか？";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "いやだ！血なんて望んでなかった、誓うよ！";
			link.l1 = "「だから俺に手下どもをけしかけたのか？」";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "お前のポケットの中身を出させてもらうだけだ、そんだけだぜ！";
			link.l1 = "「そして俺をジャングルで裸のまま放り出すつもりか？貴様なんぞ、 俺の船の一番高い帆桁に吊るしてやりたいところだがな、このろくでなしめ！だが、それはしない。 お前なんかと関わってしまった気の毒なあの善良な女に敬意を表してのことだ。なあ、 どうするかはあの女に決めさせるために、お前を連れて行ってやろうか。」\n";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "いや、それだけは勘弁してくれ！俺はクマナには戻らないぞ！";
			link.l1 = "「ずっとこの洞窟にいたいってのか？」";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "勘弁してくれ、旦那！俺を逃がしてくれたら、ここから出航して二度とクマナには戻らねえ！ ベリンダの旦那に決闘で斬り刻まれたり、刺客を差し向けられたりするのはごめんだ！";
			link.l1 = "いいだろう。リベロ夫人のために、お前を彼女の元へ連れて行くのはやめておく。\nだが、これで全てがうやむやになるなんて一瞬でも思うなよ。彼女は、 自分が色目を使った哀れなクズの正体を必ず知ることになる。\n彼女が見て分かる証拠は何か持っているのか？";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "ほら。このターコイズの指輪だ。彼女が自分で俺にくれたんだ。";
			link.l1 = "完璧だ。それを渡して、俺の前から消えろ！";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "完璧だ。それと、ソサ、俺は考えを変えた――今はイエズス会に仕えているんだ。聖書にもこうある、「あなたがたの中から悪しき者を除き去れ」とな。 お前は邪悪なナルシストで、犯罪者で、役立たずのクズだ。この洞窟でお前を溺れさせてやるつもりだ。安らかに眠れ。";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "お前は俺たちが必要としてるものを持ってるな……";
			link.l1 = "本当かい？それは一体何だ？";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "聞いてねえよ、坊ちゃん。俺はお前の持ち物、身につけてるもん全部を渡せって命令されてるんだ。\n大人しく渡すか、痛い目見るか、どっちにする？選ぶのはお前だぜ。";
			link.l1 = "自分を戦士だと思ってるのか？お前が相手にしてるのが誰か分かってねえな。 俺はお前みたいなクズを朝飯代わりにしてるんだぜ。";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "お前、なかなか道化だな、カエル野郎？じゃあ、お前の血が地面に流れる様を見せてもらおうか！";
			link.l1 = "お前のとそっくりだよ、このバカ野郎。解剖学の授業でもしてやろうか！";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "ハハハ、よし、相棒……さっさとポケットの中身を全部出せ！おとなしく言うことを聞けば、無事でいられるぜ、わかったか？";
			link.l1 = "ちくしょう、またお前らか？こんなところまで来やがって！一体どこの野郎が雇ったんだ！？";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "お前には関係ねえ。さあ、大人しく降参して生き延びるか、それとも抵抗して死体から戦利品を奪われるか、 どっちがいい？それが俺たちの取引だぜ。";
			link.l1 = "俺からも提案があるぜ。お前の死体から戦利品をいただくってのはどうだ？";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "ご命令をお待ちしています、船長！";
			link.l1 = "ジャングルを抜けてサンアントニオ岬へ向かえ。左の道を進み、そのまま真っ直ぐ行け。頭を低くして、 岸での待ち伏せに備えろ。油断するな。俺は海から向かって、そこで合流する。そこまでどれくらいかかる？";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "六時間後に到着します、船長！";
			link.l1 = "よし。動け！";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "しぶとい野郎だな！まだ生きてやがる……もっと火薬を使うべきだったって分かってたんだ！よし、分かった、今度こそとどめを刺してやるぜ、このクソ野郎……";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
