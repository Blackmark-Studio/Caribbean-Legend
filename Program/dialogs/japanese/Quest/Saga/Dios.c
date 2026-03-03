// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"「！教えてくれ、お前は地図職人のホセ・ディオスか？」";
				link.l3.go = "island";
			}
			link.l1 = "いいえ、何もない。";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "ああ、俺だ。お前のことは知らねえな、旦那。俺に何の用だ？";
			link.l1 = "私の名前は "+GetFullName(pchar)+" それで、俺はヤン・スヴェンソンに頼まれて来たんだ。彼のことを覚えてるか？";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "ああ、スヴェンソン旦那！もちろん覚えているよ！さあ、楽にしてくれ……あの名高いヤンは元気にしているかい？";
			link.l1 = "ありがとう、彼は元気にしているよ。旦那ディオス、あなたの助けが必要だ。あなたのご職業上、 きっとご存知のはずの件について相談したいんだ。 ヤンがカリブ海地域の地理の専門家としてあなたを推薦してくれたんだ…";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "聞いております、旦那。諸島の地理について何をお知りになりたいのですか？";
			link.l1 = "ハバナの北西、キューバとメキシコ湾の間に島か何かの地形があると言われている。\nその島はどの地図にも記されていないそうだ。\nこの噂がどれほど信頼できるものか、知りたいものだ。";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "ふむ……君が尋ねたことは、何年も私の中でくすぶっていたものだ。この君が言及した場所は、 長い間地理学者たちの好奇心を引きつけてきたが、誰一人としてその地域を探検する勇気を持った者はいなかったのだ。";
			link.l1 = "なぜだ？";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "実はな、その場所は何かしらの自然異常なんだ。あの海域では嵐の発生率が他のどこよりもずっと高い。\n原因は冷たい海流にあるのかもしれんが、それはあくまで俺の仮説だ。多くの船がそこで消息を絶っているし、 それだけで船乗りたちはあの辺りを避けるようになった。\nそもそも主要な航路は、あの海域から大きく離れて通っているんだよ。";
			link.l1 = "君も真実を知らないってことか……";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "その通りだ、旦那。しかし、俺にはいくつかの歴史的な文書と物的証拠があるからな、 その場所が存在する可能性が高いと疑う十分な権利があるんだ。";
			link.l1 = "もっと詳しく教えてくれるか？";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "かしこまりました。最も重要な証拠は、1620年にこの島を訪れたアルバラード船長の日誌から抜粋された歴史的な文書です。とても興味深い話ですよ、保証します！\n";
			link.l1 = "アルバラード船長？その名前を聞くのはこれで二度目だな……";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "驚きはしませんよ。アルバラード船長の話は何年も前から民間伝承の一部ですからね。その物語は変わり、噂や嘘、 夢で彩られ、こうして「見捨てられた船の島」の伝説となったのです。\n噂話は変わっても、紙とインクは変わりません。何百年もそのまま残るのです。さあ、この物語を読んでみてください――あなたが探しているものを見つける手助けになるかもしれませんよ。";
			link.l1 = "ありがとう！他に何かあるか？";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "あの海域の海底が隆起して広大な浅瀬を形成しているという説があるんだ。それに、潮流についてはすでに話した通りだ。 さらに、船乗りたちの話によれば、カモメや他の海鳥が大量に集まっているらしい。アルボラドは、 五十年以上前に消息を絶ったフランシスコ・ベタンコート提督の艦隊に属していた船の名前も挙げていた。 ただの偶然とは思えないな……";
			link.l1 = "私は自分の船に戻って、アルバラードの書き付けをじっくり読ませてもらいます。ご協力ありがとうございます、 ディオス旦那！";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "どういたしまして。実のところ、私はあなたを全く助けていませんよ。あなたはその場所の座標を持っていないし、 私も持っていません。そこに人が住んでいる島が本当に存在するかどうかさえ証明できません。しかし、 あなたはこの地域を探検するつもりなのですね？\nもしそうなら、どんな情報でも、特に物的証拠があれば、本当に感謝します。あなたは裕福な方のようですが、 必ずやお返しの方法を見つけます。";
			link.l1 = "よし。これで取引成立だな、ディオス旦那。もしかしたら、私の記録もいつか誰かに読まれるかもしれん……そして、誰かが伝説を書き残すこともあるかもな……";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "なぜだ？旦那 "+pchar.name+"、あなたは冒険好きで各地を旅している方のようですね、そこでお願いしたいことがございます。";
			link.l1 = "はい？聞いています。";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "ご存知の通り、私は地図製作者です。ですから、この二年間、カリブ諸島の地図を描き続けてきました。 ヌエバ・グラナダの副王主催のコンテスト用に提督のアトラスをまとめていたのです。しかし、 私が海賊に捕らえられている間、まさにスヴェンソン旦那に救われたあの海賊どもに、 私の二十四枚すべての地図が家から大胆不敵にも盗まれてしまいました。\n私は、この襲撃は私の地図を手に入れようとした競争相手の一人によって仕組まれたものだと確信しています。 かなりの時が経ちましたが、あのセットの地図は一枚たりとも見つかっていません。";
			link.l1 = "なるほど。君は私に地図を返してほしいんだな。";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "その通りだ。もしかしたら、今後の冒険の中で見つけることができるかもしれない。私の印が一枚一枚に付いているから、 すぐに分かるはずだ。もし奇跡的に二十四枚すべての地図を集めてくれたら、惜しみなく褒美をやろう。";
			link.l1 = "わかった。これからは諸島で見つけた地図を一枚一枚、注意深く調べることにするよ。\nさて、そろそろ行かなくちゃ。面白い話と書類をありがとう。";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "あ、あなたでしたか、旦那 "+GetFullName(pchar)+"？何か面白い話でもあるか？";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"！旦那神よ、どうか、私が見つけたこの地図をご覧ください。印によれば、これはあなたの地図の一つに違いありません。 ";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"！旦那神よ、良い知らせがあります。ご要望通り、あなたの特別な地図の全セットを集めることができました。 これが二十四枚すべての地図です。";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"！ああ、行ったことがあるぜ。俺たちが話していたあの神秘的な場所にな。";
				link.l4.go = "LSC";
			}
			link.l9 = "今のところ何もありません、旦那。ちょっと様子を見に来ただけです。";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "見せてくれ…（じっと見る）もちろんだ！これは提督の地図帳用に作った俺の地図の一つだ！船長、全部探し出してほしいんだ！ ほとんど不可能なのはわかってる、でも…それでも希望は捨てたくないんだ。";
			link.l1 = "無くすなよ、旦那。俺がこの地図を見つけたんだ、だから残りも見つけられる可能性があるぜ。まだカリブ海にあるんだ。 ";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "あなたの楽観主義には本当に励まされますよ、船長旦那。もしかしたら、 まだドン・フアン・デ・コルドバにこの諸島で一番の地図職人が誰かを見せつける機会があるかもしれませんね！";
			link.l1 = "お前さんは競争相手の悪党どもを全部打ち負かせるはずだ。地図は本当に素晴らしい……さらばだ、旦那！";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "信じられねえ！本当に見つけてきたのか？全員か？";
			link.l1 = "ああ。簡単じゃなかったが、この件では運が味方してくれた。カードを受け取ってくれ――どれも素晴らしい出来で、今まで見たどんなものよりも優れているぞ。";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "信じられない！本当に信じられないよ！正直なところ、こんな瞬間が来るなんて思ってもみなかった。";
			link.l1 = "Dum spiro, spero, 旦那ディオス。今ならドン・コルドバに会ってもよいぞ。きっとあなたの才能を高く評価してくれるはずだ。";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "感謝するぜ、船長！お前が俺にどれほど大きな助けをしてくれたか、まだ分かってねえだろう。約束通り、報酬をやるぜ。 さらに、贈り物も用意してある。水夫としてきっと役に立つと思うぜ。";
			link.l1 = "お前には興味をそそられたぜ、旦那！";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "ほら！これは私が設計した特製の船用望遠鏡だ。他には絶対にない一品だぞ。レンズはヨーロッパ、 スペインで最も腕の立つ職人が作ったんだ。筒は親しい銃鍛冶が仕上げてくれた。特製の三脚で、 どんな揺れでもしっかり狙いを定められる。船でも砦でも、必要なものは全部見えるぞ。\n";
			link.l1 = "なんて素晴らしい贈り物だ！ありがとう、旦那ディオス。";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "使ってください、船長旦那。私の望遠鏡があなたのお役に立てることを願っております。";
			link.l1 = "間違いないぜ！自分の船の甲板に取り付けて、覗くのが楽しみだ。";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "それに、こうなった以上、もう一つ小さな提案があるんだ。";
			link.l1 = "何だ？ちゃんと聞いてるぜ。";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "この地図は探検家には素晴らしいものだと気づいたが、船長に必要なものすべてが載っているわけじゃないんだ。\n考えてみろよ、湾や岬、ラグーンは正確に描かれているが、これじゃ島々の間を航海する航路は引けねえんだよ。";
			link.l1 = "確かに、それじゃ航海はできねえな。";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "でも、俺はお前のために諸島の地図も作れるぜ！しかもオランダ西インド会社で買えるようなものじゃなくて、 唯一無二の素晴らしい地図だ。";
			link.l1 = "ありがとう、旦那ディオス。でも、そんな地図は必要ないんだ。それでも、ご親切に感謝するぜ！";
			link.l1.go = "best_map_02";
			link.l2 = "冗談じゃないだろう！？旦那ディオス、どうして俺が断れるってんだ？必要なものを言ってくれよ――金も道具も惜しまねえぜ！";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "まあ、声をかけてみただけさ。いずれにせよ、取引できて楽しかったぜ、旦那 "+pchar.lastname+"!";
			link.l1 = "こちらこそ！幸運を祈るぜ！";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "もう道具は揃っている、ありがとう。\n諸島の標準地図と、コンパス、それに等級付きのクロノメーターが必要だ――地図は正確でなければならん、でなければ妨害行為になる。\n支払いとしては、ドゥブロン金貨の入った箱一つだ。";
			if(CheckAMapItems())
			{
				link.l1 = "言われたものはすでに全部持っている。ほら、受け取れ。";
				link.l1.go = "best_map_07";
			}
			link.l2 = "諸島の標準地図、コンパス、等級付きクロノメーター、そしてドゥブロン金貨の入った箱一つ。了解だ！ できるだけ早く届けるから、待っててくれ！";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "ごきげんよう、親愛なる友よ！諸島の標準地図、コンパス、公認クロノメーター、 それにドゥブロン金貨の箱は持ってきたか？";
			link.l1 = "まだです、旦那ディオス。でも必ずやります、約束します！";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "はい、旦那ディオス。ここに全部あります――どうぞ、お受け取りください。";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "よし、それじゃあ仕事に取りかかるぜ。\n一週間後にまた来てくれ、絶対に後悔はさせねえからな！";
			link.l1 = "疑いはありませんよ、旦那。また一週間後に会いましょう！";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "ああ、旦那 "+pchar.lastname+"「やっと来たな！諸島の地図が完成したことをお知らせできて嬉しいぞ！それに、あんたがくれた地図よりも、 はるかに出来がいいと自信を持って言えるぜ。」";
				link.l1 = "俺の友よ……この地図は驚くべき出来だ！まさに傑作と言ってもいいぜ！俺のためにここまでしてくれて、 一体どうやって礼を言えばいいんだ？";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "ごきげんよう、旦那！申し訳ありませんが、地図はまだできておりません。";
				link.l1 = "ああ、君が一週間必要だと言っていたのは覚えている。様子を見に来ただけだ。";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "おやおや、旦那。こんな地図を本当に価値の分かる高貴な船長のために作るのは、私にとっても喜びでしたよ。\nああ、それからこちらが元の海図です。海のご加護がありますように！";
			link.l1 = "本当にありがとうございます！おっしゃる通り、この地図は私にとって本当にかけがえのないものです。さようなら、 ディオス旦那！";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "本当か！？見つけたのか？まあ楽にしてくれ、これからの話は長くなりそうだ、違うか？";
			link.l1 = "本当にこの島について話したいことがたくさんあるの。\nでもまず、あなたに一つ約束してほしいわ。\nあなたが名誉ある方だと分かるから、きっと約束を守ってくれると信じているのよ……";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "「何を言っているんだ、船長？」";
			link.l1 = "そこには人が住んでいる……誰かが彼らの生活に干渉したら、喜ばれるはずがない。\n「調査」隊の到来なんて、歓迎されるとは思えないな。";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "だから、私が望むのは、これから十年間はこの会話で得た島の所在を特定できるような情報を一切公表しないと、 あなたの名誉にかけて約束してほしいということだ。\n現地の人々や彼らの生活についてはいくらでも公開して構わない。ただし、島の場所だけは絶対に明かさないでくれ。";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "同意します、船長。貴族としての誓いを立てます――今後十年間、島の場所や住民に害を及ぼすような情報を誰にも決して漏らしません。";
			link.l1 = "それじゃあ、俺の話を聞けよ。書き留めたけりゃ書いてもいいぜ。\nさて、その島はな、広い浅瀬に沈んだたくさんの難破船の船体でできてるんだ…";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "信じられない！とても貴重な情報をくれたな、船長！ベタンクール提督の子孫があの島に住んでいるとは！ これで彼の艦隊に何が起きたかも分かったし、カリブ諸島の地図から空白が一つ減ったぞ……君の話に心から感謝するよ。 "+pchar.name+"!";
			link.l1 = "今になって、なぜ私があなたに私の話を伝える時は慎重にするよう頼んだのか、わかりましたか？";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "なるほど。私が約束を守ることは間違いありません。さて……島から持ってきた物質的な財産はありますか？";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "私は廃船島への航海指示書を持っている。\nほら、見てみろ。\nこれがあれば、小型船で暗礁や残骸の間を抜けて安全に島へ上陸できるんだ。\nこの指示書がなければ島にたどり着くことは不可能だぜ。";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "残念ながら、私には何もありません。";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "（見ている）なんて素晴らしい文書だ！これは地図作成に長けた男が描いたものだな。俺でもこれ以上は無理だぜ。 信じられん！船長、この航海指示書を俺にくれないか？物語は物語だが、 この紙は旧世界で一番有名な地理学者たちに見せるべきだ！";
			link.l1 = "旦那ディオス、残念ながらこの書類は私自身のために必要なんです。\n先ほども申しましたが、この書類がなければ島を囲む暗礁を通り抜けるのは不可能です。\nですが、もしご希望なら道順の写しを作っても構いませんし、 あなたもそれを持っていてくだされば私としても大変ありがたいです。";
			link.l1.go = "LSC_10";
			//link.l2 = "旦那ディオス、残念ながら、この品は私自身が必要なのです。先ほども申しましたが、 これがなければ島の周りの暗礁を越えるのは不可能です。科学のために犠牲にしたいところですが……ご理解いただけるでしょう。";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "まったくその通りです。それはあなたの権利ですが、残念ですね……ともかく、お話を聞かせてくれてありがとうございます！地理学者や地図製作者、その他の好奇心旺盛な人々 にとって大きな貢献をされました。";
			link.l1 = "どういたしまして、旦那。さて、そろそろ行かなくては。では、ごきげんよう。";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "なんとも残念だな……まあ、とにかく話してくれてありがとう！地理学者や地図製作者、 そして他の好奇心旺盛な連中にとって大きな貢献をしてくれたぞ。";
			link.l1 = "どういたしまして、旦那。\nさて、そろそろ行かなくては。\nごきげんよう。";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "「ああ」 "+pchar.name+"。私のために多くの時間を割いてくださいましたね。スヴェンソン旦那によろしくお伝えください！";
			link.l1 = "さようなら、ディオス旦那。";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "本当にありがとうございます！ご親切に感謝します。少々お待ちください…";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "どうもありがとうございます！ご親切に感謝いたします。これで口頭の証言だけでなく、物的証拠も手に入りました……お礼をしないわけにはいきません、船長。ささやかな贈り物を用意しました。";
			link.l1 = "「どんな贈り物だ？」";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "私は地図学や地理学だけでなく、数学や天文学も好きなんだ。一年かけて、 緯度と経度を測定するための万能な道具を作ろうと試みてきた。そして、少しは進歩したんだ。ほら、見てくれ:\nこれが私の六分儀だ。自分で設計したんだよ。問題は、これが動かないことだ。 非常に精密なクロノメーターが必要なんだ。最高の職人が作ったものでも、時が経つと許容できない誤差が出てしまう。 だから、今のところ私の道具は役に立たないんだよ。\nでも、君はよく旅をするから、六分儀が動くほど正確なクロノメーターを見つけられるかもしれない。 もしそんな時計を見つけたら、ブソールも、コンパスも、アストロラーベも、砂時計も、 他の頼りないクロノメーターも必要なくなる――私の道具が全部取って代わるさ。";
			link.l1 = "ありがとう、旦那ディオス。\nあなたの発明が動くようなクロノメーターを見つけられることを願いましょう。\n私もそんな装置が……ちゃんと動く状態で欲しいものです。\nさて、そろそろ行かなくては。ごきげんよう。";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase("泥棒か、なるほど！衛兵ども、そいつを捕まえろ","泥棒か、なるほどな！衛兵ども、あの女を捕まえろ")+"!!!","信じられない！ちょっと目を離した隙に――お前、俺の持ち物を漁ってやがるな！やめろ、泥棒！！！","衛兵！強盗だ！泥棒を止めろ！！！");
			link.l1 = "あああっ、悪魔め！！！";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}