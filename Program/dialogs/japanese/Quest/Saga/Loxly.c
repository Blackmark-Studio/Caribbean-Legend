int iLoxlyPseudoGlobal;

// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "私の名はアルバート・ロクスリー、弁護士です。\n依頼人の利益を法廷で守ります。\n私のサービスは高額ですが、それだけの価値はありますよ、保証します。";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "私はイギリス当局に追われているんだ。";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "フランス当局に困っているんだ。";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "私はスペイン当局に追われているんだ。";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "俺はオランダ当局に目をつけられてるんだ。";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "俺は密輸業者たちと喧嘩したんだ。";
						Link.l5.go = "contraband";
					}
					Link.l7 = "ありがとうございます、しかし幸いなことに、これまで弁護士のお世話にならずに済んでおります。";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "ありがとうございます、しかし幸いにも、これまで弁護士の世話にならずに済んでおります。";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "あなたの助力が必要だ。私はヘレン・マッカーサーという若い女性の正式な代理人である。 彼女は有名なニコラス・シャープの孫娘だ。母親と叔父の死後、法的に残された唯一の相続人である。 叔父の遺言によれば、彼女にはイスラ・テソロのすべての権利がある。ヘレンが島の正当な女主人となるために、 あなたはいくら要求するつもりだ？";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "私のサービスが必要ですか、旦那？ご満足いただけることをお約束します。";
						link.l1 = "はい、必要です。私はヘレン・マッカーサーという若い女性の正式な代理人です。 彼女は有名なニコラス・シャープの孫娘であり、母親と叔父の死後、唯一の法定相続人です。叔父の遺言によれば、 彼女はイスラ・テソロのすべての権利を有しています。\nヘレンが島の正当な女主人となるために、あなたの助力にはいくら必要ですか？";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "旦那、私はまだあなたのご用件の詳細を存じ上げておりません。すでに申し上げた通り、後ほどお越しください。";
						link.l1 = "「結構だ。」";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "旦那、申し訳ありませんが、必要な書類をすべて公文書館から集めるにはもう少し時間が必要です。 まだ準備ができておりません。どうか、後ほどまたお越しください。";
						link.l1 = "「結構だ。」";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "旦那、なんでそんなに仕事が遅かったんだ！？あなたの主人はもう終わりだ。遺言状の有効期間は切れたし、 イスラ・テソロは今やイギリスのものだ。\nすぐに軍事基地になるぞ。";
							link.l1 ="なんてこった！俺の努力は全部無駄だったみたいだな…";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "ああ、ここにいらっしゃいましたね、旦那。資料には目を通しましたので、前金をいただく時です。 ドゥブロン金貨はお持ちですか？";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "ああ、持っているよ。ほら、これがあんたのドゥブロンだ。";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "記憶が悪くて申し訳ありません、船の箱に置き忘れてしまいました。すぐに持ってまいります。";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "旦那、なんでそんなに仕事が遅かったんだ！？もう依頼主は終わりだ。遺言状の有効期間は切れたし、 イスラ・テソロは今やイングランドのものだ。\nすぐに軍事基地になるぞ。";
							link.l1 ="おったまげたぜ！俺の努力は全部無駄だったみてえだな……";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "旦那、あなたのご主人の血筋を証明できるものは見つかりましたか？";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "まだだ。しかし、今取り組んでいる。";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "はい。本当に決定的な証拠がございます。";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "あっ、ここにいらっしゃいましたか、旦那。お会いできて嬉しいです。正直に申しますと、 かなり長い間お待ちしておりました。こちらがご主人様でございますか？";
						link.l1 = "はい。ヘレン・マッカーサーを紹介しましょう。";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "私のサービスがご入用ですか、旦那？きっとご満足いただけますよ、保証いたします。";
					link.l1 = "ありがとうございます、でも今は必要ありません。";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "ごきげんよう、旦那。私の報酬を持ってきてくださったのでしょうか？";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "ああ、持っている。ほら、これがあんたのドゥブロン金貨だ。";
						link.l1.go = "saga_36";
					}
					link.l2 = "あのな、ロクスリー旦那、俺は思ったんだ……つまり、九百ドゥブロンもあればあんたの仕事には十分すぎるってことさ。";
					link.l2.go = "saga_38";
					link.l3 = "覚えていますよ、ロクスリー旦那。少し後で持ってきます……";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "私のサービスが必要ですか、旦那？ご満足いただけることをお約束します。";
				link.l1 = "ありがとうございます、でも今は必要ありません。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "旦那、あんたは海に出すぎたんじゃねえか。イスラ・テソロは今やイギリス海軍の軍事基地だぜ！\nああ、シャープの遺言状は確かに存在するが、もう効力は切れていて、 イスラ・テソロはイギリス王室の所有になっちまったんだ。残念だがな！";
				link.l1 = "なんてこった！俺の努力は全部無駄だったみてえだな……";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "あのご婦人が島全体の所有者だと主張しているのか？ふむ……これは簡単にはいかない話のようだな。イスラ・テソロは、もうほとんどイギリスの植民地になりかけている……";
				link.l1 = "まだだ。遺言状によれば、地図の両方の断片を持参した男か女がイスラ・テソロの所有者になるんだ。 俺たちはシャープの地図の両方の断片を持っている。これが相続の主な証拠だ。";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "ニコラ・シャープ……ほう、ほう。私は資料室に行って、イスラ・テソロに関する資料を調べておかねばなりません。地図は持っていますか？";
			link.l1 = "持っていますが、契約書に署名した後でしか渡しませんよ。\nそれで、あなたの報酬の額はどうしますか？";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "言った通り、簡単にはいかないぜ。お前が証明しなきゃならねえのは、ただのボロ船や小屋じゃなくて、 島全体の所有権だ。それに、ニコラス・シャープは海賊だったし、海賊やその身内を助けるのは骨が折れるんだよ。"+sTemp;
			link.l1 = "実際の金額を教えてくれるのか？";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "旦那、最終的な金額は裁判の際に決まります。まだどれほど厄介になるか分かりません。しかし、 前金の見積もりはできます―― "+sTemp+" ドゥブロン金貨だ。この金額の支払いは、商売の成り行き次第であと一度か二度必要になるだろう。\n一週間以内に金を持ってこい。記録を調べて準備する時間が必要なんだ。その後で取り決めをしよう。いいな？";
			link.l1 = "諸島で一番の弁護士だと推薦されたから、これで取引成立だ。\n一週間後に会おう！";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "よろしい。あなたの案件を引き受け、法廷であなたの利益を代表する準備はできています。さて、本題に入りましょう。 私は公文書館でうまくやり、重要人物とも話をつけました。シャープの遺産の件は簡単にはいきません。 地図の両方の断片を手に入れたのは良いことです。しかし、それだけでは足りないかもしれません。\nドイル大佐はトルトゥーガの支配に失敗したため、イスラ・テソロに大きな計画を持っています。 あの島は天然の防御を備えており、この地域の将来の軍事基地になり得るのです。";
			link.l1 = "「でも、イギリスの法律によればエレンには島を相続する正当な権利があるんだ！」";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "シャープ故人が遺言に追加条項を設けたことはご存じないかもしれません。\n相続人は彼の姓を名乗らねばならないのです。\n私の記憶が正しければ、あなたの娘さんは別の姓でしたね。マッカーサーと言いましたよね？";
			link.l1 = "これは彼女の義父の姓だが、エレンにはシャープという名前を名乗る正当な権利がある。なぜなら、 彼女は故ビアトリス・シャープ、つまりニコラスの娘の娘だからだ。";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "素晴らしい！だが、それを誓って証言できる者は誰だ？エレンの養父母はベアトリス・シャープと面識があったのか？";
			link.l1 = "私の理解では、そうではなかったようです。マッカーサー旦那は彼女をグラディスの娘だと思っていましたが、 グラディスはその娘の父親と知り合いだっただけです。";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "それは残念ですね。実は、私は記録保管所でベアトリス・シャープに子供がいたという記述を見つけられませんでした。\n子供の出生が公式に記録されていない可能性もあります。誰でも自分がシャープの孫だと名乗って、 その姓を名乗る権利を主張できてしまいますからね。";
			link.l1 = "だが、地図の全てを持っているのはエレンだけだ！";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "これは彼女の切り札だが、もし地元当局がイスラ・テソロに対して独自の計画を持っていなければ、 これだけで十分だったかもしれない。ベアトリスの直筆で署名入りの書類が公文書館に保管されている。彼女が書いた、 娘が生まれた事実を証明できる書類を探す必要がある――その娘はあのグラディスに預けられた……ええと、あの女の姓は何だったかな？";
			link.l1 = "チャンドラー。ベリーズから来たグラディス・チャンドラー。";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "その通りだ。そういうものを見つける機会はあるか？";
			link.l1 = "それは疑わしいな。年月が経ちすぎている。伝説によれば、ブッチャー船長自身がエレンの父親かもしれないらしい。\nこのことについては、セントジョンズの元死刑執行人が何か知っているかもしれない。 彼はエレンの父親を生きて見た最後の男だったんだ。";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "ふむ。あいつは本当に面白い男だったな。確か名前はレイモンド・ベイカーだったと思う。一度だけ話す機会があって、 運が良かったよ。頭が良くて、教養もある男だった。さて、アンティグアで何か手がかりを探してみてくれ。 俺は引き続き記録を調べてみる。もしかしたら何か役立つものが見つかるかもしれない。";
			link.l1 = "いいだろう。俺はそれで構わねえ。";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "シャープの地図を渡せ、そして急げ。ベイカーと話せ、彼の助けで何か書類が見つかるかもしれん。 彼女の出生の証拠さえ見つかるかもしれないぞ。";
			link.l1 = "ああ、できればそうしたいけどな。まあ、じゃあな、ロクスリー旦那。";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "そうか？この証拠を見せてもらおう。";
			link.l1 = "これはベアトリス・シャープが兄に宛てて書いた私的な手紙だ。\nここには、彼女が娘を出産し、その父親が実はローレンス・ベルトロープだったと書かれている。\nその少女はグラディス・チャンドラーという若い未亡人に預けられた。\nローレンス・ベルトロープは「ブッチャー船長」としても知られている。\nほら、この手紙を受け取ってくれ……";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "グラディスはそれを宣誓の上で証言する用意がある。\nまた、父親が自らをブッチャー船長と名乗ったことも証言するつもりだ。";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "ちょっと待て！悪名高い海賊であり、イギリス臣民の殺し屋だったブッチャー船長は、 二十年前にセント・ジョンズの砦で絞首刑にされたはずだ。それに、 リチャード・ドイルの親友だったローレンス・ベルトロープも、つい最近悲劇的に亡くなった。そして何より、 ドイルは彼をシャープタウンの新しい総督にしようとしていたんだ！";
				link.l1 = "はっ！そりゃあ、誰も知らねえだろうよ……だがな、俺はセントジョンズの元死刑執行人レイモンド・ベイカーの書いた証言を持ってるんだ。奴は、 確実な死をちらつかされてブッチャーの処刑を偽装するよう強制されたってよ！ほら、これを見てみな……\n";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "待てよ！ブッチャー船長――あの悪名高い海賊であり、イギリス臣民の殺し屋は、二十年前にセント・ジョンズの砦で絞首刑になったはずだ。\nそれにローレンス・ベルトロープは生きていて、ポートロイヤルの一等地の屋敷に住んでいる。\nさらに言えば、ドイルは彼をシャープタウンの新しい総督にしようとしているんだ！";
				link.l1 = "はっ！そうだな、誰も知らねえよ……だがな、俺はセント・ジョンズの元死刑執行人レイモンド・ベイカーの書面証言を持ってるぜ。 やつは死をちらつかされてブッチャーの処刑を偽装するよう強制されたってな！ほら、これを見てみろ……\n";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "ふむ。ほう、ほう……";
			link.l1 = "なかなか巧妙じゃねえか？ブッチャー船長は生き延びてイングランドに戻ったんだ。 名前を元のローレンス・ベルトロープに戻して、こっそりここへ帰ってきたのさ。";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "だが、これは……これはすべてを変えるぞ！ベアトリスの手紙を公表すれば、 これまでずっと軍政総督が逃亡中の海賊ブッチャーを匿っていたことが明るみに出る。ブッチャーは本来、 見つけ次第逮捕され、過去の罪で裁判にかけられるべきだったのに！\nさらにベイカーの証言があれば、反論の余地は完全になくなる！これは見事だ！こんな切り札があれば、ドイルを堂々 と打ち負かせるぞ！";
			link.l1 = "嬉しいぞ。この試練でお前に期待している。それと、教えてくれ、ローレンス・ベルトロープはどうやって死んだのだ？";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "これは不気味な話ですよ、旦那。彼は自分の寝室で、顔を歪めたまま発見されたんです。あの恐れ知らずの男が、 いったい何にそこまで怯えたのか想像もつきません。霜に覆われていたとも言われています。 体中には恐ろしい裂傷があったのに、床には血の一滴も落ちていなかったんです！想像してみてください！一滴も、 ですよ！\n";
			link.l1 = "ああ、それはまるで悪夢そのものだな。\n殺されたようだが……一体誰がそんなことを？";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "分かりません。あまりにも複雑すぎて……。守備隊の医者は、彼の傷は致命的ではなかったと言っていました。ベルトロープは恐怖や痛み、 あるいは別の何かで死んだのです。いずれにせよ、これは不可解な死です。";
			link.l1 = "なるほど……それで、裁判はいつ始まるんだ？";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "すべてはあなた次第です、旦那。私への報酬の後半分、つまり450ドゥブロンを支払っていただければ、すぐに書類を裁判所に提出します。\nその一週間後にはエレンが権利を得ることになります。";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "承知した。これが君のドゥブロンだ。";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "はい、もちろんです。ご必要な金額をお持ちいたします。";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "旦那、あなたには驚かされましたぞ！あなたは多くのことを成し遂げてくれた、島はほとんど我々の手中にあったのに、 あなたが私への報酬を遅らせたせいで全てが水の泡だ！\n遺言状の効力は切れ、今やイスラ・テソロはイギリス王室のものになった。軍事基地になるだろう。";
				link.l1 ="おったまげたぜ！俺の努力は全部無駄だったみてえだな……";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "「俺の報酬の後半分、持ってきたのかい、旦那？」";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "はい、もちろんです。こちらがあなたのドゥブロンです。";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "記憶が悪くて申し訳ありません、船の箱に置き忘れてしまいました。すぐに持ってまいります。";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "しかし、これは……これは全てを覆すぞ！ベアトリスの手紙を公表すれば、ローレンス・ベルトロープは直ちに逮捕され、 過去の罪で裁判にかけられねばならん！\nさらにベイカーの証言があれば、反論は完全に崩れる！素晴らしい！こんな切り札があれば、ドイルに正々堂々 と勝てるぞ！";
			link.l1 = "とても嬉しいです。裁判はいつ始まりますか？";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "素晴らしいですな、旦那。お取引できて光栄です。さて、話はこうです。明日またここに来てください。そう、そうです、 聞き間違いじゃありません――明日です！何しろ私はこの諸島一の弁護士で、コネもありますからな。\n依頼人も連れてきてください、彼女なしでは裁判は始まりません。遅刻せず、街からも出ないように。 そして可能なら最後の支払い分も持ってきてください。勝利は間違いないと確信していますよ。";
			link.l1 = "よろしい。明日、ロクスリーさんの執務室に伺います。";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "マッカーサー？いや、シャープだ！さあ、俺について来い！";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "お祝いを言わせてください、旦那、そしてあなたの主君にも。 これで彼女は正当にイスラ・テソロの支配者となりましたね。これはシャンパンで乾杯する価値がありますよ！\n";
			link.l1 = "もちろんです、ロクスリー旦那。あなたの弁論は実に見事でした。 ローレンス・ベルトロップがブッチャー船長だと法廷で言ったとき、ドイル大佐が心臓発作を起こすかと思いましたよ。";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "ああ、ドイル旦那はイスラ・テソロに軍事基地を作る夢とお別れしなきゃならねえな。\nでもどうしようもねえさ。法は法、誰にでも適用されるもんだ、あの立派な大佐だって例外じゃねえ。";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "書類はすべて揃っているのか？それに、ヘレンの島の権利をちゃんと証明しているのか？";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "判事がローレンス・ベルトロップの逮捕を命じたと聞いた。\nつまり、彼は絞首刑になるということか？";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "かしこまりました、旦那。すべての文にあるコンマを確認いたしました。間違いなく正しいものでございます。";
			link.l1 = "「よろしい……」";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "さて、私の仕事は終わりました。今回の案件は厄介でしたが、我々は共に勝利を収めました。さて、旦那、 あとは私の報酬の残りをお支払いいただくだけです。ご無理は申しません、お忙しいのは承知しております。しかし、 残りの450ドゥブロンを一週間以内にお持ちいただけると信じております。\nそれに、旦那のようなお客様には、いつでも大幅な割引をご用意しております。私はきっとお役に立てますよ。 諸島のすべての首都、敵対的な場所でさえもコネがありますので、どんな法的な問題でも解決できます。";
			link.l1 = "素晴らしい。これで誰に聞けばいいか分かった。";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "どんなに厳しい状況でも、私が必ず有利な結果をお約束いたします。";
			link.l1 = "いいね。もう行かなくちゃ、ヘレンと俺にはやることが山積みなんだ。";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "さようなら、旦那。";
			link.l1 = "さようなら、Loxleyさん。";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "そうだな、あいつはブッチャー船長、海賊であり盗賊だ。\nだが今はポートロイヤルにはいない。運良く逃げ延びて、島の奥地へと移動したんだ。\nだが狩りは始まったし、きっと捕まるだろう。";
			link.l1 = "なるほど……書類はちゃんと揃っているのか？";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "素晴らしい！お取引できて光栄です、旦那！今後はどんな用件でも私に頼めば割引いたしますよ。法の問題でも、 賞金首になっても……ご遠慮なく。いつでもお会いできるのを楽しみにしています。";
			link.l1 = "できれば最初から面倒ごとには関わりたくなかったが……まあ、色々あるさ。ありがとう、そしてさようなら、ロクスリー旦那。";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "どういう意味だ、旦那？俺たちの約束を破るつもりか？";
			link.l1 = "その通りだ。ほとんどの仕事は俺がやったんだぜ。証拠を手に入れるために何をしたか、 あんたには想像もできねえだろう。それなのに、あんたは書類を持って裁判所に行っただけじゃねえか。 九百ドゥブロンなんて十分すぎる額だ、俺はそう確信してるぜ。";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "お前、まるで海賊みたいな口ぶりだな、旦那！まあ、四百五十ドゥブロン失っても俺が貧乏になるわけじゃねえが、 お前も大して儲かりゃしねえさ。実際、お前はもっと大きなものを失ったばかりだぜ！そして、 これから先も何かを失うかもしれねえ……さっさと俺の家から出ていけ、二度とここに顔を出すんじゃねえぞ！";
			link.l1 = "そして、私はそれをやるつもりだ。さようなら、ロクスリー旦那。";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "お前と話したくねえ。さっさと失せろ、さもねえと衛兵を呼ぶぞ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "旦那、もっと早く私のところに来てくだされば、あなたの件は勝てたでしょうに。遺言状の効力は切れてしまいました。 申し訳ありません。";
			link.l1 = "えっ、私はもっと申し訳なく思うよ！では、ごきげんよう、ロクスリー旦那。";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+"「旦那。お会いできて嬉しいです。私のサービスが必要ですか？」";
			link.l1 = "はい。だからこそ私がここにいるのです。";
			link.l1.go = "loxly_1";
			link.l2 = "いや、幸い今のところ必要ないんだ。ただ挨拶したかっただけさ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "あなたの話を聞く準備はできています。どんな助けが必要ですか？";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "私はイギリス当局に困っている。";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "私はフランス当局に追われているんだ。";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "私はスペイン当局に目をつけられているんだ。";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "俺はオランダ当局に目をつけられてるんだ。";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "俺は密輸業者たちと喧嘩したんだ。";
				Link.l5.go = "contraband";
            }
			Link.l7 = "申し訳ない、考えが変わったんだ……";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "すでにあなたの件には取りかかっております。大丈夫です、ご安心ください。";
			Link.l1 = "ありがとうございます。お待ちしております。";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iLoxlyPseudoGlobal = CalculateRelationSum(i, true);
			int iRate = abs(ChangeCharacterNationReputation(pchar, i, 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" ～と一緒に "+XI_ConvertString(Nations[i].Name+"Abl")+"。代金がかかるぜ "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(pchar.money) >= iLoxlyPseudoGlobal)
			{
				link.l1 = "よろしい、ロクスリー旦那、同意します。これがあなたの金だ、できるだけ早く片付けてくれ。";
				link.l1.go = "relation";
			}
			link.l2 = "今はあんたの言う金額は持ってないんだ。また後で来るぜ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			i = sti(npchar.quest.relation);
			dialog.text = "お取引できて光栄です、旦那。これでまた安心して呼吸できますね。あなたの問題は今後二週間以内に解決します。 どうか、誰とも争いを避けてください。 "+XI_ConvertString(Nations[i].Name+"Abl")+"「交渉の真っ最中なのに。」";
			link.l1 = "わかった、忠告は肝に銘じておくよ。ありがとう、それじゃあな！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			iLoxlyPseudoGlobal = CalculateRelationContraSum(true);
			dialog.Text = "「それで、なぜそんなことをしたんだ？密輸業者たちはいい奴らだぜ、自分なりに誠実なんだよ。 みんな生きて食わなきゃならねえからな……まあ、たいしたことじゃねえし、お前にかかるのはたった」 "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(Pchar.money) >= iLoxlyPseudoGlobal)
			{
				Link.l1 = "よろしい、ロクスリー旦那、同意します。これがあなたの報酬です、できるだけ早く事を片付けてください。";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "今はあんたが求めてる金額は持ってないんだ。また後で戻ってくるぜ！";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "素晴らしい、私があなたの問題を解決します。すぐにまた取引したいと思うはずです。";
			Link.l1 = "ありがとう！";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
