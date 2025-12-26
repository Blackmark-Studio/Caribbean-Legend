// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "ごきげんよう、旦那。今日はどうして我が家へ？";
					link.l1 = "ごきげんよう、アビゲイル。私の名は "+GetFullName(pchar)+"。私は共和国とオランダ西インド会社の利益のために仕える船長だ。";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "なんてことだ、父の金を見つけてくれたのか？本当なのか？ああ、嬉しい！早く父のところへ行ってくれ、 君と話したがっているんだ。急いで会いに行ってくれ！";
					link.l1 = "ただいま参ります、お嬢様。";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "俺たちを絶望の淵から救ってくれたんだ、船長！本当に感謝してるぜ！これでシュヌール家の名誉も取り戻せる！";
					link.l1 = "紳士として当然の務めを果たしたまででございます、奥様。 もう私のご主人とご結婚なさるのに何の障害も残っていないことを願っております。";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "何かご用ですか、船長？";
				link.l1 = "今は無理です、奥様。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "めでたし、聖なる女王、我らの命、甘美、そして希望よ。エバの子として追放された哀れな我らは、 あなたに叫び求めます。涙の谷で嘆き悲しみつつ、あなたにため息を捧げます……おお、旦那、驚かせないでください！どうしてここに？";
					link.l1 = "失礼します、アビゲイルさんでいらっしゃいますか？リチャード・フリートウッドに頼まれて来ました……";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "何かご用ですか、船長？";
				link.l1 = "今は無理です、奥様。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "ここで何が起きているの？この騒ぎは何？パパ、この変な男は誰なの？";
					link.l1 = "ごきげんよう、マダム。アビゲイル・シュヌール様でいらっしゃいますね？お会いできて光栄です。\n無礼をお許しください、ですが、あなた宛の緊急の手紙をお持ちしました……本当は誰からかお伝えしたいのですが、あなたのご尊父が家の中に入ることすら許してくださらず、 この手紙を直接お渡しすることもできませんでした。";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "ああ、ここにいたのですね、シャルル。どこへでもあなたについて行く準備はできています！";
					link.l1 = "じゃあ、行こう。";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "もうセント・ジョンズに着いたの、シャルル？リチャードにはすぐ会えるのかしら？";
					link.l1 = "はい、奥様、私たちはセント・ジョンズにおります。\n残念ながら、リチャードは今町におりません。二日前にバルバドス近海の巡回を命じられました。\nご心配なく、一週間ほどで戻るはずです。";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "シャルル！お会いできて本当に嬉しいですわ！リチャードから何か知らせはありましたの？";
					link.l1 = "ああ、残念ですわ、親愛なるマダム。リチャードはしばらくの間、 秘密かつ重要な任務のためブリッジタウンに滞在しなければなりませんでしたの。 それはオランダ人に関係しているようですわ。リチャードがどんなお仕事をしているか、 あなたにはお話ししているのでしょう？\n";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "「シャルル！君か！やっと戻ってきたんだな！」";
					link.l1 = "ごきげんよう、奥様。お会いできて嬉しゅうございます。";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "ああ、やっと家に帰ってきたわ！またパパに会えて本当に嬉しい！シャルル、今まで色々と助けてくれてありがとう！";
					link.l1 = "どうか、そのようなお言葉はご無用です、奥様。困っているご婦人に紳士として当然の務めを果たしたまででございます。 ";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "パパ、何か思い出したら、どうか教えてください！シャルルは……信頼できる人です。あえて言わせていただきますが、彼だけが私たちを助けてくれる唯一の存在ですわ！";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "昼も夜もあなたのために祈ります！\nお願いです……やると約束してください！\nその島を見つけてくれると！";
					link.l1 = "できる限りのことをいたしますわ、奥様。";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "ああ、シャルル！戻ったのね！早く教えて、島は見つけたの？もう待ちきれないわ！";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "ああ、アビ。島も見つけたし、君のお父さんのお金も手に入れた。今、それを君に返しに来たんだ。";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "ああ、奥様。ケラー船長もあなたの島も見つけることができませんでした。できる限りのことはしましたが……";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "ああ、シャルルか！何か用かい？コーヒーでもいかがかな？";
				link.l1 = "いいえ、何もありません。どうかご心配なさらないでください。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "ごきげんよう、旦那。何かご用ですか？";
			link.l1 = "何でもありません、奥様。どうかお許しください。では、ごきげんよう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "お会いできて光栄です、船長 "+GetFullName(pchar)+"……町の他のご婦人方からあなたの噂は色々と伺っておりますわ。あなたはあの幽霊海賊船を拿捕し、 戦利品としてウィレムスタッドに持ち帰った方ですものね。教えてください、船長……その船は本当に……リチャード・フリートウッドの指揮下にあったのですか？";
			link.l1 = "お聞きになったことはすべて本当ですわ、マダム。私も真実を知って誰よりも驚きましたの。まったく、 これは大スキャンダルです！イングランド共和国の海軍士官が、 まるで普通の海賊のように自国の商人たちを略奪していたなんて！あの悪党は、オランダ西インド会社の後ろ盾を得た“幽霊船”のふりをして、自分の卑劣な行いを隠そうとしたのです。その偽装を利用して会社に罪をなすりつけ、 さらにはオランダ船まで襲撃していましたわ。";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "頭がくらくらする……こんなひどい話を聞くのは辛いですよ、船長。リチャード・フリートウッドとは個人的に知り合いでしたが、まさか彼が……";
			link.l1 = "マダム、あなたがレシフェからキュラソーへ航海された件については、 私の後援者ルーカス・ローデンブルフから伺っております。\nこれで全てが明らかになりました。フリートウッドがあなたの船を沈め、その後であなたとお父上をあの無人島から『 救出』するために戻ってきたのです。\n私自身、あの海賊の航海日誌を読みました。彼はすべての詳細を記録していました。";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "なんて悪夢なの……やっぱりパパの言う通りだったみたい。リチャードが私たちの不幸の元凶だって、ずっと言われてたの。 真実が明らかになってよかったはずなのに……ああ、ごめんなさい、船長。私の小さな頭じゃ、色々ありすぎて……こんな普通の娘に、あなたのような偉い方が何のご用なんでしょう？";
			link.l1 = "アビゲイル、私はとても複雑で繊細な件でここに来たんだ。話を聞いてくれるか？";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "もちろんです、旦那。お聞きしますよ。";
			link.l1 = "先ほど申し上げた通り、私はカンパニーに仕えております。ルーカス・ローデンブルクは私の軍上官であるだけでなく、 親しい友人でもございます。彼はあなたへの伝言を託して私を送りました。 もしあなたが彼の結婚の申し出をお受けくだされば、彼にとってこれ以上の喜びはございません。私は、 私の主君とのご結婚をお願いするために参りました。彼はあなたの幸せのためなら、 どんなことでもいたす覚悟でございます。";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "ああ、船長！今になってローデンブルク旦那が自分でやろうとしなかった理由が分かったよ……私の哀れなパパなら大喜びするだろうけど、私は……";
			link.l1 = "マダム、何かお悩みのご様子ですね。ローデンブルク旦那の誠意を疑っていらっしゃるのですか？もしよろしければ、 私が再考のお手伝いをいたしましょうか？";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "ああ、船長、ローデンブルク旦那の誠実さには何の疑いもありません。 ルーカスは私や父に本当に多くのことをしてくれました。もし彼が私たちのことを気にかけてくれなかったら、 私たちはどうなっていたかわかりません。でも、どうか私の立場も理解してください！\n私の家はロスチャイルド家ほどではありませんが、貧しかったことはありません。 シュネウル家はヨーロッパの銀行家の間で財産でよく知られています……でも今や、あの恐ろしい海賊のせいで私たちは破滅しました！もうこれ以上、 陰でささやかれるいやらしい噂には耐えられません。この町の噂好きな奥様方や女中たちは、 私がローデンブルク旦那のお金目当てだと思っています。「まるでユダヤ女みたいだ」とまで言うのです。 なんてひどい人たちでしょう！父があの島の場所を覚えていてくれたらよかったのに！家族の財産の残りを、 あの海賊たち――私の姉妹や兄を殺したあの悪党ども――の手から守るために、父は島に隠したのです！\nでも、かわいそうな父は船乗りではありませんから、島と財産の場所をどうしても思い出せないのです！ どうか父に話してみてください、船長！あなたの経験豊かな感覚なら、何か思い出させることができるかもしれません。 どうかあの島と私たちの財産を見つけてください！そうすれば、私は恥と不名誉から救われます！";
			link.l1 = "よろしい、アビゲイル。お父上と話してみよう。信じていなさい、お嬢ちゃん、私にできることはやってみるよ。";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "ありがとうございます、旦那。昼も夜もあなたのために祈ります。ご先祖の神があなたと共にあらんことを！";
			link.l1 = "さらばだ、アビゲイル。必ず良い知らせを持って戻ると誓うよ。";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "ああ、そうです！ローデンブルク旦那は誠実で親切なお方です。私は何のためらいもなく彼に同意いたしますし、 喜んで夫とお呼びしますわ。";
			link.l1 = "これで私の任務は完了したと考えます。これからローデンブルク旦那のもとへ行き、良い知らせを伝えねばなりません。 ご多幸を心よりお祈り申し上げます、奥様。";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "リチャードがあなたを寄越したのですか？！聖母マリアよ、感謝します！ああ、旦那！ 可哀想なリチャードが負傷して死にかけていると聞きましたが、本当ですか？教えてください、彼は生きていますか？！ 無事ですか？！";
			link.l1 = "リチャードは生きていて……ほぼ無事だ。まず悪い知らせから言おう。少し傷んでいて、一時的に目が見えなくなっているが、回復に向かっている。\nさて、良い知らせだ。リチャードは君と一緒にイングランドへ航海し、結婚したいと言っている。 カリブでの彼の時は終わり、君の返事を待っているぞ。";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "ああ、親愛なる使者よ、リチャードに伝えてください、私たちの幸せのためなら、 彼が望むところへどこへでも一緒に行く覚悟があると。しかし、 私たちの駆け落ちが哀れな父を死に追いやるのではと恐れております……旦那、私は絶望しております、どうしたらよいのかわかりません。リチャードがあの呪われた島と、 我が家の金貨が入った宝箱を見つけてくれたら……私がいなくても、父の慰めになるかもしれません。";
			link.l1 = "なるほど……私の任務はあなたをアンティグアまで送り届けることでしたが、これで少し話がややこしくなりましたね。\nもし私が島と宝箱を見つけてあなたの元に持ってきたら、 その時は一緒にセントジョンズとリチャードの所へ行ってくれますか？";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "ああ、旦那、家族の祈りであなたのことを必ず思い出します！最初に生まれる息子にはあなたの名前をつけます！ 本当にありがとうございます、船長！あなたのために祈ります！さあ、行ってください。 キリストと聖母マリアがあなたと共にありますように！";
			link.l1 = "お待たせしませんわ、マダム。すぐに戻りますわ。";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "ああ…彼からの手紙をお持ちなのですか？ああ、お父様、お客様にそんなに厳しくしないでくださいませ！ あなたの神経質な妄想で、わたくし恥ずかしいですわ！旦那、どうぞ、こちらへお越しください。 お話ししたいことがございますの。";
			link.l1 = "ありがとうございます、お嬢さん。この家でまともなことを言う人がいて嬉しいです。";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "父をお許しください、旦那。父は本当に善良で親切な人ですが、私たちの…不運が彼を打ちのめしてしまったのです。";
			link.l1 = "大丈夫ですよ、お嬢さん、わかっています。自己紹介させてください。私はチャーリー…クニッペルです。リチャード・フリートウッドの命令でここに来ました。 彼があなたを自分のもとへ連れてくるようにと言っています。はい、どうぞ、この手紙をお読みください。";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "「ああ、リチャード……（読みながら）。ああ、神よ！彼は……父の失った金をすべて返すと決めたのね！なんて寛大なの！親愛なる、優しいリチャード！旦那、 あなたはまるでガブリエルのように良い知らせを運んでくれる！リチャードはどこ？キュラソーにいるの？」\n";
			link.l1 = "いいえ、お嬢さん。彼は命を狙われて重傷を負いました。今はアンティグアにいます……あなたはまだ手紙を読み終えていません。";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "無原罪の御宿りの聖母マリアよ、我らのために祈りたまえ！\n教えてください、彼は無事ですか？傷はひどいのですか？";
			link.l1 = "そんなに心配しないでください、お嬢さん！リチャードはそんな簡単に野郎どもに殺されるような男じゃありませんよ。 今は休んで回復しています。彼はあなたを連れてきてほしいと私に頼みました。 それから二人でロンドンへ航海するんです……ですから、手紙を最後まで書いてください、お嬢さん、焦らないで。";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "ああ、そうでした……すみません（読書中）。キニッペル旦那、あなたと一緒に航海する準備はできています。 荷物をまとめて父と話すのに一日必要です。明日また来てください、そうしたらご一緒します。";
			link.l1 = "わかったよ、お嬢さん。俺は明日ここに来る。心配しなくていい、 俺と乗組員が航海中どんな危険からもあんたを守ってやるからな。";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "ああ、残念だな。しかし、これまで待ってきたように、もう一週間くらいなら待てると思うよ…";
			link.l1 = "よく言ったね、お嬢さん。さて、お待ちいただく間、こんな質素な船室よりも、私の友人の家に移りませんか？\nそこなら柔らかなベッドも、美味しい食事もご用意できますよ。";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "チャーリー、あなたは本当に親切ね。ありがとう。陸の上に立てるのは嬉しいわ……波に揺られ続けて、ちょっと気分が悪いの。\n";
			link.l1 = "どうぞ、私についてきてください、お嬢さん。";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "お会いできて嬉しいです、ジョン。ご親切なもてなしをありがとうございます、皆さん！";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "ああチャーリー、リチャードには数回しか会ったことがなくて、彼が何をしているのかあまり教えてもらえなかったの。";
			link.l1 = "彼が愛する女性にこれほど大きな秘密を隠していたとは、正直驚きました……お嬢さん、リチャードはただの普通の船長ではありません。彼はイングランド枢密院の特別な諜報員でもあるのです。 護国卿自らが命じる繊細な任務を扱う、とても重要な人物ですよ。今の彼の任務は、 カリブ海におけるオランダ西インド会社の交易力を打ち砕くことに関わっています。";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "旦那、何をおっしゃっているんですか？";
			link.l1 = "はい、お嬢さん。あなたの愛するリチャード――私の友人――はとても重要な人物です。私はずっと彼の友人であることを誇りに思っていましたが、 最近の彼は私にさえも秘密主義になっています。何か極秘の任務に就いているのは明らかです。 その任務のせいであなたに会えないこと、本当に申し訳なく思います。";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "チャーリー、怖いよ。彼は本当に大丈夫なの？";
			link.l1 = "それは確信している。ただ……今の彼の君への態度は認められないんだ。彼の任務がどれほど重要か、 そして君のためでも義務を裏切れないことも分かっているよ。";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "ああ、愛しいチャーリー……リチャードのことは、必要なら最後の審判の日まで待つわ。酒場の上にでも泊まろうかしら……いつまでもジョンのご厚意に甘えるわけにはいかないもの。\n";
			link.l1 = "くだらねえこと言うな、お嬢さん！あんたがいてくれるだけで光栄だ。 それに俺の名がチャーリー・クニッペルである限り、 親友リチャード・フリートウッドの婚約者を家から追い出すなんて絶対にしねえよ！";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "チャーリー……あなたの私への想い、本当に胸を打たれました。私はただの平民の娘で、それにユダヤ人なのに……";
			link.l1 = "お嬢さん！そんな無謀なことを言ってはいけません、あなたは立派なキリスト教徒のご令嬢です！ 酒場のことなんて考えるのもやめなさい！リチャード様へのお仕えであなたを守れなかったら、 私は自分を絶対に許せませんよ。";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "ありがとう、チャーリー。君がこんなにも……いい男でいてくれて嬉しいよ。";
			link.l1 = "お嬢様、それが私の務めでございます。さて、申し訳ありませんが、私はこれで失礼いたします。 今は町を自由に散策していただいて結構ですわ。この家に閉じ込められて、さぞお寂しかったでしょう？";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "そうですね……ジョンはとても面白い相手ですよ。自分の薬品や混合物、それにいろんな……病気について何時間でも話せるんです。礼儀正しくて親切な人でもありますし。\nそれから、私は定期的に教会にも通っています。地元の神父さんはとても親切です……でも、やっぱりリチャードが本当に恋しいんです。";
			link.l1 = "すぐに戻ってくると思うぜ。何か必要ならチャーリー・クニッペルが力になるぜ。";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "リチャードについて噂を聞いたんだ……姿を消したって。チャーリー、何か知ってるか？";
			link.l1 = "ああ、アビゲイル。ごめん…リチャード・フリートウッドはイングランドに帰ってしまって、もう戻ってこないんだ。昇進か異動か、 そんな感じらしい…とにかく、君にあんなことをした奴のことなんて、俺はもう知りたくもないよ。";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "ああ、こうなるって分かってたのに……（すすり泣き）どうしてパパの言うことを聞かなかったのかしら！せめてルーカス・ローデンブルクと結婚していれば、 パパも喜んだでしょうに。";
			link.l1 = "もう一度お許しください、お嬢さん……";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "何のことで、チャーリー？君はまったく悪くないよ。僕にずっと親切にしてくれたじゃないか！";
			link.l1 = "さらに悪い知らせを伝えねばならん。俺は今キュラソーから戻ったばかりだが、 ルーカス・ローデンブルクが共和国への扇動と反逆の罪で逮捕された。 彼は裁判のため鎖につながれてアムステルダムへ送還される。ローデンブルクはカンパニーのディレクター、 ピーター・スタイフェサントの暗殺を企てたんだ。それだけじゃなく、ウィレムスタッドの総督を打倒しようとし、 さらに少なくとももう一人の殺人容疑までかかっている。だから、 スタッドホルダーが軽い処分で済ませるとは到底思えないな。";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "ああ、神よ！なんて悪夢なの！気を失いそうだわ！シャルル、本当なの？いや、違うって言ってちょうだい！";
			link.l1 = "申し訳ありません、お嬢さん、さらに悪い知らせです。ローデンブルクの行動を調査する中で、 あなたのフリュート船を沈めた海賊はルーカス・ローデンブルクの命令で動いていたことが判明しました。 彼は独自にイギリス船を相手に私戦を仕掛けていたのです。本当に申し訳ありません、アビゲイル。 このカリブであなたが相手にしてきた男たちは、みな嘘つきで、泥棒で、殺人者でした。";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "ああ……私はもうおしまいだわ。シャルル……お願い……ウィレムスタッドの家に連れて帰って。パパに会いたいの……";
			link.l1 = "もちろんですわ、お嬢様。残念ながら、ここセントジョンズにはあなたのためになるものは何もありませんの。さあ、 お荷物をまとめて、ジョンにお別れを言ってくださいませ。すぐに出航いたしますわ。";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "いや、チャーリー、礼を言うのは俺の方だ。お前とジョンがいなけりゃ、俺はどうなってたかわからねえ。 お前たちはこの諸島で俺が出会った唯一の正直者だよ。";
			link.l1 = "ふむ……照れるじゃないか、アビゲイル。君の力になれて嬉しかったよ。そして、 この騒ぎについては本当に申し訳なく思っている。";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "なあ、チャーリー、キュラソーへの航海中、俺はいろいろ考えていたんだ。今はすべてがはっきりした――リチャード・フリートウッドも、マインヘール・ローデンブルクも――まるでようやく終わった悪夢みたいだ。俺はまた父上と一緒にいられるし、普通の生活に戻れるんだ\nでも、簡単にはいかないだろうな――金がまったくないからな。でも、きっと乗り越えられるさ、すべてうまくいくよ。聖母様が俺たちを見守ってくださる、 あの方は決して子供たちを忘れない。たとえ、御子を否定する頑固な父上であってもな。";
			link.l1 = "アビゲイル嬢、私があなたを助けます。";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "俺たちを助けるって？でも、どうやってだ、チャーリー？";
			link.l1 = "リチャードが君の遭難と救出の話をしてくれた。それに、君の父上が自分の持ち物を未踏の島に隠したことも知っている。 俺がその島を見つけて、君の金を取り戻してくるぜ。";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "ああ、チャーリー……その不運な島がどこにあるのか、父も私も分からないの……私たちは船乗りじゃありませんもの。それに、襲撃の時は命が惜しくて震えていたわ；血と死の匂い以外、 何も覚えていないのよ。";
			link.l1 = "アビゲイル、思い出してみてくれ。頼む、どんな小さなことでも役に立つんだ。襲撃の前に何かあったか？ この島はどんな様子なんだ？\n";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "島……島に見えるのか？湾やジャングルがあった。特に印象に残るものはなかったな。あっ、思い出した！ もしかしたら役に立つかもしれない。海賊の襲撃の少し前に、フリュート船と出会って、その船長に声をかけたんだ。 彼はうちの船に招かれて、うちの船長と一緒に夕食をとった。俺たちも同席してた。その船長なら、 この島について何か知っているかもしれない。";
			link.l1 = "それはすごいな！フリュート船とその船長の名前は何だったんだ？";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "覚えてないんだ、チャーリー。本当に……";
			link.l1 = "思い出してみろ、アビ！";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "お待ちしています。\n助けてくれ、チャーリー・クニッペル。君だけが頼りだ……\n君のために祈っている！\n幸運を祈る！";
			link.l1 = "私はこれから向かう。さらば、アビ。さらば、ソロモン。";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "ああ、まあ……なんて残念なんでしょう。私たちは期待していたのですが……それでも、チャーリー、誰も助けてくれない中で手を差し伸べてくれたこと、本当に感謝しています。 どうやらこれが神が私に与えた運命のようですね。";
			link.l1 = "さようなら、アビゲイル。君が無事でいることを願っているよ。";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "それは…それは本当なの？本当に私たちの失われたお金を取り戻してくれたの？ああ、チャーリー！";
			link.l1 = "ああ、本当だ。俺が持ってる。ほら、受け取れ。全部お前のものだ。";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "どうやってお礼を言えばいいんだ！？どうすればいい！？";
			link.l1 = "礼なんていらないよ、アビ。君のためにできる最低限のことさ。これでローデンブルクやフリートウッド、 他の妙な男たちに利用されることなく、新しい人生を始められるだろう。 君のお父上ならこの金を増やす方法をきっと見つけるさ……どうやらそれは家系の才能みたいだね。";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "チャーリー、そんなに生意気言わないで！あなたは私のために、そして私のかわいそうな父のために、 本当にたくさんのことをしてくれたのよ。もう、あなたが私の人生にいることが当たり前になってしまったわ。 私は毎日あなたのために、そしてあなたとあなたの乗組員のために、聖母様に絶えずお祈りしているの。 これからもずっと祈り続けるわ！あなたは私たちの守護天使よ。信じてくれなくても、 主があなたを私たち家族のもとに遣わしてくださったのよ\n出発する前に知っておいてほしいの。私たちの家の扉は、いつでもあなたのために開かれているわ。そして……お願い、私にキスさせて、愛しいチャーリー……";
			link.l1 = "ええと…まあ、そうだな、アビ…君がそこまで言うなら。";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "神のご加護を、シャルル。俺たちには何も変わっちゃいねえ……教会の外で残飯を乞うてるんだ。";
			link.l1 = "しっかりなさい、お嬢さん。神のご加護がありますように。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "シャルル、あなたなのね！会えて本当に嬉しいわ！どうぞ、座って！今すぐコーヒーを淹れるわ！";
			link.l1 = "私も会えて嬉しいよ、アビ。君が元気そうで安心したよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "ああ、そういうことか！？俺はお前を客として迎えたのに、盗みに来たってのか！？衛兵！！";
			link.l1 = "黙れ、愚かな娘。";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
