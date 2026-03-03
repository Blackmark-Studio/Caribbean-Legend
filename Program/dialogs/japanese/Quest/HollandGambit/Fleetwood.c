// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "ごきげんよう、船長！俺の見た目に惑わされるな、俺は大丈夫だ――ほとんど目が見えねえが、まだまだ元気だ。自己紹介させてくれ。俺はリチャード・フリートウッドだ。";
					link.l1 = "ごきげんよう、お会いできて光栄です。私は船長です "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "お前に船を係留しろと言っただろう。俺の話、ちゃんと聞いてるのか？";
						link.l1 = "ああ、もちろんだ。俺がちゃんとやっておくぜ。";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "さて、また来たな。『ヴァルキュリア』の指揮を執れ――乗組員には詳細を伝えてある――そしてブリッジタウンへ向かうんだ。市内の重要人物全員を訪ねて、例の噂を広めろ。それから、 あの野郎が襲ってくるのに備えておけ。船を変えたり、艦隊を組んだりするなよ、罠だと疑われて現れなくなるぞ\nやつの船に乗り込んで、セント・ジョンズまで曳航しろ。必ず海賊の航海日誌を見つけ出せ。 あれだけがルーカス・ローデンブルクの関与を示す唯一の証拠だ。お前ならきっとやり遂げてくれると信じている。 幸運を祈るぞ、船長。";
						link.l1 = "ありがとう！約束通り仕事をやり遂げるよ。";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "お帰りなさい、船長……あなたの航海についてはすでにすべて聞いております。";
						link.l1 = "そうか？なら、知ってるはずだな……";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "戻られましたね、船長…。あなたの航海についてはすでにすべて聞いております。";
						link.l1 = "そうか？なら、知っているはずだな……";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "戻られましたね、船長…。あなたの航海についてはすでにすべて承知しております。";
						link.l1 = "知っているのか？それなら……";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "戻られましたね、船長…。あなたの航海についてはすでにすべて承知しております。";
						link.l1 = "そうか？じゃあ、知ってるはずだな…";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "やあ、友よ！会えて嬉しいぜ！お前の船にアビゲイルはいるか？";
					link.l1 = "残念ながら、リチャード、私は知らないんだ。彼女は一緒に来るのを断ったよ。父親がすでに全財産を失っていて、 彼女が去ることは父親にとって大きな打撃になるからだ。だから私はこの問題を自分で解決し、 ソロモンの財宝とその島を見つけることに決めたんだ…";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "他にご用はありますか、船長？";
				link.l1 = "いや、もう出発するところだ。";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "他にご用はありますか、船長？";
				link.l1 = "いや、もう出発するところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "くそっ、海賊め！白兵戦には負けたが、俺は最後まで任務を果たすぞ。火薬庫に火をつけるよう手配してある、 この船もお前の“幽霊船”もすぐに吹き飛ぶだろう。お前ごときにイギリス船を沈めさせはしない。俺は誇りを持って死ぬ！";
			link.l1 = "がっかりさせて悪いが、フリートウッド、お前は間違ってる。俺の船に海賊はいない。前にも奴らは片付けた。 俺にはお前が必要だったし、この船は完璧な罠になったんだ。\nもう挨拶は十分だ。これからお前を殺して、この燃えるボロ船から脱出しなきゃならねえ！";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "チャーリーからすでに敵の交易隊を見事に拿捕したと聞いている。お会いできて嬉しい、 イングランドには君のような勇敢な船長が必要だ。さて、非常に重要な話をしよう。";
			link.l1 = "お聞きします、フリートウッドさん。";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "ある海賊が諸島中で暴力行為を働いており、「フライング・ダッチマン」という伝説の幽霊船になりすましている。 彼は伝説の幽霊船「フライング・ダッチマン」を装っているが、私は彼がオランダ人だと確信している。しかし、 空を飛ぶことはできない。どうやらこれは、 オランダ西インド会社副総裁ルーカス・ローデンブルクの傭兵だと私は思っている。\nローデンブルクはイングランドに対して密かな経済戦争を宣言しており、この「幽霊船」 はイングランドの旗を掲げた商船だけを襲っている。本格的な戦争をせずに、この地域で我々 の影響力を弱めることが会社にとって重要なのだ。\n私はしばらくこの幽霊船を追っているが、船長は非常に経験豊富な航海士で、船も素早くて捕まえにくい。\n正面から戦ってもこのジャッカルを捕まえるのは不可能だから、こちらも狡猾に動くしかない。最近の私への暗殺未遂も、 我々にとっては好都合だ。どう思う、船長？怖じ気づいたか？";
			link.l1 = "無理だな。喜んでこの野郎を追い詰めて沈める手伝いをしてやるぜ。どうせそれを頼もうとしてたんだろ？";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "その通りだ。さて、詳細について話そう。俺の部下たちが、俺が死の床にあるという噂と、俺の船『ヴァルキリー』 をお前に売ったという話を広める。次に、我々のちょっとした策略を実行するぞ。お前は俺からブリッグ船を買い、 大砲のほとんどを処分した商人のふりをするんだ。\nだから、お前の任務はバルバドスへ航海し、そこにいる連中全員に、自分の船倉が貴重な積荷でいっぱいで、 懐も金で溢れていると吹聴することだ。まもなく出航するつもりだと伝えろ。 欲深くて単純だが金持ちの商人を演じるんだ。\nあの忌々しいオランダ野郎は、ブリッジタウンから交易船の情報を得ている。 誰が奴に情報を流しているのかは分かっていない。地元の商人から総督まで、全員が疑われているが、 後者だったら恐ろしい話だ。\n俺の『ヴァルキリー』とその乗組員を指揮しろ。ただし、まずはお前の全ての船をここに置いていけ。 港長にはもう話を通してある。旗艦一隻につき月一万ペソかかるぞ。\nそれが済んだら俺のところに戻ってこい、手配を進める。ああ、船長、銀の護送隊を捕らえた分の取り分と、 港長への一万ペソを忘れるな――金はタンスの中に入っている。";
			link.l1 = "分かりました、フリートウッドさん。これから港長に会いに行きます。";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "ああ、君が海賊船拿捕の任務に失敗したことは承知している。私の計画はすべて台無しだ。君から『ヴァルキリー』 を没収する。もう行ってよい、君の助けはこれ以上必要ない。";
			link.l1 = "本当に申し訳ありません。それでは、フリートウッドさん、さようなら。";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "ああ、「ヴァルキリー」を失ったことは承知している。まったくもって容認できないことだ……拿捕した海賊船は私が没収する。もう行っていい、君の助けは必要ない。";
			link.l1 = "申し訳ありません。それでは、フリートウッドさん、さようなら。";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "ああ、お前が珍しいほどのドジで間抜けだってことは知っている。海賊船も拿捕できず、俺の『ヴァルキュリア』 まで失った。お前には本当に失望した。出ていけ！";
			link.l1 = "本当に申し訳ありません。それでは、フリートウッドさん、お元気で。";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "ああ、計画がうまくいったことは承知している。悪党の海賊を始末し、奴の船も手に入れたそうだな。 あの船の本当の名前は何だ？";
				link.l1 = "Mirage";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "ああ、君が我々の計画を成功させたことは知っている。悪党の海賊を始末し、その船も手に入れたな。私の『 ヴァルキリー』号は返してもらうが、海賊船は戦利品として君にやろう。それが…ある種の補償にもなるだろう。港に停泊していた君の船は、埠頭の火事が広がったせいで焼けてしまった。 不便をかけて申し訳ない。 "+pchar.name+"…幽霊船があなたの役に立つことを願っています。\n新しい船のしつこい汚れや海藻はすべて掃除するよう命じておきました。さらに、 最高級の綿で作った新しい帆も張らせます。\n最後に、報酬として10万ペソとこの航海用具をお受け取りください。ずっとこれをふさわしい船乗りに贈りたかったのです。 あなたは見事な働きをしてくれました！さて、そろそろお別れの時です。こちらでの用事は済みましたので、 ヨーロッパへ戻ることにします。幸運を祈ります、船長！";
				link.l1 = "リチャード、お前もな！";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "蜃気楼？実にふさわしい名前だと思うよ……俺はお前から自分の『ヴァルキュリア』を取り戻すつもりだ。だから、海賊船は戦利品としてくれてやる。 それが一種の補償にもなるだろう。港に停泊していたお前の船は、埠頭の火事が広がって燃えてしまった。すまないな。 "+pchar.name+"…幽霊船があなたの役に立つことを願っております。\n新しい船は、しつこい汚れや海藻をきれいに掃除するよう命じておきました。それに、 最高級の綿で作った新しい帆も張らせます。\n最後に、報酬として十万ペソとこの航海用具を受け取ってください。私はずっと、 ふさわしい船乗りにこれを渡したいと思っていました……よくやってくれました、あなたを誇りに思います！あの野郎の航海日誌は持っていますか？";
			link.l1 = "はい、もちろん。これです、どうぞ。ちょっと聞きたいんだが、ルーカス・ローデンブルクの手下の中に……アジア人はいるか？";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "ああ、いるぜ。中国人のロンウェイ、自分の船『メイフェン』の船長だ。あんた、海賊の航海日誌でそれを読んだのか？ ちょっと見せてくれ……（読みながら）ほうほう、やっぱりな。ルーカス・ローデンブルクが全部の黒幕だったか！まあ、どうでもいいさ、 今は俺たちの問題じゃねえ……我らが総督がこの野郎を始末してくれるさ。ルーカス・ローデンブルクは自分のやったこと、全部責任を取らされるぜ！";
			link.l1 = "ふむ、面白いな。で、イングランドの総督はどうやってオランダの臣民を「処理」するつもりなんだ？";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "政治的な駆け引きはいつもあるものだよ、親愛なる友よ……オランダはイングランドに対して貿易戦争を仕掛けたことを認めなければならないが、そうする可能性は低い。代わりに、 全ての責任をローデンブルクに押し付けるだろう。ルーカスは地位を失うかもしれないし、そうでないかもしれない。 どちらにせよ、彼の経歴には大きな打撃となる。\nだが、これは今や我々の関知することではない、船長。あなたは自分の役目を立派に果たした。だからこそ、 もう一つ非常に繊細な依頼があるのだ。";
			link.l1 = "聞いているぞ、リチャード。今回はイングランド王冠の次なる敵は誰だ、誰を滅ぼすんだ？";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "いいえ、今回はもっと個人的で平和的な件を頼みたいのです。短い話をさせてください――ちなみに、あなたの『ミラージュ』に関することですよ。";
			link.l1 = "続けてくれ。";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "俺があんたと会う一月前、幽霊船を追って襲撃に出てたんだ。場所はマルティニークの南、東経64度41分の近くだ。どこか遠くで戦闘の音が聞こえたが、風が弱すぎて間に合わなかった。イギリスのフルート船が、 地図にも載っていない小島の近くで幽霊船に沈められたんだ\n海賊を捕まえ損ねた俺は、生存者がいないかとその島に寄ってみた。そこで見つけたのが、ユダヤ人の難民親子、 父と娘さ。娘の名はアビゲイル、しかもとびきりの美人だった！まるで生きた奇跡だ……俺は二人を船に乗せてキュラソーまで送り届けたが、父親のソロモンは俺にあまり好意を見せなかった\nどうやら彼は、俺が自分たちの船を沈めた海賊だと思い込んでいたらしい。 あの老人は船のことも違いもよく分かってなかった。その短い航海の間に、俺とアビゲイルは友達になった――いや、正直に言えば恋に落ちたんだ。どうだ、面白い話だろ？\nそして最近になって、あのローデンブルクの野郎が、俺のアビゲイルにちょっかいを出していると知ったんだぜ。 考えてもみろ！俺は、彼女の父親が失った金の件を片付けたら、ここに連れてくるつもりだった。 あの島に全財産を隠していたらしいが、場所はどうしても突き止められなかった。もうこれ以上待てない\n俺自身はまだ体調が悪くて航海できないから、あんたに頼みたい。ウィレムスタッドに行って、 アビゲイルを見つけてここまで連れてきてくれ。俺の名前を出せば、彼女はあんたを信じるはずだ。";
			link.l1 = "この件については何の問題も見当たりません。今すぐ出航する準備ができています。";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "素晴らしい！君を頼りにできて嬉しいよ。 "+pchar.name+"。君の働きには十分な報酬を払う、そこは心配いらない。";
			link.l1 = "あまり待たせないよ。すぐに会おう、リチャード！";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+"、本当にその島を探す決心をしたのか？あなたの寛大さには感心するよ。見つけられたのか？";
			link.l1 = "ああ、行ったよ。だが、ここからが悪い知らせだ。あの忌々しい場所から命からがら逃げ出したんだ……今でも思い出すと震えが止まらねえ……";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "何があったんだ？教えてくれ、友よ、じらさないでくれ！";
			link.l1 = "私は島に来て、ソロモンが宝箱を隠したと思われる洞窟へ向かった。\n本当にそこにあった。\nだが、箱に触れた瞬間、何か得体の知れない力に吹き飛ばされた。\n爆発音がして、宝箱から三メートルほど離れた地面に叩きつけられた……";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "信じられない！";
			link.l1 = "俺はかろうじて生き延びたんだ――痛い傷も負った。\n意識が戻りかけたとき、頭の中で恐ろしい音が鳴り響いて、あの忌まわしい化け物が地面から現れたんだ……ああ神よ、あの怪物め！";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "リチャード、私は正気だ。自分でも信じがたいが、本当に起こったんだ。頭に羽飾りをつけた、 完全に干からびて塗装されたインディアンの死体だったんだ。その化け物が何かつぶやいてから、 でかいインディアンの棍棒を抜いて俺に襲いかかってきたんだ！";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "なんてことだ……あんな化け物にどうやって対処できたのか、今でも自分で分からない……何度も何度も斬りつけたのに、普通の人間なら十二人は死んでるはずなのに、あいつはまだ立っていた……息を整えてから、あの忌まわしい箱を開けてみた……中に金はなかったが、別のものが入っていたんだ。\n見てくれ、とても興味深い品だぞ！";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "ぶるぶる……ひどい……"+pchar.name+"「待て……間違いない、あいつだ！俺を殺そうとして胡椒で目を潰そうとした野郎の首だ！」";
			link.l1 = "あいつを知ってるのか？名前はガストン、ブリッジタウンの酒場の主人で、幽霊船の船長ヴァン・ベルクの支持者だ。 俺はすぐに彼だと分かったが、誰が殺したのか、 どうやってあの切り落とされた頭があの無名の島のソロモンの箱に入っていたのかは知らねえ！";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "おっしゃる通り、本当に不気味で謎めいた話ですね。神秘的だ……";
			link.l1 = "その通りだ。金がなくなった以上、アビゲイルの元へ戻る意味はなかった。だからこそ、こうしてお前に伝えに来たんだ。 \nもしかしたら、お前なら、この混乱を理解できるかもしれない、リチャード……";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "俺か？ここじゃ何も分からねえよ、お前と同じさ…だが一つだけ確かなことがある――嫌な予感がするんだ…"+pchar.name+"、今から俺の話を聞け。ブリッジタウンに行って、ガストンが本当にいなくなったか確認してくれ。それから、20日後にキュラソーのブランカ・ラグーンに来てほしい。チャーリー・クニッペルがそこでお前を待っている。 俺はアビゲイルの父親のために金を集める。それをチャーリーに渡すから、お前はそれをソロモンに届けて、 アビゲイルをアンティグアに連れて行くんだ。今回は邪魔は入らない、そう理解してくれ。行け、相棒！";
			link.l1 = "わかった、リチャード。すぐに出航する。";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "お前が俺のアビゲイルをさらったろくでなしだな。チャーリーも戻ってこなかったし、それもお前のせいに違いねえ。";
			link.l1 = "おっしゃる通りです、フリートウッド旦那。私でございます。チャーリーが、旦那がアビゲイルに書いた手紙のおかげで、 彼女の信頼を得る手助けをしてくれました。\nさて、本題に入りましょう……金は持ってきましたか？";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "ある。だが、まずはアビゲイルに会いたい。彼女が生きていて無事だと自分の目で確かめなければならない。 ろくでなしの言葉なんぞ信用できねえからな。";
			link.l1 = "旦那、今のあなたに条件を突きつける立場じゃないと思いませんか？";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "もうこの遊びはやめだ。アビは俺と一緒にいる、そしてお前はこの浜辺に取り残されるんだ！撃て！";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "それは分かっているが、俺だって馬鹿じゃねえ。アビゲイルに会うまでは金の話はしねえぞ。\nそれで？俺は待ってるぜ。";
			link.l1 = "よろしい。さて、本音を明かす時が来ましたな、フリートウッド船長。 私がここで会談を設けたのは金のためではありません。まあ、もちろん金も欲しいですが、まずはあなたが必要なのです。 ";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "俺か？これはますます面白くなってきたな……ようやくここで何が本当に起きているのか、わかり始めた気がするぜ。教えてくれ、アビゲイルは生きているのか？ あいつは無事なのか、それともお前が殺したのか、このろくでなしめ？";
			link.l1 = "彼女の運命については教えずにおこう。お前が知るべきことは一つだけ――彼女はここにはいない。彼女は自分の役割を見事に果たした、そして今、お前は俺の手の内だ。 愛とはなんと素晴らしいものだろうな……他にどうやって狐を巣穴からおびき出し、表に引きずり出せる？ハハハ！";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "まだ喜ぶんじゃねえぞ、この悪党め。この島でお前のために素敵な歓迎を用意してやったんだ、 誰が本当に仕切ってるかはまだ分からねえからな！だから覚悟しろ、話してもらうことが山ほどあるぜ――アビゲイルのことも、チャーリーのことも。あいつらを傷つけた分、きっちり償わせてやる！";
			link.l1 = "もう怖くて震えてるぜ！話はここまでだ、旦那。地獄に行く覚悟をしろよ、天国にお前の居場所なんてねえからな。";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
