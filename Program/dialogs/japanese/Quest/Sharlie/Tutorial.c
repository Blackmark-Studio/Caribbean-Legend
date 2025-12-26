void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "見事な眺めだろう？";
			link.l1 = "この呪われた海はもう二ヶ月も俺を殺そうとしてやがる。まだ成功しちゃいねえがな。";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "まったくその通りだ。時には海が、俺たちが本当にちっぽけな存在だと教えてくれるんだよ。";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "俺は海の上じゃ、退屈か恐怖、この二つしかないと学んだ。\nだが……これは違うな。";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "はっ！初めての航海か、旦那？こんなに穏やかな時は、誰だって船長気分になれるもんさ。 今のうちに楽しんでおくんだな。";
			link.l1 = ""+GetFullName(pchar)+"。貴族なんだぞ、知っておけ。俺に「旦那」なんて呼ぶな。";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "はっ！初めての航海か、旦那？こんなに穏やかな日は、誰だって船長気分になれるさ。今のうちに楽しんでおくんだな。";
			link.l1 = ""+GetFullName(pchar)+"。貴族なんだぞ、覚えておけ。俺に「旦那」なんて言うな。";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "はっ！初めての航海かい、旦那？こんなに穏やかな時は、誰だって船長気分になれるもんさ。 今のうちに楽しんでおくんだな。";
			link.l1 = ""+GetFullName(pchar)+"。貴族なんだぞ、知っておけ。「旦那」なんて呼ぶな。";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "かしこまりました、旦那。さて、これが初めての航海ですね、旦那\n "+pchar.lastname+"?";
			link.l1 = "そんなにわかりやすいか？ああ、これが初めてだ。 俺は狭い船室やカビ臭い船の飯のために生まれてきたわけじゃねえんだよ。";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "見りゃすぐわかる、あんたは陸の者だな、旦那。";
			link.l1 = "言葉に気をつけろ！名誉ある男相手なら、手袋を投げつけて決闘を申し込むところだ。だが貴様のような百姓には――ただ耳を切り落としてやるだけだ。";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "パリなら通じるかもな。だがここじゃ、そんな言葉を口にすれば魚の餌にされちまうぜ。旦那、その剣は軽々 しく振り回さないほうがいい――それに、船長が武装したまま甲板を歩くのを許したことを後悔させるなよ。前に騒ぎを起こした奴は、 カビだらけの乾パンとネズミすら口にしないビルジ水だけで船倉送りだったんだ。しかもな、 港に着いたらその哀れな野郎、追加料金まで払わされたんだぜ。";
			link.l1 = "何を期待してたんだか……まあいい、この誤解は忘れよう。自分に言い聞かせなきゃな、このオンボロ船はルーヴル美術館とは程遠いってことを。";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "え？ルーヴル？それって何なんだ？";
			link.l1 = "はっ！ルーヴル宮は選ばれし者たちのための宮殿だ。舞踏会、レセプション、陰謀……";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "ああ……つまり娼館か。そういうのならいくらでもあるぜ。選ばれし者のための場所ってわけじゃねえ、 金さえ払えば誰でも楽しめるさ。";
			link.l1 = "はっ！お前、なかなか鋭いじゃねえか、水夫。";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "名前はアロンソだ、ちなみに。で、旦那、こんな世界の果てまで何しに来たんだ？ 大西洋を渡ってまで船乗りと口論するためじゃねえだろう。\n";
			link.l1 = "父は病気でガスコーニュの領地を離れられません。私が…兄を探すよう命じられました。兄はここに仕事で来たのですが、それ以来何の便りもありません。";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "「なぜ自分で海の苦労を味わうのではなく、信頼できる者を遣わさないのですか？」";
			link.l1 = "家族が最優先だ。最初に出会った男にその運命を任せるわけにはいかない。";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "できればそうしたかったんだけど、父がどうしても私じゃなきゃダメだと言い張るんだ。なぜかは全く分からないよ。";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "「それで、あなたの兄上の名前は何ですか？」";
			link.l1 = "ミシェル・ド・モンペール。";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "「それで、あなたの兄上の名前は何ですか？」";
			link.l1 = "ミシェル・ド・モンペール。";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "「ド・モンペ？それで、あなたは」 "+pchar.lastname+"？どうしてだ？";
			link.l1 = "そんな目で見るなよ。俺は正真正銘の息子だぜ。母親の姓を名乗ってるだけさ。";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "恥じることは何もないさ。新世界では誰もが何かしらの物語を持っている――お前もすぐ馴染めるさ。俺だって、例えば……";
			link.l1 = "俺は何も恥じちゃいねえ！マルティニークについて教えてくれよ。大きな街なのか？トゥールーズみたいにさ？";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "街だと？はっ！マルティニークは島だぜ。フランスのカリブ領の中でも最大級の一つさ。 ここじゃ燃えるようなコーヒーを育て、地獄のような硫黄を掘り出し、世界一美しい女たちが生まれるんだ。 俺に言わせりゃ、最高の組み合わせだな。";
			link.l1 = "俺はコーヒーにも硫黄にも興味はないぜ。だが、待てよ……島だって？島まるごとで兄貴をどうやって探せばいいんだ？";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "心配するな。サン＝ピエールは小さな町だ――ルーヴルじゃないが、ジャングルでもねえ。\nだがル・フランソワは……神に誓って、まともな人間が行く場所じゃねえぜ。";
			link.l1 = "仕方ない、山賊のところへ行くしかないか。ミシェルはいつも俺を助けてくれた。今度は俺の番だ。";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "悪くねえな……陸（おか）者にしちゃ。";
			link.l1 = "またかよ。いつになったらこのクソったれなマルティニークに着くんだ？";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "「五日間。」";
			link.l1 = "「五人も！？」";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "せめてそれだけはな。もし海賊が現れたら――俺たちは全滅するかもしれねえ。リーワード諸島の海は、貴重な積み荷がなくても危険なんだぜ。";
			link.l1 = "乗客以外だ！";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "ははは！心配するな。最悪の場合は俺が自らお前を船倉に隠してやるさ――ガスコーニュの貴族がラム酒の樽の中にいるなんて、どの海賊も思いもしねえだろう！俺たちも馬鹿じゃねえからな――生きたガスコーニュ人とラムを混ぜるなんて。それこそ火薬より派手に吹っ飛ぶぜ、ははは！";
			link.l1 = "ははっ！ラム酒が一ヶ月前に切れててよかったぜ！";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "えっと……そういうことは大声で言わない方がいいぜ。みんな、お前のせいでラムがなくなったと思うかもしれねえからな。";
			link.l1 = "わかったよ、アロンソ、やらないさ。そもそもあんなクズ酒なんて飲まねえよ。それに、お前の 「戦闘前に俺を船倉に隠す」って名案も却下だ。";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "なぜだ？";
			link.l1 = "私は貴族だし、剣の扱いも得意だ。それに、船倉に隠れているわけじゃない。";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "いざとなったら――俺も船を守って、みんなと一緒に戦うさ。他に何がある？";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "戦う時も逃げる時も、自分で決めるさ。どうなるか見てみようじゃねえか。";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "はっ。案外お前にも何かあるのかもな。だが気をつけろ――カリブは鼻高々に乗り込んできた奴を容赦なく叩きのめすぜ。最初の海賊どもの先鋒との遭遇で生き残れると思うなよ。\nくそ、サン・ピエールの外にいるみすぼらしいチンピラにだって、あっという間に腹を裂かれるだろうさ。";
			link.l1 = "お前は俺のことを全然知らねえな。";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "はっ。お前にも案外見どころがあるかもな。だが気をつけろ――カリブは鼻っ柱の高い奴を容赦なく叩きのめすぜ。最初の海賊どもの先鋒との遭遇で生き残れると思うなよ。いや、サン＝ ピエールの外にいるボロボロのチンピラに、あっという間に腹を裂かれるかもな。";
			link.l1 = "お前は俺のことを全然分かっちゃいねえ。";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "はっ。案外お前にも見どころがあるのかもな。だが気をつけろ――カリブは鼻っ柱の強い奴を皮まで剥ぐ土地だぜ。最初の海賊どもの先遣隊との遭遇で生き残れると思うなよ。いや、 サン・ピエールの外にいるボロ服のチンピラにだって、あっという間に腹を裂かれるぜ。";
			link.l1 = "お前は俺のことを全然分かっちゃいねえ。";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "だが、俺は新世界とその住人たちを知っている。帳簿の陰でしおれて過ごすつもりも、総督の屋敷で仕える気もないなら——すべて一から学び直す必要があるぜ。";
			link.l1 = "ここに長居するつもりはないから助かったな。";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "そう思っているのか。俺たちはヨーロッパに乗客を送り返すことなんて滅多にねえんだ。\n熱病や縄、弾丸で死ぬ奴もいるし、ここに永遠に残る奴もいる。\nか弱い貴族が船長になったのも見たし、冷酷な盗賊が立派なプランターになったのも見た。\nそして、優秀な士官が無一文の流れ者になるのもな。";
			link.l1 = "地獄のように魅力的だが、俺はフランスに帰るつもりだ。待っている人たちがいるからな。";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "ああ、そうだったな。病気の父親か？";
			link.l1 = "まあ……あるご婦人がいてな、その旦那が俺にパリにいてほしくないらしいんだよ。だが、数ヶ月もすれば情熱も冷めるさ。";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "ハハハ！それなら間違いなくここは正解だぜ。カリブは嫉妬深い旦那から逃げる奴らの楽園さ。 ここじゃ時間もあっという間に過ぎる。しばらくいれば、お前もそのうち船乗りになっちまうかもな！";
			link.l1 = "どちらかと言えば船長だな。普通の水夫には向いていないと思う。力仕事は性に合わないんだ。";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "フランスでは生まれで人を支配する。だが、船の上じゃ船長が王であり、裁判官であり、神だ。 あの帽子を手に入れるまでにどんな試練をくぐったか、誰にも分からねえ。ここじゃ、誰もが自分の分だけ報いを受ける。 甲板でよく言うだろ――人それぞれってな。";
			link.l1 = "馬鹿なことを言うな。さて、船長の話だが――お前の船長と話をする必要があるんだ、特にあいつが俺を探していたようだからな。じゃあな、アルフォンソ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "何か聞きたいことがあるのか？";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "私はピンション旦那の使いです。";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "「何もない。」";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "はっ！あのメガネ野郎もお前をこの騒ぎに巻き込んだのか？";
			link.l1 = "「メガネ野郎？」";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "彼の眼鏡を見たことがあるか？そうだろう！だが誤解するなよ――乗組員たちはピンション旦那をちゃんと尊敬してるんだ。船では腕のいい医者はいつだって重宝されるからな。それに、 あいつは会計係としてもなかなか優秀だぜ。";
			link.l1 = "「彼に何の用だ？」";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "うっ…すまねえが、それは俺たちの勝手な事情だ。だが心配すんな――船の掟は破っちゃいねえよ。";
			link.l1 = "普通の法律はどうなんだ？";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "「俺たちに普通の法律なんざ関係ねえ。で、俺の分はいくら請求されたんだ？」";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "「40ドゥブロン。」";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "５０ドゥブロン。";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "６０ドゥブロン。";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "全てをもう一度確認しないといけない。後でまた来る。";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "金貨はここだ。サン＝ピエール、今行くぞ！ははっ！";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "金貨はここだ。サン＝ピエール、今行くぞ！ははっ！";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "これが金貨だ。サン・ピエール、今行くぞ！ははっ！";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "ああ、シャルル。あまり急ぐ気はなかったようだな？船長が呼んだら、すぐに来るのが決まりだぜ。 命令に従うのが苦手か？";
			link.l1 = "俺は命令されるのには慣れてねえんだ、船長。";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "申し訳ありません、船長、遅れてしまいました。";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "お前の船――お前のルールだって、はっきり示されたな。";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "ベータテスト（チュートリアルをスキップしてマルティニークでゲーム開始）";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "私の権威に異議を唱えさせはしない。\n海の上では乗客にどれほど不幸が降りかかるか、あなたには分かるまい。\nあなたを無事サン＝ピエールまで送り届けたいと思っている私がいること自体、非常に幸運だと思いなさい。";
			link.l1 = "何の話だ？";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "謝罪は受け入れた。今を楽しめ。この夕日はそうそう見られないぞ。";
			link.l1 = "何の話だ？";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "この航海で何か学んだようで良かったぜ。船長の言葉は絶対だ――そして時には、船を離れて陸にいてもその掟は通用するんだ。";
			link.l1 = "何を言っているんだ？";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "船長。海事規則に従って私に話しかけてください。";
			link.l1 = "「何を言っているんだ、船長？」";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "お知らせしたいのですが、帆を降ろして漂流中です。\n残念ながら、マルティニークへの到着が数日遅れることになります。";
			link.l1 = "「でも、なぜですか、船長？」";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "「私がそう決めたからだ。」";
			link.l1 = "これは昨日出会ったあの商船隊――ええと、なんて言ったか――に関係しているのか…";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "「キャップスターヴィル。聞け、」 "+pchar.name+"：少し真面目な話をしなければならん。私の船室で食事に招待しよう。もうすぐ鐘が鳴る――その後で、船の最後のワインを空けながら、紳士らしくゆっくり話そう。";
			link.l1 = "お招きいただきありがとうございます。光栄です、船長。";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "準備ができたら教えてくれ。まだ少し時間があるから、船内を自由に歩き回っていいぜ――ただし、俺の船員たちの仕事の邪魔だけはするなよ。";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "他に質問はあるか？";
			link.l1 = "（片付けましょう）準備はできています、船長。あなたと一緒なら、ブルゴーニュ酒だって飲みますよ！";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "その望遠鏡でそんなに熱心に何を見ているんだ……船長？";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "船長、アロンソという男とお話しする機会がありました。彼はこの船でどんな役職についているのですか？";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "船長、あなたの船について教えてくれ。ピナスだろう？";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "また今度お会いしましょう、船長。";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "特に何もないさ、ただ水平線を見張ってるだけだ。漂流してる船は格好の獲物だからな。";
			link.l1 = "海賊を探しているのか？";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "あるいはスペイン人かもしれねえ。俺たちは護衛なしでフランスの旗の下を航海してるし、 小アンティル諸島はまさに交差点――それにジャック・バルバゾンの縄張りだ。";
			link.l1 = "誰だ？総督か？";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "もっと悪い――海賊男爵の一人だ。あいつら絞首台送りの連中は、組織まがいのものを作り、「コーストの兄弟団」と名乗ってやがる。 カリブを六つの区域に分けて、それぞれに男爵を置き、お互いに潰し合わないようにしてるんだ。";
			link.l1 = "「当局はなぜ何もしないんだ？」";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "お前は世間知らずだな "+pchar.name+"。海賊行為が存在するのは、地元当局が略奪品の分け前と引き換えに特定の港で修理や補給を許しているからだ。 認めたくはないが、この黒い疫病に実際に対処しているのはスペイン人だけだ。もし彼らがいなければ、我々 は高価な大砲で船を武装し、さらに護衛まで雇わなければならなかっただろう。";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "上級水夫。あいつのことはあまり知らねえが、一つだけ言えるぜ。誰もが秘密を抱えてるってんなら、 アロンソのは墓場丸ごとってやつだ。";
			link.l1 = "彼のことを信用していないようだな。";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "とんでもない。そんな経験豊富な男たちを船員として集めるのが簡単だと思うか？酒場の酔っ払いどもを、 少しでもまともな船員に仕立て上げるには、最低でも一年と腕のいい甲板長が必要なんだ。それに、 アロンソは船員たちの代弁者でもある。船長は下っ端と話すことなんてしないが、それじゃ愚かだし――命取りにもなる。普通の水夫にも利害があるってことを忘れちゃいけねえ。 アロンソは必要な時に彼らを代表してくれるんだ。";
			link.l1 = "「もし船員たちが不満を持ったらどうなるんだ？」";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "俺は絞首刑、あんたは刺されるだけさ。そんなに青ざめるなよ。乗組員がちゃんと給料もらって、腹を満たし、酒を飲み、 怪我も治してもらえる限り――船長と乗組員の契約は果たされてるんだ。俺は奴らの命を賭けたりしねえし、気まぐれで罰したりもしねえ。 戦利品は分け合うし、たまには酒や上陸休暇でご褒美もやる。それでかろうじて均衡が保たれてる――だからこの船はいつも目的地にたどり着くのさ。";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "痛いところを突かれたな。 "+pchar.name+"！俺の美しさについてなら、いくらでも語れるぜ。三流、二十門、大した速力――「商船」って言葉に騙されるなよ！";
			link.l1 = "銃と速度の話は分かった。でも「レート」？「商人」って何だ？";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "等級とは、大砲の数による大まかな分類だ。七等級なんてほとんど小舟みたいなもんだが、 一等級にもなればほぼ要塞だぜ。\nだが、この話をヨーロッパで言いふらすなよ――特に海軍士官の前ではな。";
			link.l1 = "なぜだ？これは船乗りの冗談か？";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "奴らはお前を完全な馬鹿だと思って笑いものにするぜ。\n本当のところ、ちゃんとした海軍なら階級制度は違うし、軍艦にしか適用されねえ。\nだがな、ここカリブじゃ、いつも通り俺たち流のやり方ってわけさ。";
			link.l1 = "「それで、自分の船を『商船』と呼んだのはどういう意味だ？」";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "また曖昧な言い方だな。軍艦は頑丈で砲撃も強い。襲撃船は奪って逃げる。商船は大量の貨物や乗組員、大砲を積めるが、 どこかで妥協しないと速度が笑いものになる。それから多目的船もあるが、持ち主の都合に合わせて変わる以外、 特に語ることはないな。";
			link.l1 = "興奮してきたな、船長。";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "「俺は自分の船が大好きだ」 "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "「おお、運がいいな――残ってるのはブルゴーニュだけだ……ちょっと待てよ、」 "+pchar.name+"。俺の昔の帽子、どこで手に入れたんだ！？\n待てよ。おい、マストの上！そっちで何が起きてるんだ？";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "おお、運がいいな――残ってるのはブルゴーニュだけだ\n待て。おい、マストの上！そっちで何が起きてるんだ？";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "申し訳ありません、de More様、しかしそこにはお入りいただけません。";
			link.l1 = "俺は前にも船長室に入ったことがあるぜ。もう覚えてるだろ。";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "ああ、俺の狡猾な計画は失敗してしまった。さらばだ、水夫。";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "申し訳ありません、旦那、しかし状況が変わりました。";
			link.l1 = "「それで、具体的に何が起こったんだ？」";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "もう航海はほとんど残っていないし、 船長としては自分の貴重品を盗まれてル・フランソワの盗賊の巣に消えられるのはごめんだ。";
			link.l1 = "船長がそんな命令を出したとき、俺のことなんて考えてなかっただろうな。";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "うーん……確かに一理あるな。それに、もう何度も船長室で食事してるじゃないか。どうぞ、ド・モール旦那。";
					link.l1 = "そうこなくちゃな！";
					link.l1.go = "OhrannikCabin_4";
					Notification_Skill(true, 12, SKILL_LEADERSHIP);
				}
				else
				{
					dialog.text = "インシ…インシニュア…何それ？そんなつもりじゃありません、ド・モール旦那！";
					link.l1 = "それなら私を通してもらわねばなりません。";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "旦那、船長室は誰でも入れる場所ではないことくらい、お分かりでしょう。命令は命令です。";
					link.l1 = "くそっ、早く陸に戻りてえぜ。こんなの屈辱だ！";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "旦那、これについてはすでに話しました。通すわけにはいきません。";
					link.l1 = "相変わらず頑固だな、水夫。じゃあな。";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				Notification_Skill(false, 12, SKILL_LEADERSHIP);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "ええ…まあいいだろう。大した害にはならんだろうしな。";
			link.l1 = "そうこなくちゃ！";
			link.l1.go = "OhrannikCabin_4";
			Notification_Skill(true, 12, SKILL_LEADERSHIP);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "他にご用ですか、旦那？中には入れません――船長が貴重品のことで心配していますので。";
			link.l1 = "盗みをほのめかしているのか、水夫？言葉には気をつけろ。それはただの中傷だぞ！";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "「何でもない、船乗り。」";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "おい、貴族のお坊ちゃん！何してやがる、悪魔をウィンドラスに詰め込もうってのか！？\nその王様みたいな足でストッパーを蹴っ飛ばしやがって！俺たち全員を海の底に送るつもりかよ！？\n頼むからよ――フランス野郎の鼻水以外には触るんじゃねえぞ！";
			link.l1 = "これは一体、何だ？";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "ウィンドラスだよ、この間抜け。錨を上げるためのものだ。もし固定してなきゃ――船をバラバラにするか、誰かを樽の中のニシンみたいに巻き上げちまうぞ！";
			link.l1 = "はは……で、逆に回せば錨が下りるってわけだろ？";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "違うぞ、天才さん、これは時間を巻き戻すんだ。残念だったな――お前はもう生まれてるからな！";
			link.l1 = "まあ、誰も怪我しなかったよな？船って本当に複雑な機械だ。これからはもっと気をつけるよ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "「さっき夕日を見ていたときと同じような畏敬の眼差しで、その大砲の長い砲身を見つめているな。」";
			link.l1 = "俺を見て楽しんでるようだな、アロンソ。さて、この軍事工学の驚異について説明してくれよ。";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "それは十六ポンド砲だ。あんなものを積んでる軍艦はそう多くねえぜ。";
			link.l1 = "それで何かに当てるのは簡単か？";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "至近距離なら――何でも粉々にしてやるぜ。百ヤード以内なら十分勝負になる。それ以上は……ほとんど音と火花だけだが、ないよりはマシだな。";
			link.l1 = "百ヤード――敵も同じことができる。";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "確かに。しかし結局は乗組員の連携と砲手の腕前次第だ。残念ながらうちの砲手は今寝てるんだよな――あいつならお前に講義をしてから自分で大砲にぶち込んでくれるぜ、はは！";
			link.l1 = "砲術士官って将校だろ？";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "普通はな。まともな砲手がいないなら、戦いは避けた方がいいぜ――大砲を海に捨てて逃げた方がマシってもんだ。\n商船の船長なんて、せいぜい六ポンド砲しか積まねえ。護衛か運に頼るしかねえんだよ。\nまあ、それも道理だ。重い大砲や弾薬がなけりゃ、船はよく走るし、売り物の積み荷も増やせるからな。\nうちの船長がこの素晴らしい大砲に大金をはたかなきゃ、ラム酒がもう少し残ってたかもしれねえな。はあ。";
			link.l1 = "船長自ら砲撃を指揮しないのか？";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "腕のいい砲手と乗組員がいれば、そんなことをする必要はねえさ。だがな、教えてやるよ。 船長が自分で大砲の照準を合わせて、「撃て！」と船楼から怒鳴るだけじゃなく直接やるときは――敵船は穴だらけになるもんだぜ。";
			link.l1 = "一発撃ってもいいか？";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "興味深い講義をありがとう、アロンソ。君はまさに海軍の知恵の宝庫だね。";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "もちろんだ！だが、大砲には手を出すなよ、それに船員たちを不安にさせるんじゃねえぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "発砲するって？ありえねえな。撃つには船長の許可がいるんだぜ。今からあいつに聞いてくる！";
			link.l1 = "必要ない！";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "「船長ーっ！」";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "どうした、アロンソ？";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "シャルル旦那が大砲を撃つことを提案している――あくまで訓練のためだそうだ。";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "俺はお前が乗組員の利益を考えてると思ってたぜ、アロンソ。だが今のお前は、次の当直を叩き起こして、 みんなを一番野蛮なやり方で起こそうって言ってるのか？\n";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "奴らの血をたぎらせて、準備させておいた方が賢明だと思うぜ。俺たちが丸見えのまま漂ってるのは気に入らねえ。 何か起こるかもしれねえからな。";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "縁起でもないこと言うなよ！…まあいい。一発だけだ。空砲だぞ。";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "楽しんでくれ、 "+pchar.name+"……俺たちは船員を起こしてくるぜ……あんたの奢りでな、ははっ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "少しお時間をいただけますか、旦那？";
			link.l1 = "話せ、水夫。";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "お会いできて光栄です、旦那。私の名はアンリです。少し金を稼ぐ気はありませんか？";
			link.l1 = "「少し」とはどれくらいだ？";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "「五百ペソ。」";
			link.l1 = "「そんなに！？そんな大金のために俺に何をさせたいんだ？反乱でも起こせってのか？」";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "おやまあ、旦那！そんなに大声を出さなくてもよろしいですわ！";
			link.l1 = "大金だな、水夫。パリならその金でいい暮らしができるぜ。";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "ああ、君の無知につけ込むつもりはないよ。ここカリブじゃ、500ペソなんて大した額じゃない。船長や商人たちが大量に品物を持ち込むから、 少しでも役に立つ物の値段はとんでもなく高いんだ。珍しい剣なんか、小さな船と同じくらいの値がつくこともあるさ。";
			link.l1 = "それは狂ってるな。";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "何と言えばいいかな？みんな状況が落ち着いて、物価が元に戻るのを待っているんだよ。\nそれで、君は500ペソ稼ぐことに興味あるかい？";
			link.l1 = "まず、どんな仕事なのか知りたい。";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "船のラム酒事情が悲惨なのは、きっとご存じでしょう。しかし、 どこかにまだ何本か瓶入りが残っていると私は確信しています。瓶入りのラムは樽の残りかすとは違います。味は格別、 毒にもならず、腕力も健康も強くしてくれる――まさに宝物です。特に航海の終わり、地平線ばかり見て気が狂いそうな時にはなおさらです。";
			link.l1 = "「それを手に入れてどうするつもりだ？自分で探せばいいじゃないか？」";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "いつそんな時間があるんだ？人手が足りねえから、俺は三人分働いてるんだぜ。\nラム酒については、転売するさ――買い手くらい見つけてやるよ。";
			link.l1 = "「まあ、男の正直さは尊敬するぜ。」";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "それで、仕事を引き受けてくれるか？三本必要なんだ。";
			link.l1 = "やってみるけど、約束はできないぜ。";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "遠慮させてもらうよ。こんな仕事、私にはふさわしくない。";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "残念だが、恨みはしないよ。良い夜を、旦那。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "はい、旦那 "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "「はい、ラム酒三本だ。」";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "ヘンリー、ピンション様から預かった物があるんだ。";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "「何でもない。」";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "彼のお役に立てていつも嬉しいですよ！今回はいくらもらえるんですか？";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28ドゥブロン。";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "３５ドゥブロン。";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "４２ドゥブロン。";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "全てをもう一度確認しないといけない。すぐ戻る。";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "ありがとうございます、旦那 "+pchar.lastname+"。財務官によろしくお伝えください。";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "ありがとうございます、旦那 "+pchar.lastname+"。財務官によろしくお伝えください。";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "ありがとうございます、旦那 "+pchar.lastname+"。財務官によろしくお伝えください。";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "ありがとうございます、旦那 "+pchar.lastname+"。見事な手際だったな！";
			link.l1 = "私の報酬も同じくらいスムーズにもらえるといいんだが。";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "金銭以外の支払いを考えてくれませんか？";
			link.l1 = "どうやら自分で言うほど正直じゃないようだな。";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "いや、違う！金が欲しいなら、金はやる！だが、知識も分けてやれるぞ。";
			link.l1 = "どんな知識だ？";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "お前の学者ぶった本には載ってねえ航海術のこと、俺はたくさん教えてやれるぜ。";
			link.l1 = "よし、それじゃあ、人生で一番高くつく授業を受けさせてもらおう。";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "五百の助言じゃ五百枚のコインの代わりにはならねえ。金はもらっていくぜ。";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "お待たせしました、旦那 "+pchar.lastname+"。改めてありがとうございます！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "心からそう願っております、旦那 "+pchar.name+"、私の教えが役に立つといいが。航海術とは何か知っているか？";
			link.l1 = "驚くだろうが、俺はできるんだ。読むことだってできるぜ。航海術ってのは、自分の位置を把握して、 例えば船の進路を決めることさ。";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "ああ。星や海図のことか。いや、そんなのは知らねえよ。それは航海士か船長の仕事だ。この辺りじゃ、「航海術」 ってのは船を操って指揮する力のことさ。";
			link.l1 = "「“ここら辺”って誰のことだ？」";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "カリブ海では、そういうものさ。理由なんて聞くなよ。つまり、航海術が上手ければ上手いほど、 船の速度や操縦性をより引き出せるってわけだ。\n乗組員も帆の操作が速くなる。\nだが、それが一番大事ってわけじゃねえ。";
			link.l1 = "お前は本当にじらすのがうまいな。";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "航海術が上達すればするほど、より大きな船を指揮できるぞ！\nだが、あまりに高性能な船を手に入れると、集中力や気力、さらには体力まで失ってしまうからな！";
			link.l1 = "危なそうだな。そんなことも知らずによく今まで生き延びてきたもんだ。";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "幸いなことに、すべてに精通している必要はないんだ。自分の不得意分野は腕のいい航海士を雇えば補えるさ。 ちゃんと給料を払い、忠誠心も確かめておけよ。自分の腕前じゃ扱いきれない船で航海士を失うなんて――最悪だからな。";
			link.l1 = "講義ありがとう、ヘンリー。必要になるかは分からないけど、知識はいくらあっても困らないからな。";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "どういたしまして、旦那 "+pchar.lastname+"。改めてありがとうございます！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "（歌う）セ・ラ・メール・ミシェルが猫をなくした…誰が返してくれるのかと窓から叫んでいる…\n";
			link.l1 = "「ここで何してるんだ、水夫？」";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "だから今の私はミシェル夫人みたいなものさ――猫を探しているんだ。ただ、私は叫ばないよ――彼女は大声を嫌うからね。";
			link.l1 = "今朝あいつを見た――また俺のブーツにしがみついてきやがった。";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "大したことないさ。船長のブーツの方がひどかったぜ。猫は好きか？";
			link.l1 = "もちろんだ。";
			link.l1.go = "OldSailor_3";
			link.l2 = "別にそうでもない。";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "道理だな。じゃなきゃ、あのクソネズミどもをどう始末するんだ？";
			link.l1 = "でも猫にはいつまでも頼れないだろう？あいつらは本当に気まぐれな生き物だからな。";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "残念だな。猫は船の上で大事にされてるし、みんなに愛されてるんだぜ。そうじゃなきゃ、あの忌々 しいネズミどもをどうやって退治するんだ？";
			link.l1 = "でも、いつまでも猫に頼るわけにはいかないだろう？あいつらは本当に気まぐれな生き物だからな。";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "そうだな。だから俺たちはヒ素に頼るんだが、カリブでそれを見つけるのは運次第だ。だから積み荷を失う――ネズミがラム酒を汚し、ビスケットを台無しにし、他の物も全部かじりやがる\nそれで会計係はこう言うんだ。「気にするな、これは交易税みたいなもんだ」ってな\nでも本当のところは分かってる――あいつがただ怠け者なだけさ。シャントールがいなけりゃ、とっくに船長に船倉でネズミ捕りさせられてただろうよ、 はは！";
			link.l1 = "猫のこと、うまくいくといいな。俺はもう行かなくちゃ。";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "待ってください、旦那。普通の水夫は甲板でしか貴族の乗客を見かけませんが、 あなたはこんな船倉までいらっしゃるとは！";
			link.l1 = "好奇心は猫を殺すってな、ははっ！";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "船乗りの技術に興味が出てきたのか？";
			link.l1 = "どうやら乗組員全員が、上陸する前に俺を本物の水夫に仕立て上げるつもりらしいな。";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "驚くことじゃねえさ。海は俺たちに多くの悲しみをもたらしたが、それでもこの仕事が好きなんだ。\nそして、水夫ってのは新しい奴が本気で興味を持ってくれると、やっぱり嬉しいもんさ。";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "さて教えてくれ。船長にとって一番大事な技能は何だ？";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "航海術。指揮できる船の大きさを決める。";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "嘘はつかない――知らないんだ。";
				link.l1.go = "OldSailor_9_1";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "気を落とさないでください、旦那。乗組員と話したり、船内を見て回ったりしてみてください。もし答えを見つけたら――あなたにも本当に面白いものをお見せしますよ。まるで私たちの仲間になったかのようにね。";
			link.l1 = "覚えておくよ。じゃあな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "正解だ！さて、もう少し難しい質問だぞ：横帆と縦帆、どっちが優れていると思う？";
			link.l1 = "何とも言えないが、何か企みを感じるな。それぞれに利点があると言えるだろう。";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "また正解だ！追い風なら横帆が最高だが、縦帆装備なら風上にも向かえるし、横風でも進めるんだ。 無駄に時間を過ごしていなかったようで嬉しいぞ、旦那。";
			link.l1 = "この知識が役に立つことなんてあるのかね……。まあ、本物の船乗りのふりをして上流階級のご婦人方を感心させたい時くらいか、ははっ！";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "ああ、よく分かりません、旦那 "+pchar.name+"。あんたは貴族かもしれねえが――俺たちをちゃんと扱ってくれる。そこは評価してるぜ。\n船長が何か企んでる。あんたの前を黒猫が横切ったぞ。";
			link.l1 = "馬鹿なことを言うな。何を言ってるんだ、水夫？";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "噂によれば、彼は数日前に通りがかった船でキャップスターヴィルへ手紙を送ったそうだ\nそして航海の終わり、皆が陸地を渇望して叫んでいたまさにその時に、漂流してしまったんだ。";
			link.l1 = "噂なんて気にしないさ。どうして気にする必要がある？俺は直接本人に聞けばいいだけだ。 貴族に対してはっきり答えを拒むはずがないだろう。";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "あなたは彼のことを知らないんです、旦那 "+pchar.name+"。奴はやるさ――しかも徹底的にな。今は怒ってる――鍵を失くしたからだ。";
			link.l1 = "「鍵？」";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "船室の中の彼のチェストにあるぜ。どこかに転がってるはずだ。";
			link.l1 = "鍵を探せ？俺がか？";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "それはあなた次第です\nところで、旦那 "+pchar.name+"、ラム酒はまだ残ってるか？まさか全部ヘンリーにやっちまったわけじゃねえだろ、はは！";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "はい。どうぞ。";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "残念ながら無理だ。あの三本の瓶を見つけただけでも奇跡だったんだ。";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "確かにそうです。ご武運を、旦那 "+pchar.name+"……あの縞模様の悪党を引き続き探すぜ。";
			link.l1 = "お前にも幸運を祈るぜ、水夫。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "船員たちにいいことをしてくれたな、旦那 "+pchar.name+"。これはちょっとしたお守りだ、幸運を祈るぜ！";
			link.l1 = "穴の開いた石？可愛らしいな。";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "好きなだけ笑えばいいさ。海の上じゃ、お守りがあっても悪いことはねえ。";
			link.l1 = "お前たち水夫は迷信深い連中だな。幸運を祈るぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "もう答えは見つけたか？船長にとって一番大事な技能は何だ？";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "航海術。指揮できる船の大きさを決める。";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "「まだだ。」";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "よう、坊や！";
			link.l1 = "お前は俺の父親には見えないな。ありがたいことだぜ。";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "ははっ！あんな背が高くて気高い息子がいたら自慢だがな。だが俺が作れるのは、俺みたいな地べたの塩っ気野郎だけさ。 ";
			link.l1 = "よし、褒め言葉は受け取っておくよ。で、何か問題でも？";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "手を貸してくれ、坊や。砲のそばで弾を積めと命じられてな、ここの危険な海域で何かあった時のためによ。 見張りの半分を使って、この鉄の野郎どもを船倉から引き上げてきたが、最後の箱で腰がやられちまったんだ。";
			link.l1 = "仲間に聞けばいいじゃねえか？船乗り同士は助け合うもんだと思ってたぜ。";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "俺たち兄弟分が本当に嫌うのは、ろくな理由もなく重い荷物を運ばされることだぜ。今日は運が悪くて、 弾薬箱を船倉から引きずり出す羽目になった。こんな仕事、俺みたいな腕利きの船乗りには似合わねえよ。でも、 仕方ねえだろ？";
			link.l1 = "泣き言はやめろ。手を貸してやるよ。どうせなら、みんなが脅してくるあの牢屋とやらを見物できるってわけだな。";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "（アスリート）俺の腰のこのブロードソードが見えるか？お前より重いんだぜ。お前のボールなんて、 楽勝で取ってきてやるよ。";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "俺は肉体労働なんてしないぜ、水夫。自分の箱は自分で運べよ。";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "ありがとうな、坊主。腰を痛めねえように気をつけろよ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "調子はどうだ、坊主？";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "ほら、一杯だ。もっと大きいのかと思ったぜ。";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "「お前の名前はポールだろ？」";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "「さらば。」";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "「え、ええ……。」";
			link.l1 = "ピンション旦那からもらった名簿にあなたの名前が載っている。";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "ふう、一瞬どうなるかと思ったよ……ああ、ポール、それは俺のことだ。で、俺にいくら用意してくれたんだ？";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "２０ドゥブロン。";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "「25ドゥブロン。」";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "「30ドゥブロン。」";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "すべてをもう一度確認しないといけない。後で戻ってくる。";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "「ありがとうな、坊主。」";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "ありがとう、坊や。";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "「ありがとうな、坊主。」";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "これ以上大きかったら敵への贈り物だぜ！船体に当たれば――まあ、誰かに木片が刺さるだけかもしれねえ。でも艫に当たったら、玉みてえに甲板中を跳ね回るぞ！";
			link.l1 = "前にもそんなことを見たことがあるか？";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "俺自身が見たんだ、坊主。人間ってのは殺しの道具を作るのが本当にうまいぜ。ブドウ弾を見ろよ――射程は短いが船体は貫通しねえ、だが一発で十人をあの世に送れる。鎖弾なら――帆に当たればズタズタだ！爆弾については……何も言わねえ、見たこともねえし、神に感謝だ！悪魔の道具だし、しかも高ぇんだよ。";
			link.l1 = "俺はもう大砲の威力がどれほど恐ろしいか見てきたぜ――お前の可哀想な背中に聞いてみろよ。";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "いやあ、俺に本当に恩を売ってくれたな。お返ししよう。ほら――ほとんど満タンの極上ラム酒の瓶だ、ははっ！";
			link.l1 = "どこで手に入れたんだ？ラム酒なんてとっくに底をついたって聞いてたぜ。そんな上物があるなら、 誰にだって船倉の箱を一つどころか全部運ばせることができただろうよ。";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "そうなっちまったんだ、坊主。礼を言うぜ、じゃあな。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "ああ、旦那 "+pchar.lastname+"。もし寝るつもりなら――運が悪いな。お前のベッドはうちの砲術士が占領してるんだ。知っての通り、あいつを起こすのはなかなか骨が折れるぜ。 ";
			link.l1 = "言わせてもらうが、必要なときはあいつ、ちゃんと全部聞こえてるんだよな！";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "「いいえ。」";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "そんなの大したことねえよ。シャープの船には、かつて盲目の砲手がいたって聞いたぜ。 やつは大砲の音だけで狙いをつけたらしい。";
			link.l1 = "今日はやけにおしゃべりですね、ボースン旦那。";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "それには理由があるんだぜ！もうすぐ上陸する――残った品をチャリンと音のするペソに変える時だ。サン＝ピエールの売春宿は、そういう金をいつだって大歓迎さ、 ははっ！";
			link.l1 = "船内の小取引を担当しているのが会計係じゃなくてお前だとは、妙な話だな。";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "主計長は人と話すのが苦手なんだよ！それは水夫長の役目さ――口も手も達者だからな、はは！主計長には主計長なりの企みがあるんだろうが――俺はそんな怪しい話には首を突っ込まねえよ。";
			link.l1 = "「さて、今日は何があるんだ？」";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "船に残った最後のラム酒の瓶、いくつかの幸運のお守り……そして、ほら！完璧な宝の地図のできあがりだ。";
				link.l1 = "お前は水夫長じゃなくて商人になるべきだぜ！どれ、何を持ってるか見せてみろ。";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "他に何かあるか？";
				link.l1 = "どれ、見せてもらおうか。";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "お守りか？お前の首にぶら下がってるやつみたいなやつか？";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "すまない……今、宝の地図って言ったか？";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "また今度にしよう。";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "ああ、目ざといですね、旦那。そう、『コーラルヘッド』――素晴らしい品です。特に私にはね。斬り込み隊を率いる時、これがあれば男たちを鼓舞できますから。";
			link.l1 = "本気でそう信じてるのか？";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "信じる必要なんてねえさ。カリブじゃそういうもんだし、船乗りの運命ってやつだ。お守りは役に立つぜ。だから、 俺たちと一緒にいるなら、いくつか持っておくといい――場面ごとにな。";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "ああ、そうさ。カリブじゃ珍しくもねえよ。運が良けりゃ大金持ちになるやつもいる。 そいつらは税金を払って静かに長生きするか……金貨を洞窟に隠すかだ。\n残るのは墓と財宝……それに紙切れ一枚ってわけさ。";
			link.l1 = "「そんな簡単に？」";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "そうでもねえさ。地図は高いし、お前みたいな他の狩人も引き寄せちまう。しかも、 手に入る財宝が苦労に見合わねえこともあるんだ。あの偉大なアルバート・ブラックウッドでさえ、 最初は苦労したもんさ。財宝探しを生業にしな。見つければ見つけるほど、報酬もでかくなるぜ。 運のお守りでも持ってりゃ、なおさらいいな！\n";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"！ちょっと待ってくれ。";
			link.l1 = "また説教かい、ピンション旦那？あんたの大事なインクには触ってないってば！";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "じゃあ、その小さな手帳には何で書き込んでるんだ？聖水か？乗客の持ち物リストにはインクなんてなかったぜ。まあ、 今はそれどころじゃねえだろうが。";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "And two hundred more — for the broken windlass. The anchor cable snapped.";
			dialog.text = "お前はまだ船の金庫に三十ペソの借りがある――壊した雨水樽の分だ。あのシャツを洗おうとしたお前の珍妙な試み、もしあの時また雨が降らなかったら、 もっと高くついてたぜ。 "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "まさに俺にぴったりだな――船を降りた途端に借金かよ。ほら、持ってけ。";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "まったく、船を降りた途端に借金とはな。ほらよ。";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "それだけか？これは賭博の借金じゃないんだ。今は少し忙しい――港に着くまで待ってもらうぞ。";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "残念だな。さて――本題に入ろう。君に頼みたい仕事がある。";
			link.l1 = "あんた、人付き合いが得意ってわけじゃなさそうだな？";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "「ちょっと待って、数えさせてくれ。」";
			link.l1 = "夕食の後、俺がテーブルに残したパンくずの数を忘れずに数えてくれよ。";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "おめでとうございます。船の財務には、今のところもうあなたに聞くことはありません。\n単刀直入に言うぞ――お前に任せたい仕事がある。";
			link.l1 = "あんた、人付き合いが得意ってわけじゃなさそうだな？";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "人付き合い？あまり得意じゃない。でも数字には強いんだ。\nあなたはどうです、旦那 "+pchar.lastname+" ――数の数え方は知ってるか？";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "（会計係）帳簿や為替手形には慣れているんだ。ゼロが何を意味するかだって知ってるぞ。";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "父上のわずかな仕送りを今季いっぱい何とかやりくりできるくらいだ。";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "おおっ！もっと早く教えてくれりゃよかったのに――この航海、もっと面白くなったかもしれねえぜ。";
			link.l1 = "任務の話をしたか？";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "自分のためにも、船主には絶対ならない方がいいぞ。自分だけじゃなく、乗組員全員まで破産させちまうからな。";
			link.l1 = "任務の話をしたか？";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "はい。ご存知かどうかわかりませんが、船長の次に偉いのは会計係と船医なんですよ。\n"+"どちらもなしで出航するのは金を危険にさらすことになる。金がなければ、船なんてただの高価な木の塊だ。\n"+"会計士がいなければ、小さなスループ船ですら船長を破産させかねない。そして、医者なしで最初の戦闘に臨めば、 乗組員全員が全滅することもあり得る――その後は、新たな船員を雇い、訓練するという長くて高くつく手間が待っているのだ。\n"+"幸いなことに、俺はその両方を兼ねているんだ。だから、個人的な取引をしたり、 乗組員にちょっとした用事を頼んだりできるってわけさ。\n"+"もちろん、私は気前よく払う――今がその時だ。\n"+"このリストと、このドゥブロン金貨の入った箱を持っていって、乗組員に支払いをしてほしい。\n"+"書いてある通りだ！だからお前に数えられるか聞いたんだよ。";
			link.l1 = "自分でやればいいじゃないか？支払いを待ってるなら、向こうから来させればいいだろう。";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "今はやることが多すぎる。航海もあと数日で終わる――すぐに百人もの船乗りたちが給料を求めて列を作ることになるんだ。";
			link.l1 = "「ドゥブロン金貨の話をしていたな……」";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "スペインの金貨。堅実な通貨だ。富の真の尺度でもある。最も希少で価値あるサービスだけが、これで支払われる。\nこうした箱に入れて保管されるのが普通だ。";
			link.l1 = "「それで俺には何の得があるんだ？」";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "（会計係）150ペソ、そして追加でドゥブロン金貨5枚――ほとんど同業者みたいなものだからな。それにペソとドゥブロンの為替レートも公正にしてやるよ。";
			}
			else
			{
				dialog.text = "150ペソと、ペソをドブロン金貨に両替できる権利だ。大した額じゃねえが、仕事は簡単だぜ。";
			}
			link.l1 = "わかった。リストと箱を渡せ。";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "この手の仕事は私には向いていないようです。さようなら、ピンション様。";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "お前の勝手だ。ただし、俺の邪魔はするなよ、旦那 "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "さあ、どうぞ。神に誓って——必ずチェストからドゥブロン金貨を持っていくのを忘れるな、リスト通りに正確に運べ、 余計なものは絶対に懐に入れるな。空になったチェストもちゃんと返してくれよ。\n無理するな、旦那。なんでそんなガラクタばかり抱えてるんだ？いくつかチェストにしまっておくのをおすすめするぜ。";
			}
			else
			{
				dialog.text = "さあ、どうぞ。神に誓って――必ずリスト通りに宝箱からドゥブロン金貨を持っていくんだ、余計な分は絶対にくすねるなよ。\n空になった宝箱もちゃんと返してくれよ。";
			}
			link.l1 = "かしこまりました。それでは、また近いうちにお会いしましょう、Pinchon様。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "どうだった？全員に支払いは済んだか？残ったドゥブロンと空の箱は持ってきたか？";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "すべて完了した。";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "「まだです、Pinchon様。」";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "さて……";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "お前は計算ができるって言ってたよな。だが、予想よりドゥブロンが少なかったぜ。つまり、 俺の仕事が増えるってことだ、減るんじゃねえ――だからお前には報酬はなしだ。";
				link.l1 = "「でも、ドゥブロンの交換はまだしてくれるのか？」";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "お前は計算ができると言ってたよな。だが、持ち帰った数が多すぎるじゃねえか。これじゃ俺の仕事が増えるだけだ、 減るどころか――つまり、お前には報酬は出ねえってことだ。";
				link.l1 = "交換の話はどうなった？";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "すべて正解だ。若い世代がまだ数を数えられると分かって嬉しいよ。ありがとうございます、旦那。 "+pchar.lastname+"。これが報酬だ――それに、同業者としてちょっとしたボーナスもつけておくぜ。";
					link.l1 = "「交換は？」";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "すべて問題ありません。若者が金をきちんと扱うのを見ると嬉しいです。ありがとうございます、旦那。 "+pchar.lastname+"。これが報酬だ。";
					link.l1 = "まだ交換を続けているのか？";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "いいだろう。1ドゥブロンにつき115ペソだ。興味があれば俺のところに来な。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "もちろんだ。1ドゥブロンにつき105ペソだぜ。興味があったら俺のところに来な。\nひとつ忠告してやるよ。もし運命があんたを船の船長にしたら、まず最初に会計係を雇え。腕が悪くても、 きっと大金を守ってくれるぜ。";
			link.l1 = "ありがとうございます、Pinchon様。";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "もちろんだ！1ドゥブロンにつき100ペソ――これは公正なレートさ。カリブの銀行ならもっと取るぜ。\nひとつ忠告しておく。もし運命が巡ってお前が船の船長になったら、まず最初に会計係を雇え。腕が悪くても、 きっと大金を守ってくれるぜ。";
			link.l1 = "ありがとうございます、Pinchon様。";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "「怠けてますね、旦那」 "+pchar.lastname+"?";
			link.l1 = "お前も船倉の担当になったのか？";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "俺は船医だ、 "+pchar.lastname+"！もうすぐ士官室は負傷者でいっぱいになるし、俺はどんな戦士よりも多くの血を見ることになるだろう。 たとえ俺がただの主計長だったとしても、やっぱり危険な最前線に立つさ。いや、 心地よい船倉で休むように命じられたのはお前だけだ。";
			link.l1 = "「じゃあ、こんなところで何をしているんだ？」";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "戦いが始まるまであと数時間あるから、日々の帳簿を締めるには絶好のタイミングだ。 ドゥブロン金貨の箱は君が持っているな、ド・モール。返してもらおうか。";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "持っていけ。二度とここに顔を出すんじゃねえぞ。";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "お前の荷物は別の場所に置いてきた。";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "そのつもりはなかったんだ。俺は陸の素人じゃねえ――俺の居場所は船倉じゃねえよ。じゃあな。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "どこか別の場所で……この話は戦いの後、船長の前で話そう。それまで待て。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "ドゥブロン金貨に興味がおありですか、旦那 "+pchar.lastname+"?";
			link.l1 = "取引しよう。";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "今は無理だ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "船長、警報だ！水平線に海賊が見えるぞ！";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "アロンソ、旦那を案内してくれ "+pchar.lastname+" 船倉へ運べ。それから、ドリュサック旦那を起こして砲手たちの準備も忘れるな。";
			link.l1 = "船長、俺は戦う準備ができてるぜ！貴族たる者、そんなことは……";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "もし何かお力になれることがあれば…";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "待って、じゃあブルゴーニュはなしってことか……";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "アロンソ、そいつをここから連れ出せ。\nさっさと動け、この怠け者ども！\n帆を上げろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "アロンソ、そいつをここから連れ出せ。さっさと動け、この怠け者ども！帆を上げろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "アロンソ、そいつをここから連れ出せ。さっさと動け、この怠け者ども！帆を揚げろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "くそっ！頑固な悪党どもめ！";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "「お前、ここで何してやがる！？仲間を見捨てて戦いから逃げてやがるのか、このクズ野郎！今すぐぶっ殺してやるぜ！」 ";
			link.l1 = "俺の船倉に忍び込むなんて悪手だぜ。俺が直々にお前の腹を裂いてやる。";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "お前、やっと立ってるって感じだな。その血のほとんどは自分のじゃねえだろ。";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "（決闘士）これがどれほど恋しかったことか。";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "へっへっ。さあ行けよ、坊ちゃん。";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "へっへっ。じゃあ、俺には失うものなんてねえな。";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "何をぶつぶつ言ってやがるんだ！？";
			link.l1 = "二ヶ月だ。二ヶ月も俺の剣を鞘に収めたままだった。さあ、踊ろうぜ！";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "少なくともお前は生きてるな……俺はもう駄目だ。舵にひどい一撃を食らっちまってな……";
			link.l1 = "何が起こったんだ！？";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "乗り込まれたんだ。くそっ！しぶとい野郎どもめ！\nよく聞け、俺たちは砲甲板を死守したが、上ではこれからが本番だ。誓ってもいい、奴らはすぐにここへ降りてくるぞ。 散弾銃を持て！おい、気をつけろ！弾はもう込めてあるからな！";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "（狙撃手）俺のことは心配いらねえ。手を出す奴には穴を開けてやるさ。";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "ブドウ弾が入ってるんだ。うまくやれば、一度に二人か三人まとめて倒せるぜ。\nお前ならできると信じてる。 "+pchar.name+"。奴らを撃退したら、死体を調べてくれ。俺のために酒でも見つかるかもしれねえ……そうじゃなきゃ、俺は役に立たねえぞ。";
			link.l1 = "頑張れ、アロンソ。客人たちが来るぞ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "「よし……よくやったな。」 "+pchar.name+"。俺のために何か見つけたか？";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "これで間違いないと思うぜ。まあ、ちょっと怪しく見えるけどな。";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "「まだ探してるぜ！」";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "なかなかやるじゃねえか、ははっ！ありがとな、 "+pchar.name+"。それに、あの三人――見事に片付けたな。お前は本物の貴族だ、指揮を執れ。俺たちでこの甲板を守り抜けるさ。上の連中もうまくやれば――今日は俺たちの勝ちだ！";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "ずっと良くなったな。散弾銃は装填したか？";
				link.l1 = "ちょうどそれをしていたところだ……なんで急に静かになったんだ？";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "あなたは本物の貴族だから、指揮を執ってくれ。";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "ずっと良くなったな。散弾銃は装填したか？";
			link.l1 = "ただそれをしていただけだが……なんで急に静かになったんだ？";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "ちょっとした演出さ。これから始まるぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "ここまで来たな、始まりの場所で終わるとは。助けてくれて感謝するぜ、 "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "これでおあいこだな。お前がどうやって俺をあそこから引っ張り出したのか、もう覚えてもいねえよ。";
			}
			else
			{
				link.l1 = "これでおあいこだな。お前と仲間たちがいなきゃ、俺はいまだにあそこにいたはずだぜ。";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "言われた通り船倉にいればよかったのにな。\n船長が生きていれば、きっちり叱ってもらえたのに残念だぜ。";
			link.l1 = "奴を死体の山の下から引っ張り出さなきゃならなかったんだ。どれだけの悪党を倒したんだ？";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "ある者は奴が三人倒したのを見たと言い、またある者は十数人だと言う。俺が思うに、数えてたのは悪魔だけだぜ。";
			link.l1 = "どうしてこんなことになったのか、まだ話してくれていないぞ。";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "話すことなんてねえよ。俺たちの十六ポンド砲じゃ、どの海賊ブリッグからも守れなかったんだぜ。\n"+"あっという間に襲いかかってきて、俺たちが旋回してる最中にブドウ弾をぶち込まれ、すぐさま乗り込まれたんだ。 甲板の有様を見せてやりたかったぜ――外科医の出番なんて何も残っちゃいなかったさ。\n"+"海賊と戦う最悪な点は――儲けがないことだ。貧乏人ばかりでな。\n奴らのブリッグさえ奪えなかったぜ。";
			link.l1 = "それで、この後はどうなるんだ？";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "船は無事に浮かんでるし、残った乗組員もサン・ピエールまで予定通りに連れて行くには十分だ。 そこで俺は新しい船長を探すし、あんたは兄貴を見つけて冒険の話をたっぷり聞かせてやれ。 これから先に何が待ってるか――それは神のみぞ知る、だな。\n"+"だが一つだけ確かなことがある――お前なら俺たちとすぐに馴染めるさ。陸のネズミにしちゃ悪くねえな。 "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "はっ！これから内側からひっくり返りそうになるぜ。遠慮すんな。それはお前の体から恐怖が抜けていく証拠だ。 カリブへようこそ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}