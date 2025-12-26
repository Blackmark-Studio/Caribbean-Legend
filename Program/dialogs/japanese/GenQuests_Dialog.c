void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "これはバグだ。開発者に連絡して、どのように、どこで見つけたかを知らせてくれ";
					link.l1 = RandSwear()+"知らせてやるぜ！";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "俺にはお前と交渉する権限はねえ。うちの士官に話せ。";
					link.l1 = LinkRandPhrase("もちろん……","なるほど。","もちろんだぜ！");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "名を名乗れ！俺が誰と話してるのか知りてえんだ！";
					link.l1 = "俺の名前は "+GetFullName(PChar)+"。ここで何が起きてるんだ？";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "船長、お前の名前は "+GetFullName(PChar)+"、そうだろ？";
					link.l1 = "ああ、その通りだ。";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "違うぜ。俺を誰かと勘違いしてるんじゃねえか。";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+"、本当にありがとうございます！あなたがいなければ、俺の運命は悲惨なものになっていただろう……どうやってお礼をしたらいいんだ？";
					link.l1 = "俺は何もいらねえ……";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "小さな報酬なら断らねえぜ。";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "「……ふむ、確かにあいつだな……ありがとう。」 "+GetSexPhrase("野郎","娘")+"、あんたの助けがなけりゃ、俺たちは大変な目に遭ってたぜ。町から抜け出す手立てもなかったんだ。ほら、受け取れ\n "+FindRussianMoneyString(iMoney)+" さっさと失せな。俺たちは仲間と“話”でもしてくるぜ……";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "「……ふむ、確かにあいつだな……ありがとう、」 "+GetSexPhrase("野郎","娘")+"、あんたの助けがなけりゃ、俺たちは大変だったぜ、町から抜け出す手立てがなかったんだ。ほら、受け取れ\n "+FindRussianMoneyString(iMoney)+" さっさと失せな。今からこの汚ねえ裏切り者の腹を裂いてやるぜ！";
						link.l1 = "もちろんだ。また会おうぜ、旦那たちよ…";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "「何だと！？いや、誰であろうと人殺しなんて許さねえ……それに、てめえの血塗れの金なんざいらねえよ！」";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "ほう……ここにいるのは何だ？海賊か！？お前らには司令官の執務室まで同行してもらうぜ、尋問のためにな……";
					link.l1 = "俺たちは全然海賊なんかじゃねえ！この男のことも知らねえよ！こいつはこの部屋を借りて引っ越してきたばかりで、 俺は荷物をまとめて出ていく暇もなかったんだ！";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "で、何を言おうとしてたんだ？俺に伝言があるのか？！待ってるぜ！";
					link.l1 = "「ほらよ……」";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "おい、そこのあんた！そう、あんただ。あんたはまともで金持ちに見えるぜ。";
					link.l1 = "お前についてはそうは言えねえな。";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "待てよ！おい、 "+GetSexPhrase("相棒","娘")+"「さあ、お前の財布がどれだけ重いか見せてみろ！」";
					link.l1 = "それで、もう教会の金を全部使い果たしちまったのか？";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "おい、船の上！ひっく…航路を開けろよ、仲間たちと話があるんだ…";
					link.l1 = "ちょっとフラフラしてんじゃねえか、相棒？さっさと寝てこいよ。";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "おい、船長！錨を下ろせ！";
					link.l1 = "「それで俺がなんで……」";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "ちょっと失礼すぎじゃねえか！？";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("やあ、あなたに祝福を！ついに主が我らの祈りを聞き入れ、この見捨てられた岸辺に勇敢な船長を遣わしてくださった！","天のご加護に感謝だ！これでこの辺の死体漁りどもに俺たちの腐った骨を食われずに済むぜ！");
				link.l1 = "やあ、旦那、俺は船長だ "+GetFullName(PChar)+"。ここでずいぶんと困っているようだな。";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "旦那、俺には自分の用事があるんだ。あんたの面倒にかまってる暇はねえよ。";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("「ああ、船長！神様があんたに順風を与えて、この寂しい場所へ導いてくれたとは、本当に幸運だぜ！」","船長！この人けのない岸に錨を下ろしてくれて、天のご加護に感謝するぜ！");
				link.l1 = "やあ、旦那、俺は船長だ "+GetFullName(pchar)+"。ここは本当に大変な状況のようだな。";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "いいか、俺には自分の用事があるんだ。お前の面倒にかまってる暇はねえよ。";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("「待て、」 "+GetAddress_Form(pchar)+"！貴重なお時間を少しだけいただけませんか？","お嬢様が見逃すか"+GetSexPhrase("ター","ｓ")+" 「この取るに足らねえ俺たちのささやかな願いを聞いてくれるか？」","お嬢様"+GetSexPhrase("ター","ｓ")+"、どうか貴重なお時間を少しだけ、哀れな者の話に割いていただけませんか。");
				link.l1 = LinkRandPhrase("こんなことに付き合ってる暇はねえんだ。","消えろ、俺はお前なんかいなくてもやることが山ほどあるんだ。","俺に構うな、あんたにかまってる暇はねえんだ。");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("何の用だ？","何の用だ？","「どうしたんだ？」");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "よう、船長！普通の店じゃ手に入らねえインディアンの小物や品物に興味はねえか？それとも現金かい？";
					link.l1 = "お前みたいなガキどもは普通、要求ばかりで何も差し出さねえもんだぜ。どうして今日は妙に礼儀正しいんだ？";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "俺のピストルが、てめえみてえなクズにはいつも物を言わせてるんだぜ！";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "聞いてるぜ、船長。用事で来たのか？";
			link.l1 = "俺はミスターを探してるぜ "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("俺は旦那だ "+pchar.GenQuest.Hold_GenQuest.Name+"「……どなたにこの光栄を賜るのでしょうか？」","見つけたんだな。俺に何か用か？");
			link.l1 = "俺が船長だ "+GetFullName(pchar)+"、お前と話したいことがあってな "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "「それは誰だ？」";
					link.l1 = "待てよ……お前は "+pchar.GenQuest.Hold_GenQuest.Name+"、それについては知らねえのか "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "なんてこった！あの老いぼれ狐の話を聞くのは久しぶりだぜ。今度は何があったんだ？";
					link.l1 = "今回は本当に大変なことになっている……捕まって監禁されているんだ、君の助けが必要だ。";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "よし、全部聞かせてくれ。";
					link.l1 = "彼の船は海賊に襲われ、今は捕らわれの身だ。身代金の件であなたに会うようにと彼から助言された。";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "ああ、昔の友達の話を聞けて嬉しいぜ。あいつは元気にしてるのか？";
					link.l1 = "彼の状況はあまりにも悲惨で、想像するのも難しいほどだ。";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "ああ、そうだ "+pchar.GenQuest.Hold_GenQuest.Name+"！でも、そんなこと俺が知ってるわけねえだろ "+pchar.GenQuest.Hold_GenQuest.CapName+"?!";
			dialog.text = "そうだ、俺だ "+pchar.GenQuest.Hold_GenQuest.Name+"「！でも名前が "+pchar.GenQuest.Hold_GenQuest.CapName+" 何も教えてくれねえな。"; // belamour gen
			link.l1 = "申し訳ねえ。もしかして俺の勘違いだったかもな…";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "なんてこった！で、俺がどうやってあいつを助けりゃいいんだ？敵を全部ぶっ殺して解放しろってのか？ははは！";
			link.l1 = "いやいや、それは必要ねえ。渡すだけでいいんだ "+pchar.GenQuest.Hold_GenQuest.RansomSum+" 身代金としてペソだ。";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "なんて図々しいんだ！それに、なんで俺があいつの身代金を払わなきゃならねえんだ！？ あいつは俺の親戚でも友達でもねえぞ！";
			link.l1 = "ふむ……あんたが奴の唯一の希望だって言ってたぜ。それに、あんたの借金のことも話してたな……";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("なんて無礼な野郎だ！あいつが俺に借金してるんだぜ、念のため言っとくがな！だが、 だからといって両方の借金を返してもらうために身代金を払う理由にはならねえ。","なんて悪党だ！商売の分け前を分けるときに俺をだましやがって、今になって身代金を払えだと！？","そりゃ驚いたぜ！なんで俺があいつの身代金なんか払わなきゃならねえんだ！？別にそんなに親しいわけじゃねえ。");
			link.l1 = "つまり、あんたが身代金の支払いを拒んで、自分の借金を認めなかったって伝えていいんだな？";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "おやまあ！どの借金のことを言ってるんだい？もう全部説明したはずだよ！それに、 このくだらない話以外に質問がないなら、これで失礼させてもらうよ。";
			link.l1 = "なるほどな。まあ、お前にはもう聞くことはねえが、その仲間にはまだ色々と聞きたいことがあるぜ。";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "ふむ……それで、お前があいつを押さえてるってわけか……まあ、俺が手を貸してやるとするか。";
			link.l1 = "よし、身代金は "+pchar.GenQuest.Hold_GenQuest.RansomSum+" ペソだ。";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "俺の言いたいことを勘違いしてるぜ。俺は市議会の一員だ。俺たちは憲章の遵守を監督しているんだ。\n"+"衛兵！！衛兵！こいつを奴隷売買と船の略奪の容疑で逮捕しろ "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "さて、「相棒」、ちょっとお前のところに行かせてもらうぜ…";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "何を言ってるんだ！？それで、俺がどうやってあいつを助けりゃいいんだ？";
			link.l1 = "彼は捕らわれの身で、身代金についてあなたに話してほしいと頼まれた。";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "もちろんだ、もちろん。できる限りのことはやるぜ。どこに捕まってるんだ？それと、身代金はいくらなんだ？";
			link.l1 = "海賊たちが要求している "+pchar.GenQuest.Hold_GenQuest.RansomSum+" ペソだ。俺は金を港に届けなきゃならねえ、それが済んだらお前の仲間は解放されるぜ。";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "ほら、金だ。運よく手持ちが足りてたぜ。";
			link.l1 = "ああ、それは本当に運がいいな。じゃあ港へ行け、すぐに仲間にまた会えるぜ。";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "こんにちは、船長、まだご挨拶できていなくてすみません。俺を探していると聞きましたぜ。";
			link.l1 = "確かに、もしあんたが旦那なら "+pchar.GenQuest.Hold_GenQuest.Name+"。俺が船長だ "+GetFullName(pchar)+"、話がしたかったんだ。";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "それで、どんな用件なんだ、船長 "+GetFullName(pchar)+"?";
			link.l1 = "お前が手放しても構わねえ物を持ってるって聞いたぜ。";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "一体何が言いたいんだ？";
			link.l1 = "そんなに意地を張るなよ、旦那。お前のいかがわしい過去も、宝のありかを示す手作りの地図のことも、 全部知ってるんだぜ。"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" 示されている。";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "くそっ！あのろくでなしが、俺は最初からわかってたぜ"+pchar.GenQuest.Hold_GenQuest.CapName+" いずれはベラベラしゃべるに決まってたんだ！こんな取引を持ちかけるなんて、俺は何を考えてたんだ？";
			link.l1 = "もう泣き言はやめろよ。俺は危害を加えるつもりはねえ……この地図を売って、いつも通りの暮らしを続けりゃいいんだ。";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "それが本当ならどれほど安心できることか……で、俺にいくら払うつもりだ？あの箱にはたんまり金貨が入ってたのは知ってるだろう。四人がかりで運んでたんだ、 奴らの魂が安らかであるように……";
			link.l1 = "But "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" もう奴の財宝を手に入れていたかもしれねえ…";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "確かにそうだな……よし、あんたに売ってやってもいいぜ "+pchar.GenQuest.Hold_GenQuest.Sum+" ペソだ。俺はどのみち死者を邪魔するなんて怖くてできねえよ。";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "いいだろう。取引成立だ。";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "いや、旦那、その紙切れはこの金には値しねえよ。じゃあな……";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "こんなことがあり得るのか、船長！？こんな大罪、神様は絶対に許しちゃくれねえぞ。";
			link.l1 = "それはあいつが決めることだ。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("こんにちは、私は "+pchar.GenQuest.ShipWreck.Name+"の船長 "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" 「」"+pchar.GenQuest.ShipWreck.ShipTypeName+"、俺の船は岸からそう遠くない岩礁で座礁しちまったんだ。"+"乗組員全体のうち、ほんの数人の水夫だけが生き残ることができたんだ。潮に流されて、 この荒れ果てた岸に打ち上げられた。俺たちは飢えと渇きに苦しみ続けていたんだよ\n "+(5+hrand(7))+" もう何週間も前からだ","こんにちは、私は "+pchar.GenQuest.ShipWreck.Name+"の船長 "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" 「」"+pchar.GenQuest.ShipWreck.ShipTypeName+"。俺たちの船はここからそう遠くない場所で難破したんだ。"+"俺たちは難破のあとなんとかこの岸にたどり着いたが、ここはどうやら無人島らしい。 仕方なく貝やヤシの実で生き延びてきたんだが\n "+(5+hrand(7))+" もう何週間にもなるんだ。");
				link.l1 = RandPhraseSimple("「それで、お前たちはあと何人残ってるんだ？」","「それで、お前たちの中で生き残ったのは何人だ？」");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "ああ、船長、我々の被害は本当にひどい……初めまして、私は "+pchar.GenQuest.ShipWreck.Name+"、船長兼船主で "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" 「」"+pchar.GenQuest.ShipWreck.ShipTypeName+"。いや、元船長兼元船主と言うべきか。 "+"この野郎 "+pchar.GenQuest.ShipWreck.BadName+" 俺が雇ったのは "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" 俺の乗組員を反乱に駆り立てちまったんだ。結局、俺たちはこんな神にも見放された場所に置き去りにされたってわけさ。 そうなったのは "+(5+hrand(7))+" 数週間前だ。";
				link.l1 = "それでどうなったんだ？お前の船員全員が反乱者に加わったのか？";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("乗組員全員の中で、ただ "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" 生き残った者もいる。他の連中は死んじまった；何人かはここで傷や熱病で既に死んだんだ\n",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " 運が良かった方さ。ほかの連中は……深海か、この海岸の砂丘で最期を迎えたんだ。");
			link.l1 = LinkRandPhrase("ああ、それは哀れな運命だな。だが、それが水夫の宿命さ――誰だってお前の立場になるかもしれねえんだぜ。","なるほどな……神様はすべての命を握ってるが、忙しすぎて全員のことなんて覚えちゃいねえんだよ。","確かに。人事を尽くして天命を待つ、だな。");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "もちろん違う！反乱者に加わるのを拒んだ者も多かったが、あいつら悪党どもが武器庫を奪いやがったんだ。 もし俺たちが抵抗してたら、その場で殺されてたぜ。ここじゃもう多くの奴らが熱病や毒虫の毒で死んじまった、ただ\n "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" 生き延びた。ありがたいことに、俺たちの試練もついに終わったんだ。";
			link.l1 = RandPhraseSimple("ああ、まったく運が悪かったぜ。","まあ、こんな神に見捨てられた場所じゃ、いろんな奇妙なことが起こるもんだ。");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "待てよ、相棒。お前らが反乱を企てた張本人として上陸させられたんじゃねえって、どうやって俺が知るんだ？";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("船長、あんたの船に空いてるロッカーがいくつかあるといいんだがな。俺たち全員家族がいるし、 今こうして話してる間にも、きっと家族は俺たちの死を嘆いてるだろう。あんたには本当に感謝するぜ。","船長、俺たちはもう絶望のどん底だ、あんたが唯一の希望なんだ。頼む、見捨てないでくれ、 この神に見放された土地から俺たちを連れて行ってくれ。");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "「おう……で、どこへ連れて行きゃいいんだ？」";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("本当に申し訳ねえが、空いてるハンモックすら一つもねえんだ、ましてや船室なんてとんでもねえ。 水夫どもは甲板で寝てるし、見張りの後でもろくに休めやしねえんだよ……","本当にがっかりさせたくはないんだが、船は積みすぎで、みんな悪天候の中で寝なきゃならねえ。\nもし病気が流行ったら、乗組員の半分を失うことになるぜ。"),RandPhraseSimple("本当に申し訳ないが、俺の船には全く余分な乗組員のスペースがねえんだ。これ以上乗客を乗せることはできねえ。","残念だが、俺の船は積み荷でいっぱいなんだ。疫病が心配でな。"));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "お前はベテランの水夫だろうから、難破から生還した奴がいるってのはとんでもなく縁起が悪いって知ってるはずだ。 俺の船乗りどもはお前ら全員を海に放り投げるぜ。";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "何を言ってるんだ、 "+GetAddress_Form(npchar)+" "+pchar.lastname+"？！頼む、情けをかけてくれ！俺はカリブで有名な商人だったんだ！まあ……昔はな。今は船も金もなくて、ただの落ちぶれ者さ……";
			link.l1 = "どういうことだ……お前らが反乱の本当の首謀者だったんじゃねえのか、そして今は自業自得ってわけだ。";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "しかし、なんてろくでなしなんだ "+pchar.GenQuest.ShipWreck.BadName+"！本当にあいつの好き勝手を許して、お前の運命に従うつもりか？";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "どこの居留地へ "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "まあ、空いてる寝台とハンモックは十分あるぜ。さっさとボートに乗りな。";
					link.l1.go = "ShipWreck_10";
					link.l2 = "ふむ……これから戦いが待っているが、お前が俺の船の上にいる方が安全なのか、 それともこの居心地のいい入り江にいる方が安全なのか、俺には分からねえな。";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "ダンケルクへ！俺の母ちゃんがそこに住んでるんだ…";
					link.l1 = "頭でもおかしくなったのか！？頭を殴られすぎたんじゃねえのか…";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "どこでもいいさ、俺たちには関係ねえ。どうせ払うもんなんて何も持っちゃいねえからな……";
				link.l1 = "まあ、空のロッカーとハンモックは十分にあるぜ。さっさとボートに乗りな。";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "ふむ……これから戦いが待ってるが、お前が俺の船にいる方が安全なのか、 それともこの居心地のいい入り江にいる方が安全なのか、俺には分からねえな。";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "だが断れば、俺たちは確実に死ぬ運命だぜ！まあいい、命を賭けてでも船まで戦って突破してみせるぞ！";
					link.l1 = "なんだと？自分たちを見てみろよ、まともに立つこともできねえじゃねえか…";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "試してみるがいい…";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "しかし、ここに俺たちを置き去りにはできねえだろう！お前の助けがなきゃ、みんなすぐに死んじまうんだ！";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "俺ができることは、お前に十分な食料と薬を残して、小舟を渡すことだけだ。\n少なくとも飢えや渇きで死ぬことはねえだろう。\n航海術については、俺が教えるまでもねえよ。";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "俺ができるのは、お前に十分な食料と薬、それにボートを残してやることだけだ。\n少なくとも飢えや渇きで死ぬことはねえさ。\n航海術については、俺が教えるまでもねえだろう。";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "薬と弾薬、ラム酒、それに食料をひと月分は置いていけるぜ。\n俺が戻ってくるか、誰かを迎えに寄越すからな。";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "だが断れば、間違いなく俺たちは死ぬ運命だ！まあいい、命を賭けてでも船まで戦ってみせるぜ！";
						link.l1 = "なんだと？自分たちを見てみろよ、まともに立ってもいられねえじゃねえか…";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "試してみるがいい…";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "お前にしてやれるのは、食料と薬を十分に残して、小舟を渡すことだけだ。\n少なくとも飢えや渇きで死ぬことはねえだろう。航海術については、俺が教えるまでもねえよ。";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "しかし、もし断るなら、俺たちは確実に死ぬ運命だ！\nまあいい、命を賭けてでも船まで戦ってみせるぜ！";
							link.l1 = "なんだと？自分の足で立つのもやっとじゃねえか…";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "試してみるがいい…";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "どうして俺たちにこんなことをしたんだ！？…お前は海の掟を無視しただけじゃなく、自分の名誉まで汚しやがった！";
							link.l1 = "俺の名誉についてお前が語る筋合いはねえだろ、このチビ！";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "俺がしてやれるのは、食料と薬を十分に残して、小舟を渡すことだけだ。\n少なくとも飢えや渇きで死ぬことはねえだろう。\n航海術については、教えるまでもねえよな。";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "あんたの言う通りだ、俺たちに勝ち目はねえ。わかった、神が裁きを下すだろうし、誰もがそれぞれの報いを受けるんだ。 ";
			link.l1 = "まあ、俺に任せとけ…";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "……仕方ねえな……もう選択肢はねえ……嵐や渇きが、俺たちの命を奪う前に人の住む場所へ辿り着けるよう祈るしかねえ……";
			link.l1 = "さらばだ。主があなたを見守ってくださいますように……";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "どうやら、我々に選択肢はないようですね……しかしお願いです、船長、できるだけ早く戻っていただくか、遠征船を派遣してください。";
			link.l1 = "何とかしてやるさ。ちょっと待ってろ。";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("船長、どうか覚えていてください、あんたが俺たちの唯一の希望なんだ…","なぜぐずぐずしてるんだ？ここにいる時間が一分一秒でも耐えられねえんだよ……");
			link.l1 = "できる限りのことはやるぜ。じゃあな……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("さらばだ、船長…。俺たちは旅の準備をしなきゃならねえ。","さらばだ……俺たちの魂を救うために、ろうそくに火を灯してくれ……");
			link.l1 = "さらばだ。主があなたを見守ってくださいますように……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "「どうして俺たちにこんなことをしやがったんだ！？海の掟を無視しただけじゃなく、自分の誇りまで汚しやがって！」";
			link.l1 = "俺の名誉についてお前が語る筋合いはねえだろ、チビ！";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "ありがとうございます、船長！積み込みにはあまり時間がかからないはずです。神よ、 この時が来るようどれほど祈ったことか！";
			link.l1 = "それは良かった。君の試練が早く終わることを願っている。";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "ありがとうございます、船長！積み込みにはあまり時間はかからないはずです。神よ、 この瞬間が来ることをどれほど祈ったことか！";
			link.l1 = "それは素晴らしいな。お前の苦労が早く終わることを願ってるぜ。";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "来いよ！本気かよ、船長！？俺たちが死を恐れるとでも！？一度は死神を出し抜いたんだ、またできるさ。ただ、 こんな形で命を落とすのはごめんだ。ここで一人きりで朽ち果てるなんてな\n喜んであんたの船に加わって、あんたの旗の下で勇敢に戦うぜ。だから、ここに置き去りにしないでくれよ…";
			link.l1 = "ここから出るためなら何でもやるつもりだな。だが、自分たちの姿を見てみろよ、 お前らがどんな船乗りになれるってんだ？";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "それはいい考えだな。雇ってやってもいいぜ。";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "いや、いや、本気だ！頼む、このカリブの屠殺場から連れ出してくれ…この地獄から逃がしてくれ！俺はな、金持ちなんだ…とんでもない大金持ちだぜ。教皇様でさえ一生でそんな金は見たことがねえ。金ならいくらでもくれてやる…";
			link.l1 = "おやまあ……よし、舟に乗れ……";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("何をぐずぐずしてるんだ、船長？錨を上げる命令を出してくれ。","申し訳ねえ、船長。でも出航の準備をしなきゃならねえんだ。","あんたがここに来てくれて、俺たちは本当に運がいいぜ！");
			link.l1 = "急げ。船は誰も待っちゃくれねえぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "船長、俺たちにはもう失うものなんてねえ。死神はすでに俺たちの後をつけてきてる……汚ねえコヨーテどもに食い殺されるくらいなら、正々堂々と戦って死んだほうがマシだぜ……";
			link.l1 = "おお、挑戦ってわけか！？よし、決着をつけようぜ"+GetSexPhrase("、男みたいにな","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "誓うぜ、船長、絶対に後悔はさせねえ。俺たちはこの群島一の水夫になるんだ。";
			link.l1 = "よし！ボートに乗り込め…";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("誓うぜ、船長、絶対に後悔はさせねえよ。","いい選択をしたな、船長。","船長、安心しな。あんたも俺たちと同じくらい運が良かったんだぜ！");
			link.l1 = RandPhraseSimple("そうだといいんだが。","急げ。船は誰も待っちゃくれねえぞ。");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "船長、どうしてそんなに疑って正直者たちを侮辱するんだ？\n奴らの顔をよく見てみろよ、本当に反乱者に見えると思うのか？";
			link.l1 = "わかったが、で、これからお前をどうすりゃいいんだ？";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "「俺に何ができるってんだ？少なくとも今は生きてる……そして、ここから逃げ出せたことを神に感謝してるぜ！だがな、もしあんたが俺の船を取り戻すのを手伝ってくれて、 この屈辱の仕返しをしてくれるなら、あの野郎が盗んで船倉に隠したものは全部あんたにくれてやる。」";
			link.l1 = "よし、取引成立だ。";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "俺たちに命令できる立場じゃねえ。あんた次第だ、どこかの入植地に連れて行ってくれてもいいし、 俺たちを船員にしてくれてもいいぜ。";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "よし、俺のクルーに入れてやる。だが、ふざけるんじゃねえぞ！俺の船は規律が厳しいんだ！";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "どこにも連れて行かねえよ。俺の船にはもう十分ゴロツキがいるんだ。";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "よし、舟に乗れ。どこかに連れてってやるぜ。";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "仕方ねえな……もう選択肢はねえ……天の御加護があって、この危険な場所から逃げ出せるよう祈るしかねえ。神様が助けてくれりゃ、 どこか人の住む土地にたどり着けるかもしれねえ……";
			link.l1 = "さらばだ。主があなたを見守ってくださいますように……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "本当にありがとうございます、船長 "+GetFullName(pchar)+"！あなたは俺たちのためにあまりにも多くのことをしてくれたから、どんな感謝の言葉でも足りねえよ。 俺たちの持ち物なんて銅貨一枚の価値もねえが、このお守りを受け取ってくれ。 海戦にしょっちゅう巻き込まれる船長には、きっと役に立つぜ。";
				link.l1 = "贈り物をありがとう！この小物は本当に役に立つぜ！じゃあな、船長 "+pchar.GenQuest.ShipWreck.Name+" 航海のご武運を祈るぜ。";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "船長、本当にありがとうございます。あなたが私たちのためにしてくれたことに比べれば、 どんな報酬も取るに足りません。どうか、感謝のしるしとしてこのささやかな贈り物をお受け取りください。";
				link.l1 = "本当に、わざわざ気を遣ってくれなくてもよかったのに……君の方が俺よりずっと金が必要だろう。それでも、親切にしてくれてありがとな。感謝する、じゃあな。";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "船長、これからはあんたのためなら地の果てまでついていく奴らがいるってことを知っておいてくれ。\n礼をするもんも持っちゃいねえのが残念だが……それでも、これを受け取ってくれ。このガラクタはあの呪われた入り江で見つけたんだ。\nあんたに幸運をもたらすことを願ってるぜ。";
			link.l1 = "俺の立場なら誰だって同じことをしたさ。じゃあな。";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("船長、もうダンケルクに着いたのか？","「本当にここはダンケルクなのか、船長？」"),RandPhraseSimple("船長、ここはヨーロッパか？","「こんなに早くヨーロッパまで航海したのか？」"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "あは…";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("「まだだ……」","ダンケルクだと？ヨーロッパだと？周りを見てみろ！","「なんてこった！」");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("でも、船長、約束したじゃねえか！","「どうして約束を破ったんだ、船長？」","「で、いつヨーロッパに行けるんだ？」");
			if(rand(100) < 70)
			{
				link.l1 = "わかった。旦那、自分の仲間と持ち物をまとめて、好きなところへ行け。";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("本当にダンケルクまで行く必要があるのか？","なあ、俺の船は大海原を渡るためのもんじゃねえんだ。","船長、カリブのどこが悪いんだ？"),LinkRandPhrase("だが、俺には別の計画があったんだ……","そもそもなんでヨーロッパに行きたいんだよ……","あの魅惑的なムラート女たちを想像してみろよ！ヨーロッパじゃ絶対に会えねえぜ…"));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "しかしどうして……？どういうつもりだ！？これは一体どんな裏切りだ！？約束を守るってことを教えてやるぜ！";
			link.l1 = "……お前が望んだことだぜ……";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("嫌だ！俺はダンケルクに行かなきゃならねえんだ！","地理を教えるよりも、自分の義務を果たしたらどうだ！"),RandPhraseSimple("そんな話は聞きたくねえ！ヨーロッパに連れて行くって約束しただろう！","いや、船長、それじゃ駄目だ。俺たちはヨーロッパへ向かって航海してるんだ。"),"俺はこんな穴蔵で惨めな人生を送って残りの人生を終えるつもりはねえぞ！");
			link.l1 = "ああ、どうなっちまうのか分からねえな……";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "見ろよ！あいつはまともな奴だぜ！ヨーロッパだ！血塗られた古きヨーロッパよ！そうだそうだそうだ！\nおう、そうだ！お前は約束を果たした、だから俺も約束通りにするぜ。ほら、この地図の半分を持っていけ。 もう半分は相棒が持ってたんだ。安らかに眠れ、いや水の中で眠れってか？まあ、どっちでもいいさ。 冒険に俺を誘ったのはあいつだったんだ。";
			link.l1 = "待てよ、お前は水夫じゃねえのか？仲間は船長だったのか？";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "おお、なんてこった…！もちろん違うさ！まあ、確かに俺は水夫じゃねえ。あいつは岸からもっと沖へ出ようとしたとき、 でっけえ波にさらわれて海に落ちちまったんだ。それで俺が指揮を取って入り江に向かうよう命じた…そして、サンゴ礁をうまく抜けて進んでたんだが、運命の事故ですべてが決まっちまった。 船が岩のかけらにぶつかって沈んじまったんだよ…";
			link.l1 = "……これぞ本物の無能ぶりだな……";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "聞けよ、ここは本当にダンケルクなのか？考えてみろよ、たった半年で全部が変わっちまったんだぜ\nほら、地図をやるよ、いや、正確にはその一部だ。宝は洞窟の中にある！どの島かは知らねえが、 お前は経験豊富な船乗りだ、そのうちきっと正確な場所を見つけられるさ…保証するぜ、aaarrrrrhgって名の海賊の莫大な財宝が眠ってるんだ…";
			link.l1 = "ありがとう、旦那。たとえ宝が全くなくても、俺はそんなに気にしねえさ。じゃあな、 もう二度と会わねえことを願ってるぜ…";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("船長、俺たちのことを忘れずにいてくれて嬉しいぜ！みんなお前の無事を祈ってたんだ！","船長、俺たちの救いは近いのか？どれほどそれが来るよう祈ってきたことか！もう絶望しかけてる奴もいるんだ……");
			link.l1 = "「ごきげんよう。」 "+pchar.GenQuest.ShipWreck.Name+"！こんな状態で仲間を置いていけるかよ？どこへ行くんだ？";
			link.l1.go = "ShipWreck_45";
			link.l2 = "「ごきげんよう。」 "+pchar.GenQuest.ShipWreck.Name+"！悪い知らせがあるんだ。計画が変わっちまって、あんたを乗せることができなくなった。";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "俺たちはどこへ行こうが構わねえ、この呪われた場所から十分遠けりゃな…俺たちが荷積みを始めてもいいか？\n";
			link.l1 = "ああ、それで進め。もうすぐお前の試練も終わるだろう。";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "ありがとうございます、船長。俺たちはもう絶望しかけてたが、あんたが本当に俺たちを生き返らせてくれたぜ。";
			link.l1 = "大したことじゃねえ……じゃあな。";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "俺に一体何の用だよ？";
			link.l1 = "来たぜ"+GetSexPhrase("","")+" 「という名の者からよろしく伝えてくれと頼まれた」"+pchar.GenQuest.ShipWreck.Name+"。あいつのこと知ってるか？"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "あの悪党を前に絞め殺しておかなかったのが悔やまれるぜ。\nまあいい、そろそろ俺の情けの代償を払う時が来たってわけだな……";
			link.l1 = "確かに……そして時間がちょうど切れた……";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "よくやったな、船長！約束通りでいいんだな？俺たちは船をもらって、 あんたは積み荷を手に入れるってことでいいんだな？";
			link.l1 = "ああ、船を持っていけ。しっかり役立てろよ。";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "ご挨拶申し上げます、船長 "+GetFullName(pchar)+".";
			link.l1 = "それで、自分の船は気に入ったか？";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "へっ、きしんだりギシギシ鳴ったりしてやがる、まるで俺みてえだ。俺もこいつも、 もう大海原を航海できる時間はあんまり残っちゃいねえな……";
			link.l1 = "じゃあ、幸運を祈るぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "船長、どうか俺たちに船かロングボート、タルタンでも何でもいい、何とか手配してくれ、本当に何でも構わねえんだ。\nこんな厳しい状況じゃ、この居心地の悪い場所から逃げ出さなきゃならねえが、入植地には顔を出せねえんだ。";
					link.l1 = "「それで、一体どんな事情なんだ？」";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "船長、どうか二百ペソほど貸してくれませんか？頼みたくはないんだが、本当に困ってるんだ。";
					link.l1 = "切羽詰まってるって？どうせラム酒が切れただけだろ、それは確かに一大事だな。";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "船長、恐縮ですが、我々のつましい一行を灯台までお連れいただけませんか "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "お前の様子を見る限り、とても謙虚には見えねえな。";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("俺は金曜日には施しをしねえんだ。","こんなくだらねえことに付き合ってる暇はねえんだ。","俺は見ず知らずの奴なんか助けねえ。");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "俺たちは逃亡者だ……どこからか "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+"……すぐに元の主人に気づかれちまう……そしたら俺たちは確実にお陀仏だぜ。";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "帆の扱い方が分かるんだな？";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "「で、何で支払うつもりだ？」";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "今はラムのことなんか考えてる場合じゃねえ。脱出してからもう一週間、今じゃジャングルに隠れて腹を空かせてるんだ。 ";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "さて、俺が金を渡したとして……それでどうする？どうせパトロールに見つかるまで隠れているつもりか？";
				link.l1.go = "Convict_12_1";		
				link.l2 = "よし、いくら必要なんだ？";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "お前みたいな奴に言うことはほとんどねえ――ただの死刑台の首だ、それだけだ！";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "「他に何ができるってんだ？喜んで船乗りの仕事を引き受けるぜ、でも俺たちは逃亡者だろ、誰が雇ってくれるんだよ？」 ";
				link.l1 = "帆の扱いができて、臆病者じゃねえって証明できるなら雇ってやるぜ。";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "もう地元の水夫たちとは話がついてるんだ。ここを出るには、あと三千足りねえだけだぜ。";
				link.l1 = "「ほらよ、三千だ。本当に役に立つんならな。」";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "さあな……それはお前自身の問題だろう、俺が手を貸すつもりはねえよ。";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "お願いです、船長、俺たちを雇ってくれよ、きっと後悔はさせねえ！俺たちはずっと一緒に海賊やってきたんだ\n "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" アドリア海で、最後には奴が絞首刑になり、俺たちは、 "+pchar.GenQuest.Convict.ConvictQty+" 男たちはこの場所に追放されたんだ。";
			link.l1 = "わかった。近くに「」という場所がある "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"。真夜中ごろにそこで迎えに行くぜ。迷子にならねえようにしてくれよ。";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "もちろん、大いに助かるぜ！風が良けりゃ今日にも出航するつもりだ、漁師どもがしくじらなきゃな。ありがとう、船長、 神のご加護を……";
				link.l1 = "お前にも幸運を祈るぜ。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "こりゃ運がいいぜ！こんなに早く金が手に入るなんて思ってもみなかった。\n船長、前の親分から奪った小物をあんたに贈らせてくれ。\nきっとあんたにも幸運をもたらしてくれるはずだぜ。";
				link.l1 = "ありがとうよ、そいつはなかなか義理堅いじゃねえか。幸運を祈るぜ。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "おう、ここにいるのは、稼ぎ方を知ってるからこそ金を惜しまず使う太っ腹な男だぜ！\n昨夜、俺たちは地元の密輸業者が積み込みをしてるのを見た "+MerPrm.QuestGoodsIdx+"。暗かったが、俺たちはなんとかボートの側面に書かれた船の名前を読み取ることができた、『"+MerPrm.ShipName+"「…そしてその船は、～の旗の下で航海している」 "+MerPrm.nation+"もしかしたらこの情報が役に立つかもしれねえな、へへ。";			
				link.l1 = "ふむ……まあ、そうするかもしれねえな。じゃあな、追っ手ども。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "おやまあ、俺たちが要求できる立場じゃねえ。分けてくれるもんなら、なんでもありがたく頂くぜ。";
			link.l1 = "３００ペソだ。";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000ペソ。";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "３０００ペソ。";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "ありがとうございます、船長。そして神のご加護がありますように……";
			link.l1 = "お前にも幸運を祈るぜ。";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "こりゃ運がいいぜ！こんなに早く金を手に入れられるなんて思ってもみなかった。\n船長、俺たちが前の親分から奪った小物をあんたに贈らせてくれ。\nきっとあんたにも幸運をもたらしてくれるはずだぜ。";
				link.l1 = "ありがとう、そいつはなかなか義理堅いじゃねえか。幸運を祈るぜ。";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "ありがとうございます、船長。神のご加護がありますように……";
				link.l1 = "お前にも幸運を祈るぜ。";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "こりゃ運がいいぜ！こんなに早く金を手に入れられるなんて思わなかった。\n船長、前の親分から奪ったガラクタをあんたに渡させてくれ。\nきっとあんたにも幸運をもたらすかもしれねえぜ。";
				link.l1 = "ありがとうよ、そいつはなかなか義理堅いじゃねえか。幸運を祈るぜ。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "今ここにいるのは、自分で稼ぐ術を知っていて、金を惜しまず使う気前のいい男だぜ！\n昨夜、俺たちは地元の密輸業者が荷積みしてるのを見た "+MerPrm.QuestGoodsIdx+"。暗かったが、俺たちはなんとかボートの側面に書かれた船の名前を見分けることができた『"+MerPrm.ShipName+"「…そしてその船は、～の旗の下で航海している」 "+MerPrm.nation+"。もしかしたらこの情報が役に立つかもしれねえな、へっへっ。";
				link.l1 = "ふむ……まあ、そうするかもな。じゃあな、追跡者ども。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "俺たちに災いをもたらさないでくれ、船長！\nいい飾り物があるんだ、頼む、身代金として受け取って俺たちを放してくれ…";
				link.l1 = "さっさと渡せ、そして生きてるうちに消えな。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "もう他に道はねえ、男は二度は死なねえんだ。最後の戦いだ、野郎ども！";
				link.l1 = "そりゃ話が違うぜ！";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "まあ、俺たちは決して聖人じゃねえが、無駄な揉め事を求めてるわけじゃねえ……俺たちは逃亡者だ、できるだけ早くここを出なきゃならねえんだ。";
			link.l1 = "通行料を払うものは持ってるか？";
			link.l1.go = "Convict_13_1";		
			link.l2 = "ああ、そうか……いや、俺はお前のせいで自分の評判を汚したりはしねえ。さらばだ。";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "任せとけよ！俺たちは白兵戦とか、そういうのには慣れてるんだ。もう二年近く、俺たちと故\n "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" 地元の商人たちを脅かしていたんだが、ああ、残念だ！奴は絞首刑になっちまって、そして "+pchar.GenQuest.Convict.ConvictQty+" 俺たちの中には流刑に処された奴らもいたんだ。";
			link.l1 = "俺の仲間にならねえか？俺は気前がいいぜ\n"+GetSexPhrase("","")+"、だが平穏な暮らしを約束することはできねえぜ。";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "ああ、俺たちは何かを手に入れたぜ\n "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+"、だから倍払えるってわけだ。これで値段は決まりだな。絶対に衛兵なんか連れてくるんじゃねえぞ。 裏切りは許さねえからな…"; // belamour gen
			link.l1 = "よし、浜辺で待ってろ "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+"……真夜中近くになったら、お前のためのボートが来る……それと、変な真似は見たくねえからな！"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "いや、仲間たちよ。もし俺が船を渡したら、お前らが裏切るかもしれねえだろ？いやだ、この件には手を貸さねえ。";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "「喜んで」 "+GetSexPhrase("旦那","お嬢さん")+" 船長。そんなことはよく知ってるぜ、しかもそんな推薦じゃあ海軍になんて絶対入れてもらえねえさ、へへ。";
			link.l1 = "わかった。近くに「」と呼ばれる場所がある "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"。真夜中過ぎにそこで迎えに行くぜ。迷子にならねえといいがな。";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "しかし、 "+GetSexPhrase("旦那","お嬢さん")+" 船長、俺たちもっと危ねえことしてるんじゃねえか？もしあんたが俺たちを司令官に売るって決めたらどうするんだ？";
			link.l1 = "そうだな……よし、夜明けまでに俺が来なかったら、この取引はなしだ。";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "ああ、船長、俺たちはあんたを頼りにしてたんだぜ…";
				link.l1 = "問題ねえさ。金さえありゃ、船には乗れるぜ。じゃあな。";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "あんたは頭が切れるな、船長。見りゃわかるぜ。どうせすぐに司令官のところへ駆け込むつもりなんだろ？ それで本当にうまくやれると思ってるのか？";
				link.l1 = "俺を止めるつもりか、そう見えるぜ！？なら、報いを受けてもらうぞ！";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "何かあるんだ。俺たちは親分の金庫をあさったんだが、そのことで騒ぎになって、逃げるために戦う羽目になった。だが、 ただ\n "+PChar.GenQuest.Convict.ConvictQty+" 男たちは生き延びることができた。";
			link.l1 = "状況を考えると、それ以下の料金では乗船を許可できねえ "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" 一人あたりペソだ。";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "お前ら、腰抜けじゃねえな。俺の仲間になる気はあるか？";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "「俺たちに選択肢があるのか？まあ、仕方ねえな、」 "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "それなら行け "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+"。真夜中過ぎに迎えのボートを出すぜ。"; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "なぜ駄目なんだ？俺たちはその手のことは知ってるぜ、ずっと海賊稼業やってきたんだからよ "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" で "+RandPhraseSimple("Gibraltar","イギリス海峡")+" ここに足止めされる前にな。";
			link.l1 = "よし。近くに「」と呼ばれる場所がある "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"。真夜中ごろにそこで迎えに行くぜ。迷子にならねえといいがな。";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("ええ、船長、あんたも昔は貧乏だったろ、懐も空っぽだったじゃねえか。今じゃ俺たちみたいな下々 の者を見下してるんだな。","船長、こんなふうに庶民を扱うのは間違ってますぜ。俺たちは皆、同じ神のもとにいるんだ。"),RandPhraseSimple("へっ、最近の奴らは本当に自分勝手になってきたな。まるであと二百年も生きられるつもりでいやがる。","おう、ヨーロッパから着いたばかりか。まだこの南国のクソ溜めの臭いも嗅いでねえんだな。"));
			link.l1 = LinkRandPhrase("俺を恥かかせようってのか？その舌、二寸ほど短くしてやるぜ！","俺を脅そうってのか？帽子をしっかり押さえとけよ！","お前、哲学者か何かか？俺がぶん殴って目を覚まさせてやるぜ！");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("それで、船長？俺たちの船は見つけてくれたのか？","よう、船長。で、俺たちの取引はどうなったんだ？","やあ、船長。心配し始めてたところだぜ。すべてうまくいったんだろうな？");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "ああ、これがお前の船だ。支払いのことは忘れるなよ。俺が払ったんだからな "+pchar.GenQuest.Convict.ShipPrice+" そのための金貨を出したんだ、だからお前は俺に借りがあるぜ "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+"、約束通りだ。";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "いや、気が変わった。自分で他の手伝いを探せよ。じゃあな…";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "もちろんだぜ！奴らは俺たちの自由を奪ったが、良心までは奪えなかった！どうか、 この金と俺たちの限りない感謝を受け取ってくれ。あんたは本当に助けてくれたんだ。\n銀の延べ棒で支払っても構わねえか？";
					link.l1 = "ああ、知らねえよ。旅の幸運を祈ってるぜ。だがな、もし外洋で俺と出くわしたら、容赦しねえから覚悟しとけよ。";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "船長、あのな、俺たちは金なんて人生でそんなに大事じゃねえって思ってたんだ。だが正直言って、 今となっちゃあんたよりも俺たちの方が金が必要なんだよ。\nでもな、前の親分から盗んだブツがあるんだ。もしかしたら金よりもあんたの興味を引くかもしれねえぜ。\nちょっと見てみる気はあるか…？";
					link.l1 = "ああ、その通りだ。本当に素晴らしいことだぜ。よし、わかった、取引成立だ。ありがとな、じゃあな。";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "そんな大金、何に使うんだよ、船長？どうせあんたは金持ちだし、俺たちはこの船を手に入れなきゃ終わりなんだ。 だからよ……悪いが、あんたから奪わせてもらうぜ。恨みっこなしだ。";
					link.l1 = "それが最後の過ちだったな。船があればまだ泳いで逃げられたが、今となっちゃ浮くか沈むかしかねえぜ。";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("それで、船長？積み込みを始めていいか？","やっと来たか！心配し始めてたんだぜ、お前が気が変わったのかと思ったからな。");
			link.l1 = "悪いが、予定が変わっちまった。今は他の船長を探すんだな。";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "船に乗れ、俺にはあまり時間がねえんだ。";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "船に乗れ、俺にはあまり時間がねえんだ。";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "くそっ！どうせもう俺たちを追う巡回隊を送りやがったんだろう！？こんなこと、ただじゃ済まねえぞ！";
				link.l1 = "何言ってやがる！？死にてえのか、それともどうなんだ！？";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Captain "+GetSexPhrase("「お前は約束を守る男なのか、それとも違うのか？」","?")+" それとも、ただのクソうるさいおしゃべり野郎か……";
				link.l1 = "舌の使い方に気をつけたほうがいいぜ……";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("「ああ、ありがとう」 "+GetSexPhrase("親切な男","お嬢ちゃん")+".","ありがとう、船長、あんたは本当に俺を絞首刑から救ってくれたぜ。","こんな素晴らしい航海、感謝するぜ。");
			link.l1 = LinkRandPhrase("それはそれでいいが、俺は金を待ってるんだ。","払う時間だぜ、わかってるよな。","「約束通り、現金はその場で払え。」");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "もちろんだ、何を今さら聞くんだよ！ほらよ、金の延べ棒で支払うぜ。それと、俺たちの心からの感謝も受け取ってくれ。 ";
					link.l1 = "お前にも幸運を。じゃあな。";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "船長、あのな、俺たちは金なんて人生でそんなに大事じゃねえって思ってたんだ。だが正直言って、 今はあんたよりも俺たちの方が金が必要なんだよ。\nでもな、前の親分から盗んだブツがあるんだ。もしかしたら金よりもあんたの興味を引くかもしれねえぜ。\n見てみるか？…";
					link.l1 = "ああ、その通りだ。まったく素晴らしいことだぜ。よし、わかった、取引成立だ。ありがとな、じゃあな。";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "なんでそんなに金が必要なんだ？どうせあんたは金持ちだろう。\nあんたが助けてくれたんだ、今度は俺たちが助けてやるさ。";
					link.l1 = "そんな機会はねえぜ。覚悟しやがれ、このクズども、俺は借金なんざ許さねえ。";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "俺はここに送られてきたんだ "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 自分自身で……";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" もう何時間も返事を用意してあなたを待っているぜ。あんたの後ですぐに俺を寄越したんだ。";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "しばらくあんたの航跡を追ってたんだが、あんたは速すぎるぜ。";
			link.l1 = "それでどうした？";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "総督は手下どもにいくら払ってやがるんだ？";
			link.l1 = "ちくしょう！";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "飲んじゃいねえよ！俺は水夫長を探してたんだ…";
			link.l1 = "さあ行け……俺が話す "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+"、お前がジャングルで行方不明になったってな。";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "お前は頭が切れる奴だな。自分の企みが知られないように神に祈るんだな "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "あいつには言わなきゃバレねえ……お前、言わねえよな？";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "なぜだ？もちろんだ、喜んでやるぜ！";
			link.l1 = "どうせそんな愚行のせいでお前は吊るされるんだぜ。だから時間を無駄にせず、 俺が絞首台から逃げる手助けをしてやるよ。";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "ふむ……それをどうやってやるつもりだ？";
			link.l1 = "俺が自分の手でお前を殺してやる……";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "ここで用事か、 "+GetSexPhrase("旦那","お嬢さん")+"?";
			link.l1 = "いやいや、俺は総督の魅力的な奥方に招待されてここに来たんだ。ただこの本当に豪華な屋敷を眺めているだけさ。";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "あんたの知り合いから伝言を預かってきたぜ。";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "ああ。お前を裁きにかけてやる！";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "ああ、そうさ、本当にこんな美しい屋敷で仕えることができて幸運だったよ。";
			link.l1 = "道理で……";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "俺たちの庭も忘れずに見ていってくれよ！";
			link.l1 = "ありがとう、いい男！";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "ええっ…… "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "こんなこと、許さねえぞ、裏切り者！";
			link.l1 = "じっとしてろ、この野郎！";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "急げよ！価値のあるもん全部持って逃げろ！";
				link.l1 = "お前も逃げたほうがいいと思うぜ。";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "うーん、失礼する、もう行かなくちゃ。";
				link.l1 = "じっとしてろ、この野郎！";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase("盗人か、なるほどな！衛兵ども、そいつを捕まえろ","泥棒か、なるほどな！衛兵ども、あの女を捕まえろ")+"!","信じられねえ！ちょっと目を離した隙に、俺の箱を漁ってやがる！泥棒を止めろ！","衛兵！強盗だ！泥棒を止めろ！");
			link.l1 = "ああっ、悪魔め！";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("やあ "+GetSexPhrase("相棒","娘")+"！お前のためにサプライズを用意したぜ、火薬庫に導火線をつけてやったんだ。今にドカンと吹っ飛ぶぞ！","なんでそこに突っ立ってるんだ？火薬庫で火事だぞ！もうすぐ爆発する、ヨーロッパからでも花火が見えるぜ！");
			link.l1 = RandPhraseSimple("この野郎、俺を騙せると思うな！かかってこい、この腰抜け！","船を捨てて逃げるネズミどもが見えるが、お前もその先頭か？");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("命が惜しいなら、お前も逃げた方がいいぜ……まあ、俺には時間がねえ、ボートが待ってるんだ。釣りを楽しめよ！","俺はヒーローごっこしてる暇なんかねえんだ、ボートの連中が俺を待ってるんだよ。釣りでも楽しんでくれよ、勝者さん！ ");
			link.l1 = RandPhraseSimple("くそっ！フェンダーを切れ！離岸しろ！","ああ、神よ、どうしてこんなひどい目に遭っちまったんだ！\n海の水門を開けろ！離れろ！");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "だから何だってんだ！？てめえ、自分が勝ったつもりかよ！？冗談じゃねえ。火薬庫に火をつけてやったからな、 てめえはこの船から生きては出られねえぞ。";
			link.l1 = RandPhraseSimple("この野郎、俺を騙せると思うな！かかってこい、この腰抜けめ！","船を見捨てて逃げるネズミどもがいるが、お前もその先頭か？");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("俺には誓いがあるが、だからって無駄死にするつもりはねえ。\n悪いが、お前にボートの席を譲れなかった。水夫たちには理解できねえだろうからな。","船同士が接舷して斬り込みが始まったから、お前の運命はもう決まったぜ。悪いが、俺のボートが待ってるんでな…\n");
			link.l1 = RandPhraseSimple("くそっ！フェンダーを切れ！離岸しろ！","ああ、神よ、どうしてこんなひどい目に遭っちまったんだ！\n海の水門を開けろ！\n離れろ！");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("お前の勝ちだ！地獄へようこそ！火薬庫に火をつけてやったぜ。","ほらよ、旦那！これで終わりだ。火薬庫に火をつけてやったぜ。");
			link.l1 = RandPhraseSimple("この野郎、俺を騙せると思うな！かかってこい、この腰抜け！","船を見捨てて逃げるネズミどもがいるが、お前もその先頭か？");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("ずっとお前を追いかけてたんだぜ。船を犠牲にしちまったのは惜しいが、お前の首は新しい船二隻分の価値があるからな。 釣りでも楽しんでな！","どうやって行くつもりだ？花火でも上げて、インドの王子様みたいにか？"+GetSexPhrase("「ce」","セス")+"。しかし俺は負け犬じゃねえ；お前の首は俺の船よりずっと価値があるんだ。じゃあな、 俺のボートはそう長くは待たねえぞ…");
			link.l1 = RandPhraseSimple("くそっ！フェンダーを切れ！離岸しろ！","ああ、神よ、どうしてこんなひどい事態になっちまったんだ！\n海の水門を開けろ！離れろ！");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("待ってくれ、船長！ちょっとだけ話があるんだ。","待てよ、船長！これはあんたにとって興味深いかもしれねえぜ。");
			link.l1 = LinkRandPhrase("戦いの最中に何しゃべってやがるんだ！？","「それで俺が死人と何を話せばいいんだ？」","どういうことだ？俺の名前で遺言状でも作りたいのか？");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "船内で疫病が発生したんだ。航海中に乗組員の四分の一を失った。お前ら全員、もうおしまいだ……";
			link.l1 = RandPhraseSimple("てめえ、このクズ野郎！なんで自分の船で災難が起きたって合図しなかったんだよ！？","海の掟を忘れたのか？船で災難が起きたなら、マストに合図を掲げるべきだっただろう！");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "どうせ俺たちは死ぬ運命だったんだ。だからこそ諦めなかった、 お前とその悪党どもを道連れにあの世へ連れていきたかったんだ！\n今はもう思い残すことはねえ。好きに汚ねえ仕事を終わらせろよ。";
			link.l1 = RandPhraseSimple("そのツケ、しっかり払わせてもらうぜ！..","お前が最初に死ぬってのはいい考えだな。俺が見届けてやるぜ。");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("俺はお前の汚え血で刃を汚す気はねえ、生かしてやるよ、だが……生きてて何になるんだ？俺は仲間を連れてあの腐ったボロ船から出ていくぜ。","そのことでお前は絞首台送りにされてもおかしくねえが、今はその必要もねえ。俺は仲間を連れて引き上げる……命は助けてやるが、お前の余命は長くねえだろうな……");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "やあ、船長、俺を探してるって聞いたぜ。";
			link.l1 = "俺はそうだぜ――お前がそうならな。 "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "そうだぜ。何か大事な用か？";
			link.l1 = "それがあんたにとって大事かどうかは知らねえが、俺が持ってきたのは "+pchar.GenQuest.EncGirl.name+"。家を飛び出して、今は酒場の近くであなたを待っているぞ。";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "ああ、なんてことだ……こうなるって分かってたんだよ……それで、なんであの子は逃げたんだ？お前に何か言ってたか？";
			link.l1 = "彼女の父親は彼女を高利貸しの息子に嫁がせたがっている。";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "「おいおい、それは絶対に許せねえ！船長、実はな、俺はとんでもねえ状況にいるんだ……あんたに俺たちを連れて行ってもらいたくて頼もうと思ってたんだ」 "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" 「という町へ」 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"、だが今は金がなくて、まだ仕事も見つかっていないんだ。家は裕福だし、将来有望な職業もあるんだが "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"…\n安心してくれ、俺の両親は若い婚約者を連れて帰ればきっと喜ぶし、あんたにもたっぷり礼をするぜ。どうだ、乗るか？";
			link.l1 = "…聞けよ、俺はまったく別の計画があるんだ。ひとつアドバイスしてやるぜ：水夫として働いて、 その給料で花嫁のために船室を借りな。そうやってヨーロッパへ渡る奴もいるし、 お前のその入植地なんざ鳥が飛んでいける距離だ。";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "ああ、若者よ……お前が俺に何を頼んでいるのか分かっているのか？親の許しもなく娘を連れ出すなんて……だが、そんな頼みを断る男がいるか？もちろん、俺も乗ったぜ！";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "ありがとうございます、船長。あなたの助けは生涯忘れません。";
			link.l1 = "たいしたことじゃねえさ。お前にいいことがあるといいな。";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "両親に君を紹介するって約束したんだ。もし時間があったら、ぜひ来てくれ\n "+sTemp+"、俺の父ちゃんがそこで働いてるんだ、あんたがしてくれたことを伝えるよ。 きっと父ちゃんもあんたに会えて喜ぶはずだぜ。";
			link.l1 = "よし、時間ができたら寄るぜ。二人とも仲良く元気でな。\n";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("待ってくれ！待ってくれ、船長！頼む。","船長、お願いです、待ってください、頼みます…");
			link.l1 = LinkRandPhrase("なんだと？息が切れたのか？","刃を上げろ、この腰抜け野郎！","どうした？遺書を書くのを忘れたのか？");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "待ってくれ……俺は傷を負って、もう戦う力がねえ……情けをかけてくれとは言わねえが、まだやり残したことがあるんだ。頼む、 死にゆく男の最後の願いを叶えてくれると約束してくれ。";
			link.l1 = RandPhraseSimple("腰抜けになるなよ、船長、男らしく死を迎えやがれ！","船長、何を感傷的になってるんだ？周りじゃ戦いが真っ最中だぜ、始めたことを最後までやろうじゃねえか。");
			link.l1.go = "CaptainComission_21";
			link.l2 = "今すぐ話せ、手短にな。";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Tell "+pchar.GenQuest.CaptainComission.Name+" 入植地からの "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+"…あいつの頼みを果たせなかった…俺に時間がなかったんだ…許してくれよ…";
				link.l1 = RandPhraseSimple("「それだけか！？まあ、やってやるぜ。おい、相棒…」","わかった、時間があれば伝えておくよ。\nおい、相棒……");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "そうは思わねえな。そんなくだらねえことに付き合ってる暇はねえ。始めたことを終わらせようぜ。";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "どうか、巡回隊の船長に伝えてくれ "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" 「」"+pchar.GenQuest.CaptainComission.ShipTypeName+"「」 "+pchar.GenQuest.CaptainComission.Name+"、二度と顔を出すんじゃねえぞ "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"当局は彼の死の本当の事情を把握している "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" 「」"+pchar.GenQuest.CaptainComission.VictimShipName+"…時間がない、あいつは逮捕されちまう……航海に出る "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" から "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+"…航海にはほぼ十五日もかかる……ああ……急がないとな……"; // belamour gen
				link.l1 = RandPhraseSimple("何も約束はできねえが、時が来たらやってみるさ。なあ、相棒…","わかった、時間があれば伝えておくよ。\nおい、相棒…");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "なんて残酷なんだ！その報いはきっと受けてもらうぜ。";
			link.l1 = "そして、もっとたくさん……";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("聞いてるぜ、 "+GetAddress_Form(pchar)+".","何の用だ？","どうなさいましたか？");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "お前は "+pchar.GenQuest.CaptainComission.Name+"？用があるんだ、船長 "+pchar.GenQuest.CaptainComission.CapName+" お前に重要な情報を伝えるように頼まれたんだ。";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "いや、何もねえ……";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "そうかい？よし。それで、船長は何を "+pchar.GenQuest.CaptainComission.CapName+"俺に知らせたかったのか？";
			link.l1 = "あいつは「あなたの頼みを果たすことはできない」と伝えてくれと言ってたぜ。";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "何を言ってるんだ！？俺はあいつを昔から知ってるが、すごく正直な男だぜ。そんなことをお前に言うはずがねえ！";
			link.l1 = "まあ、本人の意思ではどうにもならない理由があったってことさ。\nつまり――それが奴の最後の願いだったんだ。";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "ああ、まったく場違いだぜ！こんなに時間を無駄にしちまった\n"+"船長、その場合は、あなたに助けをお願いしなければならない。海賊たちが  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" 俺の身内を捕まえやがった "+pchar.GenQuest.CaptainComission.SlaveName+" そして、やつらは身代金を要求しているんだ。この任務を引き受けてくれないか？報酬はかなり弾むはずだぜ。";
				link.l1 = "あいにく、俺には他に予定があるんだ。";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "もっと詳しく説明してくれれば、助けてやろう。";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "ああ、まったく場違いだぜ！こんなに時間を無駄にしちまって\nそれで、宝箱はどうしたんだ？";
				link.l1 = "うーん……どの宝箱のことだ？";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "残念だな、船長……お前が俺を助ける気がないとは、惜しいぜ。";
			link.l1 = "それは俺の意思じゃねえんだ、相棒。わかってくれよ。じゃあな。";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "昨日、俺はから手紙を受け取った "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+"、その中で身代金がもっと高くなると知らせてきて、さらに奴隷として売り飛ばすと脅してきたんだ。 亡くなった船長は知らせておくべきだった "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+"、前の条件に同意して前金も払ったんだ。しかし今になって、なぜ海賊どもが要求を吊り上げたのか分かったぜ。";
			link.l1 = "「それで、どうしろって言うんだ？」";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "「ああ、」 "+GetSexPhrase("相棒","娘")+"、ここには何か裏があると感じるぜ。警告しておくが、これは非常に危険で、重大な結果を招くかもしれねえ。船長 "+pchar.GenQuest.CaptainComission.CapName+" 金でいっぱいの箱を三つ持っていて、それを渡すべきだった "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" 上 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" 一人の身代金として―  "+pchar.GenQuest.CaptainComission.SlaveName+"。それに、もしあいつがあんたを俺たちのところに寄越したいなら、宝箱のことを忘れるはずがねえだろう。";
			link.l1 = "最後の言葉を言いながら、彼は文を言い終えていないようだった。もっと話してくれることを期待していたんだ。";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "俺にはもう選択肢がねえ……必要な金額、15万ペソはすでに用意した。あんたにそれを届けてほしいんだ "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" それから俺の身内をここに連れて来い。終わったらすぐに四万払うぜ。";
			link.l1 = "よし、準備はできてるぜ。";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "あいにく、俺には他に予定があるんだ。";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "それなら金を受け取って、主のご加護がありますように。しかし、どうか急いでくれ。俺は心配なんだ\n "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" 待ってなどいないし、その哀れな奴を奴隷として売り飛ばすだろう。";
			link.l1 = "ここで待っていろ。そんなに時間はかからねえと思うぜ。";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "関係ねえさ\n身代金を集めた連中は気にしちゃいねえ。奴らが欲しいのは結果だけだ――生きてて、無事でいること、それだけだ。 "+pchar.GenQuest.CaptainComission.SlaveName+"。だから時間を無駄にするな。";
			link.l1 = "「もし俺が断ったらどうする？」";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "実は、お前の同意なんざいらねえ。ただ知らせてやるだけだ、もし渡さねえなら\n "+pchar.GenQuest.CaptainComission.SlaveName+" 生きて酒場に戻ったら、賞金稼ぎを差し向けてやるからな……";
			link.l1 = "ふむ……それは深刻だな。で、俺がやったらどうなるんだ？";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "それでは、さらに話を進めよう。";
			link.l1 = "よし……どうなるか見てみよう。";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("やあ、船長 "+GetFullName(pchar)+"。何か新しい情報はあるか？","それで、船長、もう身代金は渡したのか？","やあ、いい知らせを持って来てくれたのか？");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "残念だが、俺の計画が変わっちまったんで、取引は破棄しなきゃならねえ。";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "まだだ。俺はまだその件で忙しいんだ。";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("おお、会えて嬉しいぜ、船長 "+GetFullName(pchar)+"。何かいい知らせはあるか？","それで、船長、俺たちの苦しんでる仲間を助けてくれたのか？","無事で何よりだぜ、船長。俺たちの共通の件はどうなってる？");
					link.l1 = "今のところ知らせはねえが、俺が調べてるぜ。";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "聞けよ、相棒、なんでその取引の責任を俺に押し付けようとしてるんだ？";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("やあ、船長 "+GetFullName(pchar)+"。何か知らせはあるか？","それで、船長、もう身代金を届けたのか？","やあ、いい知らせを持って来てくれたのか？");
					link.l1 = "ああ。お前の頼みは果たしたぞ、 "+pchar.GenQuest.CaptainComission.SlaveName+" 俺の船に乗ってて、今まさに上陸の準備をしてるぜ。";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("おお、会えて嬉しいぜ、船長 "+GetFullName(pchar)+"。何かいい知らせはあるか？","それで、船長、俺たちの苦しんでる仲間を助けてくれたのか？","生きていて元気そうで何よりだぜ、船長。俺たちの共通の件はどうなってる？");	
					link.l1 = "例の男を連れてきたぜ。俺の船に乗せてある。";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("やあ、船長 "+GetFullName(pchar)+"。何か新しい知らせはあるか？","それで、船長、もう身代金を渡したのか？","やあ、いい知らせを持って来てくれたのか？");
					link.l1 = "「ごきげんよう」 "+pchar.GenQuest.CaptainComission.Name+"、残念だが、期待には応えられねえ。";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("おお、会えて嬉しいぜ、船長 "+GetFullName(pchar)+"。何かいい知らせはあるか？","それで、船長、俺たちの苦しんでる仲間を助けてくれたのか？","生きてて元気そうで何よりだぜ、船長。俺たちの共通の件はどうなってる？");
					link.l1 = "お前がかばっていた男は死んじまったぜ。";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "ありがとうございます、船長、あなたは我が家に大きな恩を返してくれました。\nこれがあなたへの報酬です……三つの箱、ちょうど四万ペソになります。\nどうかお許しください、今すぐ彼に会わねばなりません。";
			link.l1 = "もちろんだ、お二人とも良い出会いと幸運を祈るぜ。";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "お前の焦る気持ちはよくわかるが、予想外の事情があって、余計な出費を強いられたんだ。";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "俺にはわからねえ……もう報酬の額は決まってるはずだろ？";
			link.l1 = "あるさ、だが十五万ペソの代わりに二十万も払わされちまったんだぜ。しかもバルバドスまで行く羽目になったんだ。";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "船長、これはあんた自身の怠慢の結果だぜ。海賊どもは俺に追加の要求なんてしてこなかった。 人の苦労につけ込んで儲けようとするなんて、変わった奴だな？";
			link.l1 = "わかったよ、お前に何を説明しても無駄だってことがよくわかったぜ…";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "素晴らしいじゃねえか！俺たちがうまくやれるか疑ってたんだろう。";
			link.l1 = "しかし、この件にはかなり金を使っちまったんだ。";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "わかってる、わかってる……だが、それもお前のせいだぜ。 どうしてあんなに苦労して財務官からかっぱらった金貨の入った三つの箱を沈めちまうんだよ、まったく "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" そんな専門家がいるかもしれねえ "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "ちゃんとした見返りがなけりゃ、あいつを渡すつもりはねえからな。";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "なるほど、お前は頭の切れる男だな。もう交渉の余地はねえってことくらい分かってるだろう。お前の船も積み荷も、 俺たちは奪うことができたんだぜ。\nだが、補償は事前に用意されていた。だからこそ、政府は "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" 成功した作戦を祝福し、この貴重な贈り物とささやかな報酬を贈呈する。";
			link.l1 = "ふむ……まあ、何もないよりはマシだな。お前の大事な専門家を連れていけ。";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "ああ、残念だぜ！もう時間を無駄にしすぎた。お前には本当にがっかりだ、船長！";
			link.l1 = "分かったが、状況はどうしようもなかったんだ。ほら、これが金だ。";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "急いでいただけませんか？また海賊たちが取引の条件を変えるのではないかと心配しています。";
			link.l1 = "心配すんな、なんとかなるさ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "お前が時間と競争しているって自覚してるだろうな？";
			link.l1 = "またかよ！任せとけ。少し待ってな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "神よお救いください！無理強いはしねえ、ただ謙虚なピューリタンからちょっと手を貸すだけだ\n自業自得だぜ。お前が船長を殺したんだ "+pchar.GenQuest.CaptainComission.CapName+"、俺たちの金は失われ、すごく価値のある男の身代金も失敗したんだ。今じゃ面倒なことになってて、お前の責任だぜ。 許されたなんて思うなよ……全部のツケは払わせてもらうからな。";
			link.l1 = "くたばれ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "やあ、何か用か？";
			link.l1 = "このプランテーションの持ち主に会わせてもらえるか？";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "ここにはいねえよ、逃げた奴隷を探してるんだ、ブレードとかブラッドとか、よく覚えてねえが……。それと俺はここの執事だぜ "+npchar.name+" 「そして親分が留守の間、俺がすべての用件を取り仕切る権限を持ってるんだ。」";
			link.l1 = "そうか？それはいいな……それで、奴隷を売るのもお前の商売か？";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "もちろんだ。いくつ買いたいんだ？";
			link.l1 = "「一つだけだ。」";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "ええ…本当に奴隷は一人だけでいいのか？";
			link.l1 = "もちろんだ、俺は。名前は "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "しかし、当然ながら、単独の奴隷の値段は、大量の奴隷の一人あたりの値段より高くなるってわかってるだろう？";
				link.l1 = "もちろんだ。値段を言ってくれないか？";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "ふむ……お前が誰のために口を利いてるのか、分かってるんだろうな？";
					link.l1 = "どういう意味だ？";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "ああ、あの怠け者か。あいつには一文もやりたくねえな。ここに連れて来られてからというもの、 まともな仕事なんざ一度もしてねえよ。なんで大佐がこんな国の囚人どもに金を使うのか、俺にはさっぱり分からねえ。\nだがな、黒人たちは話が違うぜ。あいつらは働き者だし、強くて従順なのは血筋ってやつだ。信じてくれ、 どんな仕事だってやれるんだ。サトウキビの収穫でも、執事でも――ちょっと『説得』してやりゃ、誰にも負けねえ働きを見せるさ……";
					link.l1 = "旦那、あんたの黒人どもなんざ俺にはどうでもいいんだ。俺が興味あるのはあんたが言ってたその怠け者だけさ。 どうせ長くは生きちゃいられねえ。俺は砲弾の餌にするつもりだし、そいつにはもっと金を払ってやるぜ。";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "ああ、わかったわかった。値段を見せてくれ\nおおっ！十五万ペソか。";
			link.l1 = "「おったまげたぜ……」";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "値段は値札に書いてあるはずだ。ほら。\nなあ、俺にはよく分からねえ。他の奴隷はまともな値段で売られてるのに、あいつだけは法外な値で売られてるんだよ……";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "ここで何が起きているか、だいたい分かったぜ……よし、これが金だ。そいつは俺が連れていく。";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "ふむ……だが俺は人質の身代金を払うんじゃねえ、ただの奴隷を買いたいだけだぜ。その金額なら、 まともな装備の整った船が一隻買えると思わねえか？";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "あれはただの奴隷じゃねえ。ビショップ大佐が見張りをつけるほどだぜ。";
			link.l1 = "じゃあ、あいつを買うことすらできねえのか？";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "もちろんできるぜ。大佐があいつに値をつけてる――値段表によれば二十万ペソだ。";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "おったまげたぜ！まあ、あの大佐もあの奴隷がどんな奴かはきっと分かってるはずだろうな…";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "ふむ……だが俺は人質の身代金を払うわけじゃねえ、ただの奴隷を買いたいだけだぜ。その金額なら、 ちゃんと装備の整ったまともな船が一隻買えると思わねえか？";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "ああ、そうだったな。すまん。ビショップ様が残した料金表を見せてくれ。\nああ、これだ。ふむ。おおっ……十五万ペソ！？";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "どうやら何かの間違いらしいな。奴隷がそんなに高くつくはずがねえだろう。きっとゼロが一つ多いんだ、 金額は一万五千ペソのはずだぜ。それでも高すぎるくらいだ、あいつは怠け者で馬鹿だからな。";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "ふむ……だが俺は人質の身代金を払うんじゃねえ、ただの奴隷を買いたいだけだぜ。その金額なら、 まともな装備の整った船が一隻買えると思わねえか？";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "素晴らしい！それは最高だ！すぐに彼をここに連れてくるだろう…ええと…お茶でもどうだ？";
			link.l1 = "いや、結構だ……ビショップ大佐によろしく伝えてくれ……";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "それで、誰からか、聞いてもいいか？";
			link.l1 = "ん…やっぱりいい、気にすんな。じゃあな。";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "申し訳ないが、俺にはどうにもできねえ。これが料金表だ。";
			link.l1 = "もういい加減にしろよ、「値段表が、値段表が…」ってさ。お前らはビショップがいなきゃ一番簡単なことも決められねえのか。あいつに伝え…いや、やっぱ何も言うな。";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "つまり、その奴隷を買うつもりはねえんだな。";
			link.l1 = "いいや。じゃあな。";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "俺はそのことについて何も知らねえ。その奴隷の売却に関してだけ、特別な指示を受けてるんだ。";
			link.l1 = "馬鹿なことを……まあ、いいさ。これが金だ。奴隷を連れてこい。";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "もちろんです。すぐにここへ連れてまいります。";
			link.l1 = "さらばだ。";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "ふむ……そうかもしれねえな。きっと何かの間違いだぜ。";
			link.l1 = "さて、値段で合意したなら、今すぐあいつを連れて行ってもいいか？";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "はい、もちろんです。すぐに彼をここへ連れてきます。";
			link.l1 = "よし、これが報酬だ……じゃあな。";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "お茶はいかがですか、船長？";
			link.l1 = "いや、結構だ。";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "あいつを買うことに決めたのか？";
			link.l1 = "いいや。じゃあな。";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "やあ、船長。どうなさいましたか？この苦しみがやっと終わったなんて信じられません。";
				link.l1 = "俺じゃなくて、お前の身内に感謝すべきだぜ "+pchar.GenQuest.CaptainComission.Name+" から "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"。身代金を集めた。";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "やあ、船長。俺の身代金を払ってくれたと聞いたぜ。そのことには感謝しなきゃならねえが、 あんたがただの使いっ走りだったってことも分かってるさ。";
				link.l1 = "せっかく自由を取り戻したのに、あんまり嬉しそうじゃねえな。何か心配事でもあるのか？";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "お願いです、もしご都合の邪魔にならなければ、彼のところまで連れて行ってください。ぜひ直接お礼を言いたいのです。 ";
			link.l1 = "もちろんだ、俺がやるよ。さあ、船まで案内してやるぜ。";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "俺の自由が確かなものになるためには、それに金を払った連中の名前を知る必要があるんだ。";
			link.l1 = "まあ、払ったのは俺だけど、自分の意思じゃなかったんだぜ。";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "そうか、俺の疑いは当たってたんだな。お前は無理やりやらされたんだな "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "ああ、そうだ "+pchar.GenQuest.CaptainComission.Name+" から "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "なるほどな。奴らがあんたに何を約束したかは知らねえが、こうしよう――俺をあの酒場まで連れていけ "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+"、そこなら本当に安全だろう。代わりに、俺の持っている情報を少し分けてやるぜ。";
			link.l1 = "それでいいさ、どうせあいつらは今のところ何も約束しちゃいねえしな。\nついて来い、俺の船まで連れてってやるぜ。";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "俺は怪しい情報のせいで自分に災いを招くような危険は冒さねえぜ。";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "残念だが、今はまだお前に明かせねえ。これは俺たち二人にとって厄介なことになるかもしれねえからな。";
			link.l1 = "なおさらだ……ついて来い、ふざけた真似はするなよ。もう一度逮捕されたと思え。";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "なにっ！？また海賊どもが取引を変えやがったのか？\nだが、これ以上商売から金を出すわけにはいかねえ！\nそんなことじゃ、すぐに破産しちまうぞ！";
			link.l1 = "いや……あなたの親族はバルバドスのプランテーションで脱走に失敗して命を落としたんだ。";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "ああ……俺はもう完全に打ちのめされたぜ……どうしてこんなことになっちまったんだ？";
			link.l1 = "海賊どもは身代金を待たずに、あいつを奴隷として売り飛ばしやがった。俺はバルバドスまで追いかけたが、 助け出すことはできなかったんだ…";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "なんだと！何が起こってるんだ？\nよし、船長、協力に感謝するぜ。それと、渡した金は返してくれよ。";
			link.l1 = "俺の出費は予想をはるかに超えちまったからな……お前の金はもらっておくぜ……じゃあな。";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "ああ、持っていけ……力になれなくて悪かったな……じゃあな。";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "それは残念だな。本当はどれほどひどいか、お前には分かっちゃいねえんだ……";
			link.l1 = "どうしようもねえさ。むしろ、こうなってよかったと思ってるぜ。じゃあな。";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "飲み物を…船長、水を持ってきてくれ…";
			link.l1 = "おい、相棒、お前は "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "ああ…それが俺だ…";
			link.l1 = "聞け！ここで座礁したヒラメみてえにくたばりたくなけりゃ、しっかりしろ、俺の話をよく聞け。 バルバドスの灯台がどこにあるか知ってるか？";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "俺は……";
			link.l1 = "チャンスができたら、すぐにそこへ走れ。俺がそのチャンスを作ってやるからな。";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("さあ聞けよ、船長。でも手短にな、俺は今仕事中だ。","しゃべれよ、だが手短にしろよ。くだらねえことで俺を煩わせるんじゃねえぞ。");
			link.l1 = RandPhraseSimple("ある奴隷を探しているんだが、居場所を教えてくれないか？名前は "+pchar.GenQuest.CaptainComission.SlaveName+".","このプランテーションのどこかに、名前が「」という奴隷がいるはずだ "+pchar.GenQuest.CaptainComission.SlaveName+"。どうすれば彼と話せるか教えてくれないか？");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "今日は罰を受けて見張りの下にいる。";
			link.l1 = "ありがとう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "ありがとう……船長、命を救ってくれた……";
			link.l1 = "バルバドスの灯台まで走って、そこで俺を待っていろ。";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "船長、どう感謝したらいいかわからねえよ。この苦しみがやっと終わったなんて、まだ信じられねえ。";
				link.l1 = "あなたの親類からはすでに礼を言われている "+pchar.GenQuest.CaptainComission.Name+" から "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"。俺はあいつの指示で動いてるんだ。";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "ありがとうございます、船長。あんたが誰のために動いているのかは知らねえが、 貧しい自由でも立派な奴隷生活よりはマシだぜ。";
				link.l1 = "どういう意味だ？";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "もしあなたの予定の邪魔にならないなら、どうか彼のところへ連れて行ってください。\nもうこんなことには本当に疲れました。";
			link.l1 = "もちろん俺は……ここから生きて出られたらな。";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "「俺の自由のために金を払った奴らの名前を教えてもらえるか？」";
			link.l1 = "実は、報酬はもらってねえんだ。奴らに選択肢なんて与えられなかったぜ。";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "そうか、俺の疑いは当たってたんだな。お前は無理やりやらされたんだな、 "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "ああ、そうだ "+pchar.GenQuest.CaptainComission.Name+" から "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "奴らがあんたに何を約束したかは知らねえが、こうしようぜ：俺を酒場まで連れて行け "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+"、そこなら本当に安全だろう。代わりに、俺の持っている情報を少し教えてやるぜ。";
			link.l1 = "それでいいさ、どうせ今のところ何も約束されちゃいねえしな。ついて来い、俺の船まで案内してやるぜ。";
			link.l1.go = "CaptainComission_95";
			link.l2 = "俺は怪しい情報のせいで自分に災いを招くような危険は冒さねえぜ。";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "残念だが、今はお前にそれを明かすことはできねえ。\nこれが俺たち二人にとって厄介なことになるかもしれねえからな。";
			link.l1 = "なおさらだ……俺について来い、ふざけた真似はするなよ。もう一度逮捕されたと思え。";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "ありがとうございます、船長。これでやっと安心できました。金銭は差し上げませんが、知識とその巧みな活用こそが、 朽ちる金属よりはるかに価値があると私は確信しています。";
			link.l1 = "情報を待っている";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "実は、俺は科学者で、専門は "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" そして "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" 「しばらくの間、俺に協力を申し出ていたんだが、」"+"だが、俺は軍の技師であり、忠誠の誓いは守っている。連中は俺を奪おうとしたが、本当の問題は、 海賊どもが俺の正体と重要性を知ったときに始まったんだ\n"+"結局、奴らは俺を捕まえることに成功したが、欲しかったのは金だけで、俺の知識なんて必要なかったんだ。\n友も敵も身代金を払うのが間に合わず、俺はプランテーションに売られた。\nあとは知ってるだろう。";
			link.l1 = "ああ、まさにその通りだな、言われてる通り、ほんとにそうだぜ。";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "まあ、そう言えるかもな。だから、俺の言うことをちゃんと聞いてりゃ、その技術がもっと上達するぜ "+sTemp;
			link.l1 = "ありがとう、その情報は本当に役に立つぜ。";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "じゃあな、いろいろ世話になったぜ。";
			link.l1 = "こちらこそありがとう。じゃあな、次は捕まらないように気をつけろよ。";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("おう、俺は船長だ "+GetFullName(NPChar)+"、俺の船の甲板に何の用だ"+pchar.GenQuest.CaptainComission.ShipTypeName+"「？」","ああ、俺の船に客人を迎えるのはいつだって嬉しいぜ。船長 "+GetFullName(NPChar)+" お役に立ちますぜ。");
			link.l1 = "やあ、俺が船長だ "+GetFullName(pchar)+"「ある船長の代理として」 "+pchar.GenQuest.CaptainComission.CapName+"。あんたは で逮捕されるって伝えてくれと頼まれた "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"。役人たちは知っている "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "ここで何してやがるんだ？全部手筈は整えたはずだろう！さっさと自分の船に戻れ！";
			link.l2 = "うっ…ああ、そうだぜ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "ああ、残念だな！ちょっと考えさせてくれ\nそれで、船長はどこにいるんだ "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "彼は死んだ。";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "くそっ！状況は悪くなる一方だ……聞け、 "+GetFullName(pchar)+"、そのような展開に直面する覚悟はできていません、船長 "+pchar.GenQuest.CaptainComission.CapName+" そして俺はそこで会うことにしたんだ "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"…計画では、あいつの船に積み荷を載せるはずだったんだ。だが今や船長は死んじまったし、 俺はあの入植地に顔を出せねえ\nもうお前に頼るしかなさそうだ。";
			link.l1 = "お前がどんな助けを求めているかによって、俺が承諾するかどうか決めるぜ。";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "何人かの男とロングボートを手伝ってくれ。積み荷を運び出す必要があるんだ "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"。亡くなった船長の取り分の積荷はお前が持っていていいぜ。";
			link.l1 = "ふむ……どうやらお前さん、手に余ることに首を突っ込んじまったようだな。もっと詳しい情報が必要だぜ。";
			link.l1.go = "CaptainComission_305";
			link.l2 = "残念だが、俺にはそんなことに時間を無駄にする余裕はねえんだ。";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "よし、詳しい話をしてやる\n"+"定期巡回の最中に、俺は旗を掲げた船に遭遇した\n "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"。俺の降伏命令を無視しやがったんだ。"+"短い追跡の後、俺たちが追いついたとき "+sTemp+" 「」"+pchar.GenQuest.CaptainComission.VictimShipName+"「それで奴らは黒旗を掲げたんだ。砦はかなり遠かったから、俺たちは自力で戦うしかなかった。 ジブブームを壊されちまってな、それで敵の乗り込みを避けられなかったんだぜ。\n」"+"危なかったが、聖母マリア様と火縄銃兵の部隊のおかげで全員仕留めることができたんだ。\nそれが分かったときの俺たちの喜びを想像してみてくれよ "+sTemp+" で満たされていた。 "+"俺たちは、この傷と仲間の死に対する報酬としてこれが妥当だと決めたんだ\nもう暗くなっていて、俺たちは奪った "+sTemp+" 一番近い湾まで行って、積み荷を陸に隠したんだ。そしたら俺たちは爆破した\n "+sTemp+" それから沈没した海賊船のことは報告したぜ。もちろん、積み荷のことは黙っておいたがな。";
			link.l1 = "どうやら、誰かがまだしゃべっちまったようだな……";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "残念だな、船長……お前が俺を助ける気がないなんて、惜しいぜ。";
			link.l1 = "それは俺の意志じゃどうにもならねえんだよ、坊や。わかってくれ。じゃあな。";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "俺の手下じゃねえと思うぜ。たぶん、積み荷の持ち主が損失の痛みを和らげたくて必死なんだろうな\nで、どうだ？お前の助けを当てにしていいのか？";
			link.l1 = "ああ、いい感じだな。";
			link.l1.go = "CaptainComission_308";
			link.l2 = "いや、相棒。まず第一に、どれだけの積荷が俺の船倉に入るか分からねえんだ。第二に、 当局がもう見つけて持ち去っちまって、隠し場所に待ち伏せしてる可能性だってあるからな。";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "「で会おう」 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" それから、ちょうど真夜中の後だ。今の俺の立場は秘密を要する。見回りは避けなきゃならねえ。"; // belamour gen
			link.l1 = "わかった、そこで待ってろ。";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "残念だが、もう選択肢はねえな。船一隻じゃあ全ての積み荷は運べねえ。俺はそのために命もキャリアも賭けたんだぜ。 きっと、お前の船員たちも、ちゃんと分け前をやれば喜んで手伝ってくれるだろうよ。";
			link.l1 = "「それで、どうしろって言うんだ？」";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "お前の船は俺がいただくぜ。ここに置き去りにしてやる。 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "お前の成功なんてありえねえと思うぜ。たとえお前の乗組員全員を斬り倒してでも、俺は自分の船に戻るからな。";
			link.l1.go = "CaptainComission_311";
			link.l2 = "仕方がないようだな。まあ、暴力には従うしかないか……";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "船長、急がねえといけねえぜ。見回りに見つかっちまうかもしれねえ。";
			link.l1 = "よし、急ごうぜ。";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "船長、全ての救命ボートを出すよう命じてください。\n何度か往復しなきゃならねえし、入り江に巡回の連中が来やしねえか心配だぜ。 ";
			link.l1 = "心配するな、すべてうまくいくはずだ。ボートはもう上陸してるぜ。";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "くそっ。今度はお客さんが来ちまったな……";
			link.l1 = "本当に、馬鹿の話をすればすぐに現れるもんだな……";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "船長、俺たちは戦争犯罪者を探しているんだ "+pchar.GenQuest.CaptainComission.Name+"「当局から貴重な積荷を隠している者だな。書類を見せてもらおう。」";
			link.l1 = "何の書類だ、役人？俺たちは真水の補給のために上陸しただけだぜ。";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "「そして、ここに奴がいる」 "+pchar.GenQuest.CaptainComission.Name+" 自分でな。武器を渡して俺について来い、二人とも！";
			link.l1 = "「本当にタイミングが悪かったな、役人さん……」";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "増援が来る前に急がなきゃならねえ。積み込みはほとんど終わったし、お前の取り分は "+pchar.GenQuest.CaptainComission.GoodsQty+" の単位 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "素晴らしい。もう出発する時間だ。取引できて楽しかったぜ。";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "それと、もう一つだけお願いがあるんだ。役人どもがきっと俺たちを追ってくるから、俺の船を護衛してくれないか "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+"、それは上にある "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "いや、相棒、これからはもう各自自分の身は自分で守るしかねえ。じゃあな……";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "もちろん、いい報酬がもらえるならやってやるぜ。";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "もちろんだ。護衛のために金を払うつもりだ  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" ペソだ。しかし、もう一つ条件がある：かかる時間は "+pchar.GenQuest.CaptainComission.iDay+" 日数だ。大事なことだ。";	
			link.l1 = "取引成立だ。すぐに出発しよう。";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("船長、時間を無駄にしてるぜ。やつらはいつ見つけに来るかわからねえんだ。","船長、時間との勝負だぜ。俺を探してる連中がいるのを忘れるなよ。","船長、ぐずぐずしてはいけません。俺の船は大きすぎて巡回の目を逃れられねえんだ。");
			link.l1 = LinkRandPhrase("ああ、その通りだ。急がなきゃならねえ。","それじゃあ、さっさとボートに乗り込め。","それで決まりだ……連中を集めろ。出発するぞ。");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "船長、俺の部下たちと話がしたいんだ。";
			link.l1 = "どうぞ。";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "ごきげんよう、船長 "+pchar.CaptainComission.Name+"。で、貨物は全部持ってきたのか？それと船長はどこだ "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" 死んだ。俺が聞かなきゃならなかった "+NPCharSexPhrase(sld,"この旦那","この女の人")+" 助けを求めてな。紹介しよう。こちらが船長だ "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "And "+NPCharSexPhrase(sld,"あいつは誰だ？奴は","彼女は誰だ？彼女は")+" 俺たちの事情を知ってるのか？";
			link.l1 = "まあ、だいたいはそうだ。だが、一つ問題があるんだ―"+NPCharSexPhrase(sld,"彼は確信している","彼女は確信している")+"、その積み荷の半分は～のものだ "+NPCharSexPhrase(sld,"彼を","彼女の")+"。説得しなければならない "+NPCharSexPhrase(sld,"彼を","彼女")+"、それは必ずしもそうではないんだ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "「相棒」 "+GetFullName(pchar)+"、お前はもう必要なことは全部聞いたはずだ。俺たちはお前の船倉に入る必要があるんだ。";
			link.l1 = "「それで俺の連中が、ガキどもが船倉を空にするのを黙って見てるとでも思ってんのか？」";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "なるほどな。例えば、現金でその額… "+pchar.GenQuest.CaptainComission.GoodsSum+" ペソを払えば、お前の船員たちと争う必要はねえ。これは積み荷の半分に相当するから、公平ってもんだ。納得するなら、 誰も傷つかずに済むぜ。";
			link.l1 = "「もし俺が断ったらどうする？」";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "その場合は、暴力は避けられねえな。最初の犠牲者はお前だぜ。この居心地のいい入り江で安らかに眠ることになるんだ。 仲間も助けに来れねえ……どうだ、気分は？";
			link.l1 = "仕方ねえな。よし、全員ぶっ殺してやるぜ。";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "仕方ねえな。よし、金をやるよ。";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "さて、それはふさわしい決断だな "+GetSexPhrase("高貴な紳士","勇敢な女傑")+".";
			link.l1 = "ごちゃごちゃ言うな！本題に入ろうぜ！";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "賢明な判断だ。幸運を祈るぜ。";
			link.l1 = "それで喉を詰まらせちまえ……";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Captain "+GetFullName(pchar)+"、遅かったな。もう報酬を受け取る資格はないってこと、わかってくれよな。";
			link.l1 = "ああ、もちろんだ。おかげでたんまり稼がせてもらったぜ。じゃあな……";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "「王冠の栄光のために戦場で大いに苦しんだこの老兵に、ラム酒を一杯買ってくれねえか？」";
			link.l1 = "バーテンダー！ラムを注いでくれ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "「ああ、ありがとう」 "+GetAddress_Form(pchar)+"……記憶をすっかり失った足の不自由者を助けてくれるなんて、本当に親切だな……";
			link.l1 = "「完全に、だと？」";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "もちろんだよ、お嬢さん"+GetSexPhrase("「ter」","ｓ")+" 船長……まったく何も覚えてねえんだ。頭にカンister弾が直撃したこと以外はな。見てくれよ、この穴を。きっと全部の記憶がここから漏れちまったんだろうな。";
			link.l1 = "相棒よ、くだらねえ話は奥さん連中にでもしてな。俺はぶどう弾をまともに食らって、 記憶も頭も吹っ飛んじまった奴らを見てきたんだぜ……。それなのにお前は、ありもしねえ鎖弾の話かよ。船長のことを話そうじゃねえか\n "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "ああ、まあ、分かるだろ。俺も何とかして食っていかねえとな。船長については\n "+pchar.GenQuest.CaptainComission.Name+"…俺がペラペラしゃべったって儲けにならねえよ…あいつのことで一つ質問されるごとに百枚ずつ取ってりゃ、今ごろ総督が一年で民から集める金よりも、 もっと金貨を持ってたぜ… ";
			link.l1 = "「それで、あの船長が隠しておいた積荷を売ろうとしたことはあるのか？」";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "なんだと？また探偵気取りか？もう一度言うが、俺はどの船長のことも覚えちゃいねえぞ "+pchar.GenQuest.CaptainComission.Name+"！俺は頭を打ってるんだ、しかも医者の診断書まであるぜ！これ以上何が必要なんだよ！？";
			link.l1 = "おいおい、そんなに興奮すんなよ。\nあいつはな……遅すぎたんだ。船長 "+pchar.GenQuest.CaptainComission.CapName+" 「そう伝えてくれ」と頼まれた "+pchar.GenQuest.CaptainComission.Name+" あの居留地には顔を出さない方がいいぜ、当局はその破壊の経緯を知っているからな "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" 「」"+pchar.GenQuest.CaptainComission.VictimShipName+"、そして彼は逮捕される。";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "ふう。最初からそう言えばよかったのによ、回りくどい話はやめてくれ。船長に頼んだのは俺だぜ "+pchar.GenQuest.CaptainComission.CapName+" 我々の船が戻るところを待ち伏せして拿捕するんだ。 "+"あの血みどろの戦いの直後に、荷はすぐに波止場へ運ばれたんだ。\nあの忌々しい海賊が、なんであそこで自分の品を持ってやがったんだ！？\nあいつのせいで、たくさんの仲間が死んじまったぜ。";
			link.l1 = "「どうやって生き延びたんだ？」";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "間違いでさ。正直に言えば、自分のドジだ。俺が素早く動けなかったせいで、 うちのロングボートは危険地帯から抜け出せなかったんだ。だが、被害を受けたのは俺だけだった。 残骸にぶつかって海に投げ出されたんだよ。どうやって岸までたどり着いたかも覚えてねえ。";
			link.l1 = "「で、どうやってあの取り調べからうまく逃げ切ったんだ？」";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "俺は乗り込みの時にケガしたって言って、積み荷のことなんか何も知らねえって言い張ったんだ。それに、 ちょっと頭が弱いふりもしたんだぜ。ほら、ついさっきまで寝込んでて、 あんたが来る直前にやっと立ち上がれたばかりってな。\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+"。うまく動けなかった、体の調子が全然ダメだったんだ。";
			link.l1 = "おい、でも結局その積荷の秘密をバラしたのは誰なんだ？";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "海賊どもが負傷した商人の名を騙って総督に手紙を送ったらしい。\n奴らはしつこい船長に復讐することに決めたんだ。\n全部あいつのせいだ、あの忌々しい頑固さが俺たちをこんな目に遭わせたんだぜ。";
			link.l1 = "「でも、そもそもどうやってその海賊に出くわしたんだ？」";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "知らねえな。普通の巡回だったし、普通の船がその旗の下で航海してたんだ。 "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"。なぜ船長がそれを調べることにしたのか全く分からねえが、警告の一発を無視しやがって、 俺たちが追いついたときには“ジョリー・ロジャー”を掲げやがったんだ。 "+"砦の支援がなかったから、戦いは楽じゃなかったぜ。そんで、白兵戦になったんだ。どうやって奴らを倒せたのか、 今でもわからねえよ。\n"+"そうさ、あの貴重な積み荷は全部見たぜ。悪魔が俺たちに授けたに違いねえ。積み荷は陸に隠して、 奪った船は派手に吹き飛ばすしかなかった。あいつはもうボロボロだったからな。";
			link.l1 = "総督の連中に隠し場所が見つかったら、今までの努力も犠牲も全部無駄になるんじゃねえか、怖くねえのか？";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "奴らには見つけられねえよ。洞窟の入口はしっかり吹き飛ばしておいたからな。なんたって、 俺は隊で一番の爆薬使いだったんだぜ。俺の隠し場所を見つけられるのは密輸業者くらいさ、あいつらはこの場所の隅々 まで知ってやがるからな。\n"+"見ろよ、俺自身もその戦利品をどうしたらいいか全然わからねえんだ。自分じゃ売ることも運び出すこともできねえしな。 それに、頭に傷のあるやつと取引するやつなんていねえよ。仲間の死で儲ける気はねえが、 隠し場所なら教えてやってもいいぜ\n "+pchar.GenQuest.CaptainComission.Sum+"  俺をそこまで連れて行ってくれたらペソをやるぜ "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "同意だ。ほら、金だ。さあ、話せ。";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "くそっ！わかった、ここで待ってろ、俺が金を取ってくる。";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "そりゃ多すぎだぜ、相棒。それに、俺にはちょうどいい船もねえんだ。ま、幸運を祈るぜ。じゃあな……";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "よし、わかった。今夜、真夜中過ぎにあたりで俺に会え。 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+"。あと、ちゃんと船倉に空きがあるか確認してくれよ "+pchar.GenQuest.CaptainComission.GoodsQty+" 個 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"……どれも捨てるのはもったいないな……"; // belamour gen
			link.l1 = "それは俺に任せとけ。入り江で会おうぜ…";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "やっと来たか。心配し始めてたぜ。てっきりお前、俺を役人に突き出すつもりかと思ってたよ。";
				link.l1 = "俺はまだ気が狂っちゃいねえ。ほら、金だ。次はお前の番だぜ。";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "それで、金はどこだ？";	
				link.l1 = "くそっ！わかった、ここで待ってろ、俺が取ってくる。";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "船長、どうやら遅かったようです。密輸業者どもがもう隠し場所を見つけちまいました。";
			link.l1 = "俺の戦利品は絶対に渡さねえ、悪魔だって俺から奪えやしねえぜ。";
			link.l1.go = "CaptainComission_351";
			link.l2 = "俺はやめるぜ。競争相手のことは自分で何とかしな。";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "船長、ここは重大な問題がありますぜ。俺はあんたに、うちの艦隊が来る前に自分の艦隊を引き上げることを勧めるぜ。";
			link.l1 = "旦那方、どうやら自分の物じゃねえものを奪おうとしてるみてえだな。";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "へえ、そうかよ！？お前、自分が誰と話してるかわかってんのか？";
			link.l1 = "俺はお前に話してるんだ、相棒。その積み荷には正当な持ち主がいるんだぜ、俺はそいつの代理人ってわけだ。";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "たとえお前が我らの神の救世主だったとしても、俺たちのやり方に口出しはさせねえ！命が惜しけりゃ道を空けろ！";
			link.l1 = "俺の言ったこと、わからなかったのか？その積み荷は俺のもんだ、絶対に置いていかねえぞ！";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "ふざけんな！そんなに欲しいなら、ここで永遠に待ってな！";
			link.l1 = "運命が誰をここに永遠に留めるか決めるだろう。";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "船長、部下に急ぐよう命じてくれ、いつ巡回隊が来てもおかしくねえ。\nそれに、密輸業者どもも明らかに自分たちの運び屋を待ってたようだぜ。";
			link.l1 = "ああ、急がねえとな……荷を船倉に積み込んで、とっととここを出るぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "ありがとうございます、船長 "+GetFullName(pchar)+"……もしあんたがいなかったら、密輸業者どもに俺たちの積み荷を奪われてたし、 それを守って倒れた連中も無駄死にだっただろう……";
			link.l1 = "「そして、俺を信じてくれてありがとう。」";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "ここに一つだけお守りがあるんだ。俺の命はこれに救われたんだぜ。頼む、受け取ってくれ。 あんたの幸運のお守りになるかもしれねえ。改めて礼を言うぜ、友よ。いつも風があんたの味方でありますように。";
			link.l1 = "贈り物、ありがとうよ。まさかもらえるとは思わなかったぜ。\nそれと、ポケットにまだ金があるうちに自分の体も気をつけた方がいいぜ。";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "どうやら今日は俺の面会日らしいな。俺に用か？";
			link.l1 = "もしお前が船長なら "+pchar.GenQuest.CaptainComission.Name+"、ならそうだ。";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "…元船長"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "俺だ "+GetFullName(pchar)+"、それでお前にいくつか質問があるんだ。";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "「それで、なぜ俺がそいつらに答えると思うんだ？」";
			link.l1 = "Captain "+pchar.GenQuest.CaptainComission.CapName+" 「の破壊を取り巻く状況について警告するように頼まれた」 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" 「」"+pchar.GenQuest.CaptainComission.VictimShipName+" 当局に知られるようになった、 "+"だが、航海中にお前の船は見かけなかったぜ、+\n "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "それで、船長はどこだ "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "彼は死んだ。";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "なるほど……そういうことか。いろいろ納得がいったぜ。つまり、誰かが俺たちが略奪したってしゃべっちまったんだな\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"遅かれ早かれ、奴らは積み荷を見つけて俺を絞首刑にするだろう。船長 "+pchar.GenQuest.CaptainComission.CapName+" 死んじまったってことは、もう誰にも助けてもらえねえ\nお前以外にはな\n "+GetFullName(pchar)+"、ここから出してくれたら、きっとお前に見返りをやるぜ。";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "総督は積荷の持ち主から伝言を受け取ったんだ。しかも、その中の数字がなかなかすごいんだぜ。";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "だが、まさか俺が目隠しされたままあんたを手伝うと思ってるんじゃねえだろうな？";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "総督は積荷の持ち主から伝言を受け取ったんだ。\nしかも、その中の数字がなかなかすごいんだぜ。";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "植民地ではお前が密輸業者と関わっているって噂が流れてるんだぜ…";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "どうやら全部話さなきゃならねえようだな。\n"+"俺の定期巡回の途中で、旗を掲げた船に遭遇したんだ "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"。俺の降伏命令を無視しやがった。 "+"俺たちは到着した "+sTemp+" 「」"+pchar.GenQuest.CaptainComission.VictimShipName+"「短い追跡の後、奴らは黒旗を揚げやがった。砦はかなり遠かったから、俺たちだけで戦うしかなかったんだ。 ジブブームを壊されちまってな、それで接舷戦を避けられなかったんだぜ。\n」"+"危なかったが、聖母マリア様と火縄銃兵部隊のおかげで全員倒すことができたんだ。 俺たちがそれを知ったときの喜びを想像してみろよ\n "+sTemp+" 財宝で満ちていた。 "+"俺たちは、この傷と仲間の死に対する報酬としては妥当だと決めたんだ\nもう暗くなっていたが、なんとか奪うことができた "+sTemp+" 一番近い入り江まで行って、積み荷を陸に隠したんだ。そんで俺たちは焼き払った "+sTemp+" それから沈没した海賊船のことを報告したんだ。もちろん、積み荷のことは言わなかったぜ。";		
			link.l1 = "俺を騙しても意味がねえと思うぜ。だから、取引を提案する。お前が隠し場所を見せてくれたら、 望む場所までこの諸島のどこへでも連れてってやる。";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "ハハハ……いやだよ船長、俺の取り分なしでこの居留地を出るつもりはねえ。たとえ絞首台にぶら下がる羽目になってもな。";
			link.l1 = "よし。お前の取り分は半分だ。";
			link.l1.go = "CaptainComission_377";
			link.l2 = "ふん……お前のために命を張る気はねえんだ。じゃあな……";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "そうこなくちゃな。俺は準備できてるぜ\nまずは、お前の船に俺を隠してくれ。隠し場所のある入り江を案内してやるよ。";
			link.l1 = "じゃあ、素早く連携して動こう。俺がお前の牢を開けるから、ついて来い。砦を出るまでは遅れるな、質問もなしだぞ。";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "助けてくれて感謝するぜ。先へ進もう "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+"、隠し場所を教えてやるぜ。野蛮人どもに見つかる前に急いだ方がいい。";	// belamour gen	
			link.l1 = "本当に全部の積み荷を運べると思ってるのか？";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "その通りだ、十分なスペースを確保しておけ "+pchar.GenQuest.CaptainComission.GoodsQty+" 「～のかけら」 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"。これほど血塗られた貴重な戦利品を失うのは惜しいぜ。奴らは二度目のチャンスなんてくれやしねえ。";
			link.l1 = "それは俺に任せとけ。";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "船長、証人なんて必要ねえぜ。頼むから、この連中を入り江から出て行かせてくれ。";
			link.l1 = "よし、そうしようぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "船長、申し訳ねえが、ここはあんたの訓練には向いてねえ場所だぜ。あのドックはもう使われてるんだ。";
			link.l1 = "旦那方、俺は観光に来たんじゃねえ。ここには用があって来たんだ。";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "ここでもクラゲなんか捕まえてねえんだ、さっさと船を引き返してとっとと失せやがれ。";
			link.l1 = "俺はお前を説得して時間を無駄にしたくねえ。素直に出て行けば生きられるが、ここに残れば二度と戻れねえぞ。";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "俺の言ってることがわからねえみたいだな。まあいいさ、お前の葬式だぜ……";
			link.l1 = "そっちのほうがいいぜ！";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "着いたぜ。隠し場所はあの岩の割れ目の中だ。入口は岩で塞がれてる。隠し場所の中には\n "+pchar.GenQuest.CaptainComission.GoodsQty+" の単位 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"。覚えてるか？その半分は俺のもんだぜ？";
			link.l1 = "ああ、もちろんだ。俺の手下たちが荷物を積んでる間に少し時間がある。お前とお前の積み荷をどこへ運ぶか、 話そうじゃねえか。";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "よし、いいだろう。さて、俺が分け前をやる理由が何かあるのか？";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Captain "+pchar.GenQuest.CaptainComission.Name+"、あんたに嫌なことを伝えなきゃならねえ。俺は総督のために働いてるんだ。そして、 あんたが隠した積荷は全部奴に渡すつもりだぜ。おとなしく牢屋に戻って、自分の運命を待つんだな。";
				link.l3.go = "CaptainComission_389";
				link.l2 = "とてもいいだろう。だがな……最初はお前を役人に突き出そうと思ってたが、今さらそんなことする理由があるか？それに、 なんでお前と分け前を分けなきゃならねえんだ？";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "俺は行かなくちゃならねえ "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+"、で "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" のため "+pchar.GenQuest.CaptainComission.iDay+" 日数だ。あそこにいる俺の仲間たちは、きっと積み荷を売る準備をしているはずだ。"; // belamour gen
			link.l1 = "よし。それじゃあ、出発の時間だな。";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "そうだな。常に心じゃなくて頭を信じるべきだ。生きて学ぶもんだぜ。\nこんな展開は予想してなかったが、俺はいつでも戦う覚悟はできてる。裏切りの代償、払ってもらうぜ。";
			link.l1 = "運が良けりゃな……";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "そうだな。心じゃなくて頭を信じるべきだぜ。生きて学ぶんだ\n予想外だったが、俺はいつでも戦う覚悟はできてる。裏切りの報いは受けてもらうぞ。";
			link.l1 = "お役に立ちますぜ……";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "どうやら、俺たちは遅れちまったようだな……客は待たなかったし、俺一人じゃ積荷の保管や売却の手配もできねえ……";
			link.l1 = "この件について、何か特別な提案でもあるのか？";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain "+GetFullName(pchar)+"、ちょっと言いにくいんだが……俺の取り分を金で渡してくれないか？まあ、そう思ってな。 "+pchar.GenQuest.CaptainComission.GoodsPrice+" ペソがいい妥協案になるかもしれねえな。";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "ああ、公平な値段だな。俺は気にしねえ。ほら、金だ。じゃあな。";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "おいおい、そりゃ困るぜ、相棒。いつまでもお前の面倒は見てられねえんだ。荷を受け取りたくねえなら、 俺が預かっておくさ。安心しな、ちゃんと保管して、そのうち売りさばいてやるからよ。";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "待ってくれ、船長。助けてくれて礼を言いたいんだ。正直、もうほとんど希望を失いかけてたんだよ……ほら、これを受け取ってくれ。きっといろんな厄介な場面で役に立つはずだ……じゃあな。";
			link.l1 = "ありがとう。そんなこと、思ってもみなかったぜ。取引できて嬉しいぜ。";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "お前にそんなことをされるとは思わなかったぜ……どうやら決闘を申し込むしかなさそうだな。";
			link.l1 = "お任せください…";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "船長、俺の部下たちと話がしたいんだ。";
			link.l1 = "先に行け。";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "ごきげんよう、船長 "+GetFullName(pchar)+"。で、貨物は全部持ってきたのか？それと船長はどこだ "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" 死んじまって、俺は密告で捕まったんだ。もし船長が "+pchar.CaptainComission.FullName+" 助けてくれなかったら、俺も積み荷もお前の前に現れなかったぜ。";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "And "+NPCharSexPhrase(sld,"あいつは誰だ？奴は","彼女は誰だ？彼女は")+" 俺たちの事情を知ってるのか？";
			link.l1 = "もちろんだ。 "+NPCharSexPhrase(sld,"彼が引き抜いた","彼女が引き出した")+" 牢屋から俺を出してくれて、ここに積荷の半分を届けることを引き受けたんだ。残りの半分は俺が約束した "+ NPCharSexPhrase(sld, "彼","彼女") +" 償いとして。";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "ええ、船長、無理だぜ。そりゃあお前の問題だ！俺は船を奪って逃げようって提案したのに、 お前は自分のくだらねえ出世のことばっか気にしてたじゃねえか。で、どうだ？ その大好きな総督に牢屋にぶち込まれてやがる。"+" お前の取り分は半分にも全然届いてねえぞ！俺たちは命懸けでぶどう弾をくぐり抜けたんだ、 全部お前が半分持ってくためじゃねえんだよ！";
			link.l1 = "聞けよ、甲板長、お前は船が完全に難破したのを覚えてねえのか？ほとんど水没しかけてたんだぜ？ 俺がこの男に半分渡さなかったら、お前は積み荷のかけら一つだって二度と見られなかったって分かってねえのか？";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "俺を騙せると思うなよ！お前が共謀してなかったなんて、どうやって証明するんだ？ そもそも逮捕なんてなかったかもしれねえだろ？それとも、 ただ欲に目がくらんで俺たちの持ち物を盗もうとしただけじゃねえのか？それとも、 俺たちが剣の使い方を忘れたとでも思ってるのか！？";
			link.l1 = "お前、どうかしちまったみたいだな。耳にはコインの音しか聞こえてねえじゃねえか。";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "野郎ども！今の船長の話しぶりを見てみろよ！まったく、欲にまみれてやがる！俺たちの取り分を売りやがったんだぞ、 "+NPCharSexPhrase(sld,"悪党","女冒険者")+"!!";
			link.l1 = "今すぐその汚ねえ口を閉じろ、さもねえと二度と喋れねえようにしてやるぞ！";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "すみません、船長、こんな馬鹿げた光景を見せてしまい、しかも巻き込んでしまって。\nたった一ヶ月前まで俺たちは団結した仲間で、誰もが仲間のために喜んで命を投げ出す覚悟だったなんて、 今じゃ信じられねえよ。";
			link.l1 = "正直に言うと、それは想像できねえな、悪く思うなよ。";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "残念ながら、俺自身で積荷の保管や販売を手配する機会はねえんだ……";
			link.l1 = "この件について、何か特別な提案があるのか？";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain "+GetFullName(pchar)+"、ちょっと言いにくいんだけど……俺の取り分を金で渡してくれないか？たぶんさ、 "+pchar.GenQuest.CaptainComission.GoodsPrice+" ペソならいい妥協になるかもしれねえな。";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "よし、構わねえ。ほら、金だ。じゃあな。";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "いや、それは無理だ。貨物を持っていくか、船倉に置いていくかは勝手だが、俺は一文たりとも渡さねえぞ。";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "待ってくれ、船長。助けてくれて礼を言いたいんだ。実は、もうほとんど希望を失いかけてたんだよ……これを受け取ってくれ。きっといろんな厄介な場面で役に立つはずだ……じゃあな。";
				link.l1 = "ありがとうございます。そんなことは思ってもみませんでした。取引できて嬉しいです。";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "待ってくれ……今ふと思ったんだ……俺の人生はもう終わりだし、仲間もいないし、故郷でも追放者だ。きっとお前も、 口の堅い信頼できる腕利きが必要だろう。どうか俺をお前の仲間にしてくれ、絶対に後悔はさせねえと誓うぜ。";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "正直言って、あんたが承諾してくれるのをずっと待ってたんだ。\nもちろんだ。船で会おうぜ。";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "ふむ……お前は誰かの下で働くには頭が良すぎるようだな。じゃあな……";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "どうやら今日はまったく運がねえ日みてえだな……よし、船長、刃を抜いて一気にケリをつけようぜ……";
			link.l1 = "お役に立ちますぜ……";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "お前には関係ねえよ。で、ここで何をうろついてやがる？さっき捕まった男を探してるんじゃねえのか！？";
				link.l1 = "男か？！いや……";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "よかったな。じゃなきゃ、お前もあいつと一緒に牢屋行きだぜ。だからここでうろちょろするな、水夫。さっさと失せろ！ ";
				link.l1 = "ああ、俺は行ったほうがよさそうだな…";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "よし！今すぐあの密輸業者を探しに酒場へ行こうぜ。ここに長居なんてしたくねえ！";
				link.l1 = "それは問題ねえぜ。行こうぜ……";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "へへ……どうやら、 "+GetSexPhrase("野郎","娘")+"、お前もすぐに地獄行きだぜ……おい、相棒―二人まとめてぶっ殺してやろうぜ！";
				link.l1 = "この汚ねえ豚野郎！覚悟しやがれ！";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "「改めてありがとうございます。」 "+PChar.name+"……さらばだ……";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "「報酬だと？！ああ、もちろんだ。ほら――受け取れ」 "+FindRussianMoneyString(iMoney)+" ……さらばだ……";
				link.l1 = "……じゃあな……";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "へっ！そんなデタラメ信じろってのか！？野郎ども、この二人の死刑囚を捕まえろ！";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "役人さん、あんたは無実の二人を拘束しようとして大きな間違いを犯してるぜ。信じてくれ、 俺はあの男なんか知らねえし、興味もねえんだ。"+" もしお前が法を守る市民二人を拘束したら、司令官はきっとお前にひどく不満を抱くだろうな…";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "ふむ……そうだな、もしかしたらお前の言う通りかもしれねえ。司令官はきっとこれに腹を立てるだろう。\nよし、もうこの小さな出来事は忘れちまおうぜ。";
				link.l1 = "ありがとうございます、役人さん、おかげで時間が節約できました。次はもっと注意してほしいんだが、 降格なんてされたくないだろう？";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "いや、決してそんなことはない。その場合は、解散してくれ。じゃあな…";
				link.l1 = "そっちのほうがいいぜ！";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "上出来だ！さあ、とっとと失せろ！";
					link.l1 = "「なんだと？！じゃあ金はどうなるんだ？俺たちは取引したはずだろう…」";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "配達ご苦労だったな。さあ、とっとと失せ……待て、誰か来やがった……";
						link.l1 = "何だって！？";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "よし。配達ご苦労だったな。ほら、受け取れ "+FindRussianMoneyString(iMoney)"。あと覚えておけよ、密輸業者はいい奴のことはいつまでも忘れねえんだ…";
					link.l1 = "そう願いたいね。じゃあな。";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "聞けよ……俺とお前の間には何の取引もなかっただろうが。金が欲しいなら、その取引をした奴からもらえ。";
				link.l1 = "まあ、今日はまったく運がねえ日だな、他に言うこともねえぜ！？\nよし、じゃあな…";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"その報いは受けてもらうぜ！死ぬ覚悟をしろ！";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "「俺に挑むとは、」 "+GetSexPhrase("小僧","汚物")+"？お前は自分に何が大事か全然わかってねえんだな。ぶった斬ってやるぜ！";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("五百人の野郎どもだ！それに死人の箱もな！ひっく！","飲め！ヒック！そして悪魔が――ヒック！――残りを片付けちまったぜ！");
						link.l1 = "ああ…まあ。やあ、旦那 "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "よし、さてと……帆布が三枚、船体用の板材、ベルトやブレースのロープの交換……";
							link.l1 = "やあ、旦那 "+GetFullName(NPChar)+"。俺が船長だ "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("さっさと俺の船から出て行け！お前なんかいなくてもやることは山ほどあるんだ！","本は受け取っただろ、他に何が欲しいんだ？！","言われたことは全部やっただろ、まだ何を望んでるんだよ！？");
							link.l1 = "そんなに興奮するなよ、心臓発作を起こすぜ！";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("ラムだ、ラム！ラムをくれ…ひっく！","久しぶりだな…ひっく…あんなに酔っぱらったのは…");
					link.l1 = "ああ、船倉はもういっぱいだな……そろそろ入り江に向かう時か？";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("どうぞ、おかけください、船長ひっく！何を飲みやがりますか？","座ってくれよ、船長！何を飲みたいんだ？ひっく…");
					link.l1 = "ありがとう、でも俺はまともな男と気持ちのいい会話をしたいんだ。";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "お前、俺をバカにしようってのか…ひっく！あの酒場にはまともな奴なんて一人もいねえ！ひっく！いるのは盗賊と人殺しばかりだ！みんなゆすり屋だし、 あいつなんか…一番の極悪人だ！あいつらの頭で、ウツボでも喉に突っ込んでやがる！";
				link.l1 = "お前のことを言ったんだ。話したいのはお前だぜ。で、盗賊の頭は誰で、そいつがなぜ……";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+GetSexPhrase("ター","ｓ")+"！おお、旦那！もう一度名前を聞かせてくれねえか？お前さんには敬意を表するぜ！今まで誰も、 こんな老いぼれ船乗りをまともな人間だなんて言ってくれたことはなかったんだ！お前さんのためなら何でもしてやるぜ！ 最後の一ペソまで全部くれてやる！……あ、忘れてた。もう金なんて一文も残っちゃいねえ。レアルすら残ってねえんだ。あの野郎、 あのゆすり屋が最後のコインまで巻き上げやがった、地獄で悪魔どもがあいつの腸で大砲を詰めてくれりゃいいのによ！";
				link.l1 = "船長さん？大丈夫ですか？うわごとを言ってるのがわかりますか？何の巻物のことです？";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "いやいや！この年寄り船長は酔っ払ってるかもしれねえが、まだ頭はしっかりしてるぜ。 本と巻物は神父さんからもらったんだ "+PChar.GenQuest.ChurchQuest_1.ToName+"、俺はそいつらを連れて行くところだった " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + "。そして朝になって地元の教会へ行き、そこの神父にこの本のことを話したんだ。もちろん、あいつらのことだ、 すぐに見たがるさ――ああいう連中は聖人伝やら何やらに目がないからな。だからキャビンボーイに本の入った箱を持ってこさせたんだ。 待っている間に、ちょっと賭け事でもしようと思ってな……気がついたら全財産をすっちまった。全部だ！酒代を払う金も残っちゃいねえ！それで、 酒場の主人が本を担保に取っていきやがったんだ。ついでに巻物も渡しちまったよ…";
				link.l1 = "つまり、お前は神父から託された聖書を売ったんだな  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "わかってる、わかってるさ……俺は永遠に地獄の業火で焼かれるんだろうよ。今さら、あの用事を頼んだ神父にも、書類を届けてくれた奴にも、 地元の連中にも顔向けできねえ……\n今さら誰が俺の魂のために祈ってくれるんだ？もし破門されたらどうすりゃいいんだ？ああ、なんてこった……酒が必要だ…… ";
				link.l1 = "おいおい、落ち着けよ、そこまで悪くねえだろ。お前のやったことはひでえし、不信心だったが、 それでも俺は助けてやるつもりだぜ。お前の借金は俺が払って、この写本も買い取ってやる。それに、 どっちの神父ももう知ってるから、俺は直接そっちへ航海するぜ\n  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 書類をそこに届けるためだ。いいか？";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "救世主！神の使い……もちろん、同意するよ！あんたには何もかも――何もかもやるぜ……もう一杯飲めるなら……";
				link.l1 = "もう十分飲んだだろうが……まあいいさ。酒場の親父からラム酒をもっと買ってやるよ。";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "…それからシーツもだ！シーツも取り替えないといけねえ！…あっ、こんにちは。気を悪くしないでくれ、お嬢さん"+GetSexPhrase("ター","ｓ")+" 名前なんてどうでもいいが、今見ての通り俺はかなり忙しいんだ。用があるなら手短にしてくれ。";
				link.l1 = "俺の知る限りだと、神父 "+PChar.GenQuest.ChurchQuest_1.ToName+" で聖なる書類を渡した "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+"。お前は奴らを届けると約束した " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " どうせその方向に航海していたんだろうからな。"; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "俺もそっちに向かってたんだが、あの忌々しい嵐で俺のオンボロ船がぶっ壊れかけて、 どれだけここに足止めされるかわかったもんじゃねえ！\n桟橋の連中は、潮で流れ着いた腐った板切れを船体用に売りつけようとしやがるし、帆には、 奴らの婆さんが若い頃に寝てたボロ布を持ってきやがるんだぜ。";
				link.l1 = "旦那、次回は喜んであなたの素晴らしい話を聞かせてもらいますが、 今はあなたが受け取った本や写本の行方についてもっと知りたいのです "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "誰もだ、聞こえるか？この忌々しい書類の配達が遅れたことで俺を責める奴なんざ、一人もいやしねえ！";
				link.l1 = "ああ、違う、そんなつもりじゃなかったんだ。君の負担を少しでも軽くしたかっただけさ。実は、その… "+PChar.GenQuest.ChurchQuest_1.ToName+" に届けられる本や書類のことをかなり気にしている " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + "。実は、今からそこへ航海するつもりだ。";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "俺にはそう思えるんだ、お嬢さん"+GetSexPhrase("ター","ｓ")+"、どこの港にも霊的な相談役がいるってわけだな。まあ、俺には関係ねえけどよ。そんなくだらねえもんが欲しいなら、 本を持ってさっさと失せな！せいせいするぜ！";
				link.l1 = "ありがとうございます、船長。修理がうまくいくよう祈ってます。";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "そのことは気にするな、お嬢ちゃん"+GetSexPhrase("ター","ｓ")+"、そして向かう " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 軽々しく言うなよ、俺がその書類を届ける役目を引き受けたんだ。どんな手を使っても俺がやり遂げるさ。誰にも 「船長が…」なんて街中で騒がせはしねえ。 "+NPChar.name+" 約束を守らなかったんだ！";
				link.l1 = "しかし、船長、実は肝心なのは……";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "実は、お前に用はまったくないんだ。教皇様から本を届ける任務を受けただけだ。 " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 地元の神父にそれを渡してこい。\nだが、そこでお前の姿は見たくねえ。絶対にな！\n運がいいことを祈ってるぜ。";
//				link.l1 = "そうかい。責任感だけはある男だな、それだけが取り柄だが。運が良けりゃいいな、無礼な野郎め";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "お前の無礼な態度にはもう我慢ならん。お前の馬鹿げた口ぶりじゃ、天使でさえ怒り出すだろう。 聖なる父の御意志を果たさねばならん、必要とあらばこの武器も使うぞ！";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "静かに、静かに、船長 "+PChar.name+"！どうしたんだ？まあ、わかったよ、お前がその書類を持ってこなきゃ、あの聖職者どもはみんなお前に怒るだろうし、 天の父上様も黙っちゃいねえだろうな。よし、神学の宝を持って行け、神のご加護を。";
				link.l1 = "俺の立場を理解しただけじゃなく、俺の名前まで覚えてくれて嬉しいぜ。馬鹿なことをしそうになったら、 毎回その名前を思い出すんだな。";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("消え失せろ…","邪魔するんじゃねえ！");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"そんなこと言うんじゃなかったな！これで俺の罪の許しを祈るために、お前をあの世の主のもとへ送らなきゃならねえ！";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"そんなこと言うんじゃなかったな！これでお前をあの世へ送って、俺たちの罪の許しを主に祈らせてやるしかねえ！";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"そんなこと言うんじゃなかったな！今からお前をあの世に送って、俺たち全員の罪の許しを神様に祈らせてやるぜ！";
			}
			
				link.l1 = "とんでもねえよ、相棒。みんな自分のことは自分で神様にケリつけるんだ！";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "おい、なんでそんなに口が悪いんだ？もしかしたら俺がお前に用があるかもしれねえだろ。";
				link.l1 = "そりゃあ驚きだぜ！おい、俺はお前みたいな奴と世間話してる暇はねえんだよ！";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "まあ、俺もお前と長話するつもりはねえよ。だが、もしかして安く小物をいくつか買いたいって気はねえか？";
				link.l1 = "俺がくすね屋に見えるってのかよ！？";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "落ち着け、落ち着け、俺たちの中に泥棒はいねえよ！この花瓶はちゃんとした仕事の報酬でもらったんだ！見てみろよ……純金で、真珠まで飾ってある。でもな、問題は俺たちにゃ使い道がねえってことさ。だから売って、 その金を分けたいだけなんだ。";
					link.l1 = "よく見せてくれ……おおっ！これは聖体拝領の杯じゃねえか！！！ってことは、お前らがあの教会を荒らした冒涜者ってわけか "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"？！そこにいたのか！";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "静かにしな、お嬢ちゃん"+GetSexPhrase("ター","ｓ")+" 偽善者め！なあ、ちょっと金が足りなくてな、何か売ることにしたんだ。見てみろよ、この花瓶……純金製で真珠も付いてるぜ。お前には特別価格だ、そうだな、千枚のコインでどうだ。";
				link.l1 = "よく見せてくれ……おおっ！これは聖体拝領の杯じゃねえか！！！ってことは、お前らがあの教会を荒らした冒涜者どもか！ "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"？！やっと見つけたぞ！";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "落ち着け、お嬢ちゃん"+GetSexPhrase("ター","ｓ")+"「…くそっ、あの間抜けに時が来るまで騒ぐなって言っただろうが…」";
				link.l1 = "何をぶつぶつ言ってやがる？よし、選べ。お前が盗んだ戦利品を素直に渡すか、それとも俺が衛兵を呼ぶかだ。";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "「聞け、」 "+GetSexPhrase("いい男","お嬢ちゃん")+"、揉め事はごめんだ、だから穏便に済ませようぜ。信じてくれ、俺たちはあの教会を本当に襲ったわけじゃねえし、 金も持ってねえんだ。確かに、強盗のふりをした報酬としてペソを少しとあの金の飾りをもらった。で、 この金の杯だけが、密輸業者に支払いを済ませた後に残った唯一の品なんだよ…";
				link.l1 = "つまり、お前はこう言いたいんだな…";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "あの忌々しい神父が俺たちを雇ったんだよ、そう言ってんだ！でも、なんでお前までこっちに寄越す必要があったんだよ……まあ、これでおあいこだな。この花瓶を持っていけ、あの偽善者に見せてやれよ。 きっと浅瀬のイカみたいにのたうち回るぜ！";
				link.l1 = "カップを渡してさっさと消えろ、気が変わらないうちにな。";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "口はうまいが、俺はそんなに簡単に騙されねえぜ。俺を納得させたいなら、まずこの刃を納得させてみろ。";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"俺はあの野郎どもに言ったはずだぜ――神父からは金以外、何も手を出すなってな！";
			}
			else
			{
				dialog.text = RandSwear()+"あの欲深い野郎どもには言ったはずだぜ――強欲な手は出すな、神父からは金だけ取れってよ！";
			}
			
					link.l1 = "何をぶつぶつ言ってやがる？よし、選べ。盗んだ戦利品を大人しく渡すか、それとも俺が衛兵を呼ぶかだ。";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "俺は別の選択をするぜ。だから黙って財布を渡せば、命だけは助けてやる。";
				link.l1 = "今すぐお前を我らの主に引き合わせてやるぜ！";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "よし、金をやるぜ。ただし、俺の気持ちでやるだけだ。お前や仲間たちが真っ当に生きて、 盗みなんかで身を落とさなくて済むようにな。";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "ええ…わかったよ、揉め事はひとまず置いといて、話の最初に戻ろうぜ。で、その品はいくらで売りたいんだ？";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "「俺も面倒ごとはごめんだぜ、」 "+GetAddress_Form(pchar)+"、だが今は値が上がった。その貴重な杯のために、持っているもの全部を要求するぜ。";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "この強欲なクズめ！俺はたった "+FindRussianMoneyString(iMoney)+" 俺と一緒だ。持っていって、とっとと失せろ！";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "間違った選択だな、欲深いネズミめ。俺の犠牲になっても何も得られねえぞ！"+GetSexPhrase(" 俺は風のように自由だ――今日はここにいて、明日には消える。今は貧乏だが、明日には金持ちになってるさ……","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "「特に今日は、そう言おうとしてるんじゃねえか」 "+GetSexPhrase("お前は貧乏だ","金がねえんだな")+"?!";
				link.l1 = "その通りだぜ、欲張りな友よ、残念だったな。さて、俺はこれで失礼するぜ、やることが山ほどあるんでな。";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "止まれ！これから確かめさせてもらうぜ。もし嘘をついてたら、その舌を蟻の巣に突っ込んでやるからな！";
				link.l1 = "「そんなこと言ったら、お前はもう終わりだぜ！」";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "ああ、決めることなんて何もねえさ。全部俺たちで勝手に決めるぜ。だが、お前の船はいただいて、 ここから出ていくからな。";
			link.l1 = "条件が一つあるぜ。まずは俺の剣を奪ってみせろよ……";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "やあ、船長！どうやら天の摂理があんたを助けに遣わしたようだ "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" あいつとその手下どもだ。こっちは本当に困ってるんだぜ。"+"Our "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" 嵐でこの辺りの岩礁に座礁し、生き残った乗組員たちは波にさらわれて岸に打ち上げられた。"+"For "+(5+hrand(7))+"何週間も俺たちは地平線をじっと見つめて、助けに来てくれる船の帆が見えることを願っていたんだ。";
				link.l1 = RandPhraseSimple(RandPhraseSimple("ああ、それは気の毒な運命だぜ。だが、それが水夫の人生ってもんさ、誰だってお前の立場になるかもしれねえんだ。","なるほどな……神様はすべての命を握ってるが、忙しすぎて全員のことを覚えてられねえんだよ。"),RandPhraseSimple("確かに。人事を尽くして天命を待つ、だな。","ああ、そりゃ本当に運が悪かったな。"));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "とても深刻だったんだ！あのろくでなしが "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" 出ていく以外の罰は思いつかなかった "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" 無人島で、まるでみすぼらしい野良犬みてえにな！ "+"奴は、俺たちを漁師の台に干されたサバみてえに、太陽と渇きでカラカラにさせようとしたんだ！\nだが、奴は間違ってたぜ。天の摂理そのものが俺たちの味方だった。お前がここに来て、 俺たちを救ってくれたんだからな…";
				link.l1 = RandPhraseSimple("慌てるな、相棒。俺の見るところ、お前らは自由な稼業の連中だろうし、ここに来たのも偶然じゃねえだろう。","もう救いの話か？俺の理解じゃ、お前は何か特別な功績があってここにいるんだろう。");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("船長、どうか情けをかけて助けてください  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" 落ちぶれた男たちだ。俺たちの唯一の希望はあんただ、あとは慈悲深い主だけだ。","船長、あんたの船に空いてるロッカーはあるか "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" 落ちぶれた男たちか？");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "「おお…で、どこへ連れて行ってほしいんだ？」";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("本当に申し訳ねえが、空いてるハンモック一つもねえし、ましてや船室なんてとんでもねえ。 水夫どもは甲板で寝てるんだ、見張りの後でもろくに休めやしねえんだよ…","本当にがっかりさせたくはねえが、船は積みすぎで、みんな悪天候の中で寝なきゃならねえんだ。\nもし病気が流行ったら、乗組員の半分を失っちまうぜ。"),RandPhraseSimple("本当に申し訳ないが、俺の船には全く余分な乗組員のスペースがないんだ。これ以上乗客を乗せることはできねえ。","残念だが、俺の船は乗組員でいっぱいなんだ。疫病が心配でな……"));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "お前はベテランの水夫だろうが、難破から生き延びた奴がいるってのはとんでもなく縁起が悪いって知ってるはずだ。 俺の船乗りどもはお前ら全員を海に放り投げちまうぜ。";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "ふむ……いろいろ理由があって、できるだけ役人どもから離れていたいんだ……頼む、どこでもいいから人の住む島か本土の入り江に降ろしてくれれば、あとは自分たちでなんとかするさ。";
			link.l1 = "まあ、空いてる寝台とハンモックは十分あるぜ。さっさとボートに乗り込め。";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "ふむ……運が悪いな……これから戦いが待ってるぜ。お前が俺の船にいた方が安全か、それともこの居心地のいい入り江にいた方が安全か、 俺にも分からねえ。";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "おお、船長！今の時代はな、女房と寝床にいても安心できねえんだぜ、ははっ、ましてや海の上なんてなおさらだ……見ろよ、あの野郎ども、みんな素手で大砲に立ち向かう覚悟ができてやがる。 安全や快適さなんざこれっぽっちも求めちゃいねえ、その面構えを見りゃわかるだろう！";
			link.l1 = "奴らの顔には、自分たちの愚かな恩人を背後から刺す気満々なのが見えるぜ。";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "ふむ……それは確かにいい考えだな。ところで、旦那、お前の手下どもは俺の船の乗組員として働く気はあるのか？";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "残念だな、船長…。どうやら穏便には済まなそうだぜ。海の掟を思い出させてやるしかねえな。\nそれに、白兵戦なら俺たちに敵う奴はいねえってこと、覚えておけよ…";
			link.l1 = "さて、ようやくお前の本当の姿が見えたぜ……";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "もちろんだぜ！あいつらは喜んでお前の斬り込み隊に加わるさ！戦いであいつらに勝てるのは、 せいぜいデイヴィ・ジョーンズくらいのもんだろうな！ハッハッハ！";
			link.l1 = "よし、じゃあな。お前ら、ボートに乗り込め…";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "ありがとうございます、船長！積み込みはそんなに時間がかからないはずです。神よ、 この瞬間が来るようどれだけ祈ったことか！";
			link.l1 = "「よし、そういうことだな。」";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("何をぐずぐずしてるんだ、船長？錨を上げるよう命令しろよ。","申し訳ないが、船長、出航の準備をしなきゃならねえんだ。","あんたがここに来てくれて、俺たちは本当に運がいいぜ！");
			link.l1 = "急げ。船は誰も待っちゃくれねえぞ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "ありがとうございます、船長。確かに、俺たちが運を信じて正解だったな……どうぞ、この宝石を受け取ってくれ。あの不運な入り江で見つけたんだ。船長に幸運をもたらすことを願ってるぜ。";
				link.l1 = "こんな贈り物がもらえるとは思わなかったぜ。";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "船長、どうか無礼だとは思わないでくれ。だが、俺たちは本当に金がなくて困ってるんだ。全部失っちまったんだよ。 ペソをひと握り、いやふた握りほど貸してくれねえか？必ず返すぜ……機会があればな……";
				link.l1 = "おったまげたぜ！まったく、図々しさにも限度がねえな。まあ、これまで俺がしてやったことを考えりゃ、 今できるのはお前のことを役人にチクらねえことくらいだな。";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "そうかよ……で、いくら欲しいんだ？";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("ありがとうございます、船長。","船長、俺たちは本当に感謝してるぜ。","あなたのために祈ります、船長 "+PChar.name+"!");
			link.l1 = "幸運を祈るぜ。じゃあな……";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "へっ、船長……なあ、俺たち、うまくやってきたよな……お前を殺すのは本当に惜しいぜ……";
			link.l1 = "やってみろよ！";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "「さて、言ってみろ、」 "+iMoney+" 俺たち一人ひとりにペソをくれりゃ、悪くねえ取引だぜ…もちろん、これが俺たちの苦労と痛みに見合わねえって思うなら、別だけどな、へへ…";
			link.l1 = RandPhraseSimple("逆に、俺はこう思うぜ……お前ら全員の首に縄をかけるのが一番だな。","そんな大金のためなら、俺が自分でお前らをヤシの木に猿みてえに吊るしてやるぜ！");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "わかった、持っていけ。これ以上は借りなんかないよな？";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "なんて気前がいいんだ！正直言って、俺たちが欲しいものは必ず手に入れるって、もう分かってると思ってたぜ。今回も、 絶対に引き下がらねえからな……";
			link.l1 = "やってみろよ！";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "おいおい、船長、何言ってんだよ！？もし教会に足を踏み入れることがあったら、 絶対にあんたのためにロウソクを灯してやるさ……ははっ！";
			link.l1 = "そうだといいが……";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "おいおい、船長、何言ってんだよ！？俺たちが教会に足を踏み入れることがあったら、 絶対にあんたのためにロウソクを灯してやるさ……ははっ！";
				link.l1 = "そうだといいんだが……";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "へっ、船長、知ってるだろ、そんなの大した問題じゃねえよ。俺と仲間たちで、 今そのハンモックを使ってる連中をどかして、船に十個ぐらい空けてやるぜ……";
				link.l1 = "ふん……それは脅しみたいだな……";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "実はな、これは脅しだぜ。俺はお前の船が必要なんだ。お前の同意があろうとなかろうと、ここを出ていくからな！";
			link.l1 = "さて、やっとお前の本性が見えたぜ……";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "分かってるぜ、船長。お前の言いたいことはよく分かる……絞首台を願うような哀れな海賊なんざ、誰も面倒見たくねえよな？\nだがよ……もし俺から取引を持ちかけたらどうだ？俺たちをどこか人の住む島か本土の入り江まで運んでくれたら、 その見返りに宝の地図を渡すぜ。どうだ、話はまとまるか？";
			link.l1 = "ふむ……で、この地図が偽物じゃねえって、どうやって保証するんだ？";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "はっ、どうせお前の地図なんざ、その紙切れと同じ価値しかねえだろうが…";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "……仕方ねえな……だがよ、俺たちはここを出るぜ、お前の許可があろうとなかろうとな！";
			link.l1 = "さて、ようやくお前の本当の姿が見えたぜ……";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "「それで、どうやって俺たちを一番近い港の役人に売らないって保証できるんだ？ お互い手の内を見せずに勝負してるんだぜ…」";
			link.l1 = "よし、取引成立だ。";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "ありがとうございます、船長 "+PChar.name+"。お前は果たした"+GetSexPhrase("","")+" 約束だ、もう時間だ "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" 俺の目的を果たすためにな。地図は持ってねえが、宝の在りかは教えてやる。入り江へ行け…";
			link.l1 = "おお、今になってそう言うのかよ！最初から俺を騙すつもりだったんだな……";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "最初からお前のことは信用できねえって分かってたぜ…";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "これが海賊を信用した結果だ。お前らはどんな連中なんだ？お前らには神聖なものなんて何もねえのか！";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "騒ぐんじゃねえ…俺は聖人じゃねえが、約束は守るぜ！";
			link.l1 = "またお前の言うことを信じろってのか？そしたら明日にはカリブ中の連中に笑いものにされちまうじゃねえか？";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "ふむ……どうやら平和的な解決はなさそうだな。しかし、神のみぞ知る、俺はこんなこと望んじゃいなかったんだ……";
			link.l1 = "剣を抜け、さもねえとネズミみてえに叩き潰してやるぞ！";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "他にどうしろってんだ？あの臭え水たまりで仲間と一緒に腐り果てろってか？最後まで俺の話を聞いたほうがいいぜ…"+XI_ConvertString(sTitle+"Gen")+" 船長 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" 奴の隠し財宝があるぜ。だが、気をつけろよ"+GetSexPhrase("","")+"、あいつはよくそこに行くんだ。用心していれば隠し場所を見つけるのは難しくねえさ…"; // belamour gen
			link.l1 = "「またお前の言うことを信じろってのか？そうしたら明日にはカリブ中の連中に笑いものにされちまうじゃねえか？」";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "わかった。だが、もう一度俺をバカにしたら、必ず見つけ出してやるからな。";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("「聞け」 "+sTemp+"、あいつの言ってることは筋が通ってるぜ。","怒らないでくれ "+sTemp+"、奴には他に選択肢がなかっただけだ。","ありがとうございます、船長。");
			link.l1 = "…幸運を祈るぜ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "「他にどうしろってんだ？あの臭ぇ水たまりで仲間と一緒に腐って死ねってか？俺の話を最後まで聞いたほうがいいぜ…」"+XI_ConvertString(sTitle+"Gen")+" 船長 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" あいつが戦利品を隠してる隠し場所があるんだ。だが気をつけろ、あいつはしょっちゅうそこへ行くからな。 油断しなけりゃ隠し場所を見つけるのは難しくねえぜ…"; // belamour gen
			link.l1 = "またお前の言葉を信じろってのか？そうしたら明日にはカリブ中の連中に笑い者にされちまうじゃねえか？";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "お前は誰だ？"+GetSexPhrase(" 相棒"," 嬢ちゃん")+"？それで、こんな寂れた場所に何の用で来たんだ？";
			link.l1 = "俺は真水の補給のために立ち寄ったんだ。";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "俺は～の代理で来た "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "そんなことをするには、ここは悪い場所だぜ……まあ、ゆっくりやれよ。";
			link.l1 = "あは…";
			link.l1.go = "exit";
			link.l2 = "「お前、何様のつもりで俺に指図してんだ？」";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "俺がみんなに指示を出してるんだ。\nそれで、頭がいいと勘違いしてる奴らはヤシの木に吊るされることになるぜ。";
			link.l1 = "舌を引き抜いてやるぜ、この野郎。";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "「それで、なんで本人が来なかったんだ？」";
			link.l1 = "奴はやりたくなかった、あいつはそこに残った "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" そして俺を待っている。"; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "あの年寄りの悪党め！また俺たちを騙そうとしてやがるんじゃねえか？そんなの許せねえ。 俺たちが一緒にいる時だけ金を受け取れるって伝えてくれ！";
			link.l1 = "「金を持たずに戻るな、誰も乗せるな」と言われたんだ……";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "ああ、そんなにあいつを信じてるなら、ここに残ってもいいぜ。だが、俺たちはお前の船と金をいただいて、 そして向かうのさ\n "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+"。俺たちはの顔を早く見たくてたまらねえんだ "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "そんなに会いたいなら、泳いで行けばいいさ……それとも、ここでくたばるか。";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "あんたは抜け目ない奴だな。だが、俺たちと 船長との争いについては安心してくれ。 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" 純粋に思想的なものだ。俺はあいつに、汚い商売はいずれ罰が下ると警告したんだが、今や俺の  "+iBanditsCount+" 俺たちの仲間は、神と正義への愛のせいで苦しんでるんだ。";
			link.l1 = "どういうことだ……お前らが反乱の本当の首謀者だったんじゃねえのか、そして自業自得ってわけだ。";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "もちろん……でも、船長の意見も聞いてみたいな "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" お前とのいざこざについて自分自身で考えている。";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "船長、なぜそんなに疑い深くて正直な連中を侮辱するんだ？\nあいつらの顔をよく見てみなよ……本当に反乱者だと思うのか？あれほど謙虚な奴らはいないぜ……\nだが、正義のために、いい指揮官の下なら誰にも負けねえ戦いぶりを見せるんだ！\n俺が一人一人保証してやるよ。";
			link.l1 = "よし、だがこれからお前をどうするかだな？";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "望み通りにしな。あんた次第だぜ、どこかの町に連れてってもいいし、俺たちを船員にしてくれてもいい。 あんたはいい船長に見えるぜ。";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "よし、俺のクルーに入れてやる。だが、ふざけるんじゃねえぞ！俺の船は規律が厳しいんだ！";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "どこにも連れて行かねえよ。俺の船にはもう十分ゴロツキがいるんだ。";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "よし、船に乗れ。どこかに連れてってやるぜ。";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("誓うぜ、船長、絶対に後悔はさせねえよ。","いい選択をしたな、船長。","船長、安心しな。あんたも俺たちと同じくらい運が良かったんだぜ！");
			link.l1 = RandPhraseSimple("そうだといいんだが。","急げ。船は誰も待っちゃくれねえぞ。");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "それは簡単に手配できるぜ。奴は航海中だ  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" 「」"+sTitle+" 奴隷貿易に手を染めている……こうしようぜ：もしそいつを見つけたら、お前が積み荷をもらって、俺たちは船をもらう。ああ、それと、 そいつにこれについて知ってるかどうかも聞いてみてくれ\n "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+"…あいつがその名前を聞いてビビって漏らさなきゃいいがな、だってそれは俺の船だからな…"; // belamour gen
			link.l1 = "よし、取引成立だ。";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "俺に一体何の用だよ？";
			link.l1 = "「の代理で挨拶に来た」 "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+"。あいつのことを知ってるんだろう？";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "あの悪党を前に絞め殺しておけばよかったぜ、残念だ。\nまあ、俺の情けのツケを払う時が来たってわけだな……";
			link.l1 = "確かに……そして時間がちょうど切れたな……";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "よくやったな、船長！約束通りでいいんだな？俺たちが船をもらって、あんたが積み荷をもらうってことでいいんだな？";
			link.l1 = "ああ、船を持っていけ。しっかり役立てるんだぜ。";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "ごきげんよう、船長 "+PChar.name+".";
			link.l1 = "それで、自分の船はどうだ？";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "へっ……きしきしギシギシいってやがる、まるで俺みてえだ。俺もこいつも、 もう大海原を航海できる時間はあんまり残っちゃいねえな……";
			link.l1 = "じゃあ、幸運を祈るぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "なんで俺の船を沈めたんだ！？俺たちの約束を覚えてるのか？\n";
			link.l1 = "なんだと？俺は沈められるのはごめんだったんだぜ。\nギリギリで助かったのがわからねえのか？";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "そんな戦い方する奴がいるか？あんな船を失いやがって！ふざけんな！お前みたいなガキがここで何してるんだ？";
				link.l1 = "舌を引き抜いてやるぜ、この野郎。";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "誰がそんな戦い方をするんだ？あんな船を失いやがって！俺がどれだけ金をかけたと思ってるんだ！？ "+FindRussianMoneyString(iMoney)+"！これで借りができたな……";
				link.l1 = "お前には荷が重すぎるんじゃねえか？俺はもう一度お前に恩を売ってること、忘れるなよ。";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "くたばれ、お前もあの忌々しい船も！金は持っていけ、二度と俺の前に現れるんじゃねえぞ！";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "「それが今の俺に何の役に立つってんだ！？もし船長が」 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" 今ごろ俺の船と一緒に海の底だ！もう取り分も船も戻らねえ！こんな運命があるかよ、浮浪者みてえに溝で死ぬなんて！！ ！";
			link.l1 = "「でも、なぜだ？ここで派手な葬式をしてやってもいいんだぜ。それで構わねえならな……」";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "俺たちと……話をつけられるんじゃねえかと思ってな。お前が一つ頼みを聞いてくれりゃ、ちゃんと礼はするぜ、へへ。";
			link.l1 = "頼みごとか？で、話はなんだ、見返りに何をくれるんだ？";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "俺たちの船長 "+PChar.GenQuest.JusticeOnSale.SmugglerName+" 現地の巡回隊に捕まった  "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+"。奴は捕まっているが、絞首刑にするだけの証拠が足りねえんだ。俺たちだけじゃ引きずり出せねえ\n"+"あんたは評判のいい男だ。みんなあんたのことを知ってる。もしかしたら、交渉して保釈したり、 いっそ金で買い取ることもできるんじゃねえか？\n信じてくれ、俺たちは仲間を手に入れたらすぐに島を出る。だからあんたの評判には傷がつかねえよ！"; // belamour gen
			link.l1 = "俺が手を貸すとしてもよ。だが、報酬はどうするんだ？";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "地獄へ落ちろ、この悪魔の化け物め！俺はお前なんかと関わりたくねえ！";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "インディアンの小物やお守りはいかがだ？なかなか珍しい品だぜ……それとも現金がいいか？数千ペソってところだが、どうだ？";
			link.l1 = "地獄へ落ちろ、この悪魔の化け物め！俺はお前なんかと関わりたくねえ！";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "俺はインディアンの小物に興味があるんだ。まあ、引き受けてやるぜ。";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "現金は船乗りの一番の友だちだぜ。金に臭いはねえって、みんな知ってるだろ。俺も同感だ。";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "ありがとうよ、船長。報酬に加えて保釈金の分もちゃんと払わせてもらうぜ。 俺たちの船長については司令官と話すべきだと思う。あんたなら説得できるかもしれねえ。無事に出せたら、 俺たちのところに来てくれ\n "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+"、そこに俺たちの船が錨を下ろしているんだ― "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" 「」"+PChar.GenQuest.JusticeOnSale.ShipName+"』。岸で待ってるぜ。"; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "ありがとうございます、船長。保釈金の額も報酬に加えてお支払いします。 うちの船長については司令官と話すべきでしょう。もしかしたら説得できるかもしれません。彼を出したら、 こちらに来てください\n "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+"、そこに俺たちの船が錨を下ろしているんだ― "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" 「」"+PChar.GenQuest.JusticeOnSale.ShipName+"。岸で待ってるぜ。"; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "着いたぜ、船長！あの腹の出た役人どもをうまく騙したな！これが報酬だ。\nおい、野郎ども、小物を持ってこい！";
				}
				else
				{
					// Награда золотом.
					dialog.text = "着いたぜ、船長！あの腹の出た役人どもをうまく騙したな、見事だ！ほら、これが報酬だ。おい、野郎ども、 箱を持ってこい！";
				}
				
				link.l1 = "俺の取り分をよこして、とっとと失せろ！";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "着いたぜ、船長！全部きれいに準備してくれたみたいだな。だがよ……証人なんざ要らねえんだ、だからよ……船長にお礼を言おうぜ、野郎ども！";
				link.l1 = RandSwear()+"会ったときにお前を撃っておくべきだったぜ！";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("お前は誰だ？それに、なんで俺の部屋にずかずか入ってくるんだ？","おったまげたぜ。お前は誰だ？ここはもちろん俺の部屋だが、こんな客なら歓迎だぜ。これは愛のお届け物か？")+"";
			link.l1 = ""+GetSexPhrase("もうお前の部屋じゃねえ。宿屋の親父が俺に貸してくれたんだ、お前は金も払ってねえし、そろそろ出ていってもらうぜ。 素直に出るか、ゴリ押しされるか、どっちがいいか選べよ。","夢でも見てるのかよ。俺たちの場合は掃除だ。だからさっさとここから消えな。ここはもう俺の部屋だぜ。お前と違って、 俺はいつも宿屋の親父にちゃんと金を払ってるからな。")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("あんたのことは聞いたことがあるぜ。わかったよ、負けだ、俺は引き下がる。まだ生きていたいからな……","ふむ、あんたのことはいろいろ聞いてるぜ。舌だけじゃなくて腕も立つんだろうな。よしよし、怒るなよ、 部屋はあんたのもんだ。")+"";
				link.l1 = ""+GetSexPhrase("いい決断をしたな。","いい子だ。")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("そういうことか。じゃあ、俺は茨の道を選ぶぜ。","このアマめ！俺は優しくしてやろうと思ってたのによ…")+"";
			link.l1 = ""+GetSexPhrase("お望みどおりに……","「それで“優しく”したつもりか？哀れだな。いや、やっぱり同情はしねえけどな。」")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("わかった、もういい、やめてくれ！殺さないでくれ。俺はもう行く。","止まれ！これからどうしろってんだ、この部屋のことで殺し合いでもするのか！？くれてやるよ、全部お前のもんだ。 くそったれが……")+"";
			link.l1 = ""+GetSexPhrase("正しい判断だ。次は頭を使えよ。俺ほど親切な奴ばかりじゃねえ、うっかり殺されることだってあるんだからな。","野郎ども。")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("さて、俺を追い出したのか？斬り捨てる前にとっとと失せろ。","お前らは口ばっかりだな。俺がまだ機嫌がいいから助かってるんだぜ、 そうじゃなきゃもっとひでえ目に遭わせてやったところだ。さっさと失せろ！")+"";
			link.l1 = ""+GetSexPhrase("くそっ……","くそっ、俺がお前を甘く見てたぜ……わかった、わかった、今すぐ引き下がるよ。")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "あぁ？…どけ、若造、俺は…ひっく…誰とでも飲むわけじゃねえんだ。";
			link.l1 = "今ここでぶん殴ってやるぜ、そうしたら一週間は酒が飲めねえぞ。";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "「なんだと！？お前、自分が誰に話してるかわかってるのか？俺は『」"+pchar.ship.name+"！船長に報告するだけで、お前は町から逃げ出す暇もなくなるぞ！今のうちに無事で出ていけ。"; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "船長か……";
			link.l1 = "1か月間、甲板を磨いてもらうぞ。";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "すまねえ、船長！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "よう、船長！あんたが船長だってのは知ってるぜ、そうだろ。";
			link.l1 = "挨拶だ。どうして俺が船長だとわかったんだ？";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "ははっ、俺は百戦錬磨の海の狼だぜ。もう十年以上も海を渡ってきたんだ。主に航海に従事してきた――凪でも嵐でも、ラガー船でも戦列艦でも乗ったことがある。実は先月、激しい戦いのあとに負傷しちまった。 嵐が荒れ狂ってて、誰も帆に登ろうとしなかったから、俺がやったんだが、その代償は高くついた。 幸い足首をひねっただけで、何週間か歩けなかったが、それで陸に上げられたってわけさ。今はもう良くなって、 こうしてここでチャンスを待ってるってわけだ。";
			link.l1 = "面白いな。この分野の専門家がいれば助かるぜ。俺のクルーに加わらないか？";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "なぜだ？もう船の甲板と新鮮な風をはらんだ帆の音が恋しいんだ。必要ならお前のチームの指導もできるぜ。ただし、 先に言っておくが、すぐに千ペソ要求するからな。じゃないと、もう俺の懐は空っぽだ。他の連中も同じだがな。 俺は正直者なんだぜ。";
			link.l1 = "いや、たぶん断るぜ。船乗り一人ひとりに千ペソも払って雇ってたら、俺の身がもたねえ。俺を責めないでくれよ。";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "いいだろう。腕のいい専門家に千ペソくらい惜しくねえさ。\nほら、これだ。\nそれじゃ、船で待ってるぜ。";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "はは、俺は百戦錬磨の海の狼だぜ。十年以上も海を渡ってきた。大抵は大砲のそばにいたんだ――ファルコネット、キャロネード、カルヴァリン、セイカー……色んな砲で撃ちまくった。ラガー船にも戦列艦にも乗ったことがある。まあ、先月の激しい戦いで負傷しちまってな、 ブドウ弾の跳弾が当たったが、大したことはねえ、足にかすり傷ができただけだ。それで陸に下ろされちまった。 今はもう良くなったから、こうしてここでチャンスを待ってるってわけさ。";
			link.l1 = "面白いな。この分野の専門家がいれば助かるぜ。俺の仲間にならねえか？";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "なぜだ？もう砲甲板が恋しいぜ、火薬の匂いと大砲の轟音もな。必要ならお前のチームの指導もしてやれるぜ。\nだが最初に言っておくが、俺は千ペソ要求するぜ、でなきゃ俺の懐は空っぽのままだ。\nそれに、他の連中と同じく、俺も正直者だからな。";
			link.l1 = "いや、たぶん断るぜ。船乗り一人ひとりに千ペソも払って雇ってたら、俺の身がもたねえ。俺を責めないでくれよ。";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "いいだろう。腕のいい専門家に千ペソ払うのは構わねえ。ちょっと待て……ほらよ。それじゃ、船で待ってるぜ。";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "はっ、俺は百戦錬磨の海の狼だぜ。十年以上も海を渡ってきたんだ。主に白兵戦で戦ってきた――海賊とも正規軍ともやり合ったし、どんな武器でも扱える。ラガー船にも戦列艦にも乗ったことがあるんだ。まあ、 先月は激しい戦いの末に負傷しちまったがな。背中にちょっとしたサーベルのかすり傷――あの腰抜け、正面から来れなかったが、結局俺が奴を仕留めてやったぜ。あの傷を見た連中の顔ときたら、 お前にも見せてやりたかったな、ははは。そんで陸に上げられたってわけさ。今はもう良くなったし、 こうしてチャンスを待ってるってわけだ。";
			link.l1 = "面白いな。この分野の専門家がいてくれると助かるぜ。俺の船に乗らねえか？";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "なぜだ？もう剣の音や、船同士が接近するきしみ、戦いの興奮が恋しいんだ。 必要ならお前のチームの指導もしてやれるぜ。だが、先に千ペソ払ってもらわなきゃ困る。俺の懐はもう空っぽだからな。 それに、他の連中と同じく、俺も正直者なんだぜ。";
			link.l1 = "いや、たぶん断るぜ。船乗り一人につき千ペソも払ってたら、俺の身が持たねえよ。俺を責めないでくれ。";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "いいだろう。腕のいい専門家に千ペソ払うのは構わねえ。待てよ……ほら。船で待ってるからな。";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "海での幸運を祈るぜ、船長！";
			link.l1 = "お前もな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "お、お前は誰だ？";
			link.l1 = "俺が船長だ "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "悪いな、相棒、急いでるんだ。";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "船長？…ひっく！せ、船長…酒場まで送ってくれ…ひっく！…ん？頼むよ。この植民地で…迷っちまったみたいなんだ、そう…ひっく！…";
			link.l1 = "どけよ、俺は暇じゃねえんだ！";
			link.l1.go = "NightAdventure_End";
			link.l2 = "よし、行くぜ。お前一人じゃたどり着けそうにねえからな。";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "ただ…ひっく！…ゆっくり、お願い…ひっく！…立って…いられ…ないんだ…";
			link.l1 = "よし、行くぞ、ゆっくりな。";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "船長…ひっく…し、船長…助けてくれ！";
			link.l1 = "離れろ、俺は暇じゃねえんだ！";
			link.l1.go = "NightAdventure_End";
			link.l2 = "どうしたんだ？";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "あそこだ…酒場に…ひっく…イカサマ師がいるぞ！";
			link.l1 = "まあ、それがどうしたんだ？どこの植民地の酒場にも、イカサマ師なんてゴロゴロいるぜ。";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "せ、船長、あんた…分かっちゃいねえ…ひっく！…あいつはお、俺を…一ペソも残さず置いていきやがったんだ！ひっく！…そんで…俺を追い出しやがって…ひっく！..";
			link.l1 = "それで、今度は俺に何の用だ？";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "俺と一緒に来いよ…ひっく！…こいつをどうにかしろ！お、俺の金を…ひっく！…返させろ！ひっく！…";
			link.l1 = "酔っ払い相手にテーブルで勝つのに、イカサマ師になる必要はねえさ。次はもっと酒を控えな。";
			link.l1.go = "NightAdventure_End";
			link.l2 = "「で、俺がこれを何に使うってんだ？…まあいい、行くぜ。お前のイカサマ師を見せてもらおうじゃねえか。」";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "ちょっと…ひっく…ゆっくり、お願いだ。俺は…ひっく…立って…いられねえ…";
			link.l1 = "よし、ゆっくり行こうぜ。";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "か、か、船長…ひっく！…本当にありがとう…助かったぜ！俺…ほらよ…ひっく！…あんたにやるよ。";
			link.l1 = "さあ、もういいだろ…そんな飲み方はやめとけ。少なくとも、これ以上厄介ごとを探しに行くなよ。";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "か、船長！…あの…ひっく…イカサマ師が！…";
				link.l1 = "俺か？イカサマ師だって？";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "あそこだぜ、船長！ひっく…テ、テーブルに座ってやがる…";
				link.l1 = "来いよ……";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "いや…ひっく！…シャーパー！…あいつ、消えちまった！…";
			link.l1 = "ああ、彼はもう行っちまったから、お前を待ってなかったぜ。";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "それで…つ、次は何だ？ひっく…";
			link.l1 = "まあ、今さらどうしようもねえよ。俺が夜中に植民地じゅう探し回るなんて絶対にしねえからな。 もうあんな飲み方はやめとけ。少なくとも酔っ払って賭け事するのはやめとけよ。";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "サイコロ勝負を提案するぜ。乗るか？";
			link.l1 = "冗談じゃねえ。俺はこの船の船長だぜ、イカサマ野郎と遊ぶ気はねえんだ。だがな、そこの善人に金を返さねえなら、 てめえの肋骨を簡単に折ってやるぞ。";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "イカサマ師だと！？俺がイカサマ師だってのか？金を返せだと、あの酔っ払いにか！？船長、馬鹿にしやがって……";
			link.l1 = "もっと手荒にしてやってもいいんだぜ。金を返せ。";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "ああ、俺はイカサマ師じゃねえ！正々堂々と勝負してるんだ。運が勝つだけさ。お前の仲間はたまたまツイてなかった、 それだけだぜ。";
			link.l1 = "運か？サイコロを寄越せよ、どれだけツイてるか見てやるぜ。";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "わかった、わかった、落ち着けよ、船長。まあ、酔っ払いには勝ったし、ちょっとズルもしたけど、 他の奴らもみんなやってることだぜ。ほら、こいつの金だ。";
				link.l1 = "そりゃあいいな。だがな、もし俺の仲間が「これじゃ全額じゃねえ」と言ったら、 またお前のところに戻ってくるってこと、分かってるよな？";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "ああ、どうぞ、これが俺のサイコロだ。両方のセットだぜ。調べてくれ。隠し事なんてねえよ。";
				link.l1 = "そうか…ペア…なし…ペア…フルハウス…なし…なし…ツーペア…スリーカード…なし…ペア…";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "ああ、どうぞ、これが俺のサイコロだ。両方ともな。調べてくれ。隠し事なんて何もねえよ。";
				link.l1 = "そうか……フォーカード……フォーカード……フルハウス……フルハウス……フォーカード……ポーカー……フルハウス……ポーカー……フォーカード……フルハウス……ふむ、それを俺にどう説明するつもりだ？";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "全て分かった、これが全額だ。君と君の仲間に幸運を祈るぜ。";
			link.l1 = "お前もな。";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "でも…あいつは認めたくなかったんだ！ひっく…";
			link.l1 = "ああ、逃げようとしたんだ。ほら、金は返すよ。";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "か、船長……ひっく！…本当にありがとう…助かったぜ！俺…「横にゲロを吐く」…ほらよ…ひっく！…あんたにやるよ。";
			link.l1 = "さあ、うっ…もういい…そんな飲み方はやめろよ。せめて酔ってるときは賭け事はするな。";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "どうだ？納得したか？";
			link.l1 = "ふむ、確かにただのサイコロみたいだな……";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "言っただろう。お前の仲間はただ酔っ払ってるだけだ。それに、自分の負けを認められなくて、 お前をここに連れてきたんだぜ。";
			link.l1 = "わかったよ、あの件は悪かったな。幸運を祈るぜ。";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "そ、そうか…ひっく！…なんだって？…あいつは…ひっく！…い、いかさま師じゃねえのか…？";
			link.l1 = "まあ、あいつは公正に勝負したようだな。";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "それで…つ、次は何だ？ひっく…";
			link.l1 = "まあ、もうどうしようもねえさ。あいつは正々堂々とお前を打ち負かしたんだ。そんなに飲むのはやめとけよ。 少なくとも酔っ払ってる時に賭け事はするなよ。";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "運だ。ただ運が良かっただけさ。運ってのは気まぐれな女神だぜ。";
			link.l1 = "ふむ、そうか。じゃあ、お前と遊んでやるぜ。ただし、このサイコロは俺のもんだ、覚えとけよ！";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "これかい？…いや、その…やっぱり、あんたとは遊びたくねえ！俺のことバカにしやがって。それに、どうせ俺はスッカラカンだし…";
			link.l1 = "もしかして、この酒場の連中全員にお前のサイコロのことを話してやろうか？\nそれとも見せてやろうか？\nそしたら運について語れるだろう。どう思う？";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "なんだと！？てめえ、何様のつもりだ！？俺を脅す気か！？さっさと失せねえと、今すぐ鉛玉ぶち込んでやるぞ！";
			link.l1 = "俺はここに残って、みんなにあんたのサイコロを見せてやりたいぜ。";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "さあ、こっちに来い、腐れ野郎！";
			link.l1 = "ズボンをなくすなよ。";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "か、船長？…お前…ひっく！…喧嘩したのか？…で、こいつの方が…ひっく！…つ、強いのか？";
			link.l1 = "自分で殴られたんだ。他の奴とはもう遊ばねえよ。";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "でも…あいつは認めたくなかったんだ！ひっく…";
			link.l1 = "ああ、奴は逃げようとしたぜ。単にお前の金を持ってなかったんだろう。たぶん使っちまったんだな。";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "ああ、奴は逃げようとしたぜ。ほら、金だ。";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "それで…つ、次は何だ？ひっく…";
			link.l1 = "まあ、今さらどうしようもねえさ。あいつは正々堂々とお前を打ち負かしたんだ。もうそんなに飲むなよ。 少なくとも酔っ払ってるときに賭け事はやめとけ。";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "か、船長…ひっく…本当にありがとう…助かったぜ！俺は…「横に吐く」…ほらよ…ひっく…あんたにやるよ。";
			link.l1 = "さあ、うっ…もういい…そんな飲み方はやめろよ。せめて酔ってるときは賭け事はするな。";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "船長？…ひっく…し、船長…桟橋まで送ってくれ…ひっく…ん？頼むよ。俺…ひっく…船に…行かないと…ひっく…ボースンが…遅れたら罵る…ひっく…";
			link.l1 = "離れろ、俺は暇じゃねえんだ！";
			link.l1.go = "NightAdventure_End";
			link.l2 = "よし、行くぜ。お前一人じゃたどり着けそうにねえからな";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "ただ…ひっく！…ゆっくり、お願いだ。俺…ひっく！…もう…立ってられねえ…";
			link.l1 = "よし、ゆっくり行こうぜ。";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "か、船長…ひっく！…本当にありがとう…助かったぜ！俺は…（横でゲロを吐く）…ほらよ…ひっく！…あんたにやるよ。";
			link.l1 = "さあ、うっ…もういい…そんな飲み方はもうやめとけ。せめて冒険を探しに行くのはやめとけよ。";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "か、船長！…船だ！";
			link.l1 = "「“船”だと？」";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "し、船が！…どこだよ…ひっく…";
			link.l1 = "明らかにあいつは出て行ったんだ。酒場で飲みすぎるのはやめとけ。 船全体が酔っ払いの水夫一人のために待ってるわけじゃねえぞ。";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "でも俺は…ひっく！…酔ってねえ…ほとんど…たぶん…";
			link.l1 = "ああ、そうだな。本当に。幸運を祈るぜ。";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "待ってくれ、船長！お、おれを……ひっく……お前の船に連れてってくれ！もう……ひっく……酒は飲まねえから……";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "仕方ねえな、どうしようもねえだろう。だが、まっすぐ船に戻れよ。\nそれから、どこかで酔っ払ってるのを見つけたら、次の港まで甲板掃除だぜ。";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "つまり、俺の給料で酔っぱらって、そしたら俺が植民地中の酒場や路地でお前を探し回らなきゃならねえってわけか？ そんな幸せはいらねえよ。";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "あ、あいよ、船長！…ひっく…";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "船長か？…ひっく！…お前は…陸のネズミだ…ひっく！…船長なんかじゃねえ！…";
				link.l1 = "俺はお前みたいな奴を何百人も斬り捨ててきたんだ、白兵戦でな。だから、とっとと失せろ、この酔っぱらい。";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "船長…ひっく！…あ、あの襲撃であのボロ船の船長かい？…ひっく！…";
				link.l1 = "海でこの水槽が水平線に見えたら、すぐに海に飛び込んだほうがいいぜ。俺の船とやり合うより、 サメと一緒にいたほうがまだ生き残れるからな。さあ、とっとと失せな！";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "船長だと？…ひっく！…お前なんざ船長じゃなくてミルク飲みのガキだろうが！…お前のか、母ちゃんがまだ娘だった頃…ひっく！…俺はもう海を渡ってたんだぜ…";
				link.l1 = "でも、お前の母ちゃんはきっと喜ぶだろうな。俺みたいなガキが船長になったのに、 お前は相変わらず酔っ払い水夫のままで、甲板掃除しかできねえんだからよ。";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "船長か？…気をつけろよ…ひっく！…船長…てめえの歯を全部ぶっ飛ばしてやるぜ…ひっく！…まばたきする暇もねえからな！…";
				link.l1 = "反動で死ぬぞ。出て行け！やれるもんなら俺の歯をぶっ飛ばしてみろ…";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "船長だと？…どう見ても…ひっく…ただのボロ野郎じゃねえか…";
				link.l1 = "まだ自分の顔を鏡で見てないみたいだな……";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "か、船長？…俺は…ひっく…あんたの船で働くなんて…ひっく…絶対に同意しなかったぜ…";
				link.l1 = "誰もお前を俺の船に招待してねえんだ、だから同意する理由もねえだろ。どけ。";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "ひっく！";
			link.l1 = "寝ろ。";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "ひっく！…ああ…まだ遠いのか… ";
			link.l1 = "もうすぐだ、我慢しろ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "だ、だれだ…ひっく！…お前は…？";
			link.l1 = "俺は船長だ "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "悪いな、相棒、急いでるんだ。";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "船長…ひっく…し、船長…助けてくれ！俺…いや…ひっく…友達が…本当に助けが必要なんだ！頼む。";
			link.l1 = "俺は夜中に出会う酔っ払いどもの問題をいちいち解決してやるつもりはねえんだ。";
			link.l1.go = "NightAdventure_End";
			link.l2 = "よし、そこのお前の仲間に何があったのか話してみろ。";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "俺の友達さ…まあ、あいつはな…酔っ払っちまったんだ。とにかく…ひっく…酔い潰れちまったんだよ…";
			link.l1 = "もちろん、当直中に酒を飲んでいた水夫どもは俺が酔いを覚まさせてやったが、かなり荒っぽいやり方だったぜ。 あんたの友達にはそこまでする必要はねえだろう。";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "いやだ！あいつは…あいつは衛兵と一緒なんだ！あいつ、うう…衛兵と口論してさ。それで喧嘩になったんだ。それで…ひっく…牢屋に連れていかれた…ただの酔っ払いなんだよ！";
			link.l1 = "「で、今度は俺に何の用だ？あいつが悪いんだぜ、自業自得さ。酒を控えるべきだったし、 少なくとも一人で揉め事を探しに行くもんじゃねえ…」";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "看守に話せよ、船長…ひっく！…船長！あいつが放してくれる…放してやれって！うーん…ここだ…ひっ！…お前は運がいいな…俺の友達がさっき…口論して…まあ…俺の顔を殴ろうとしたんだ…でも…ひっ！…武器は持たなかったんだよ…";
			link.l1 = "今じゃ夜になると酔っ払いどもを牢屋から引っ張り出すくらいしかやることがねえ。 あいつはしばらくそこで反省させとけ。次はもうちょっと考えてから行動するだろうさ。";
			link.l1.go = "NightAdventure_End";
			link.l2 = "ああ、くたばれ。わかったよ、監守に話してくるぜ。";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "看守は俺の訛りを気に入らねえだろうな。どうせ後で総督に報告するだけさ。だから俺抜きで行ってくれ。";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "悪いがな、相棒、俺にはこの町の牢屋へ行く道は閉ざされてるんだ。看守は俺の顔を聖画みたいに飾ってるし、 あいつらの“親切な”部屋に住むつもりもねえ。だから悪いが、力にはなれねえよ。";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "あ、ありがとう…船長。それに、俺の友達の分も。ほ、ほら…これをあんたに。";
			link.l1 = "次は、友達が酔っ払って衛兵と喧嘩しようとしたら、ちゃんと見張っておけよ。 船長が酔っ払いのために看守と交渉するために街を歩くなんて、毎晩あることじゃねえからな。幸運を祈るぜ。";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "おおっ！…そうか、俺は知ってるぜ…ひっく…どうやって俺の…と、友達を…ひっく…解放するか…ひっく…衛兵！街にスパイがいるぞ！…ひっく…";
				link.l1 = "お前は仲間を助けるにはずいぶんと悪い手を選んだな。";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "あ、よ、よそ者……ひっく！…お前…お前は面倒なことになるぜ…ひっく！…よし…ここには…ひっく！…全部俺が仕切ってるからな。";
				link.l1 = "もちろんだ。何かあったら、すぐにお前のところへ行くぜ。";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "ああ…お前は…ひっく…犯罪者だな！衛兵！";
				link.l1 = "ああ、今はそんな口をきくのか！";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "ああ、なんて……ひっく！……すまねえ。で、もしも……俺に……ひっ！……看守と交渉させてくれたら、あんたは……ひっ！……俺の友達のためにどうだろう？……";
				link.l1 = "いや、俺のために交渉する必要はねえよ、ありがとな。幸運を祈るぜ。";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "だ、誰だ…ひっく…お前は…？";
			link.l1 = "俺は船長だ "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "悪いな、相棒、急いでるんだ。";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "船長…ひっく…し、船長…頼む、町の近くの洞窟まで送ってくれ…ひっく…ん？お、お願いだ。";
			link.l1 = "洞窟へ？よくわからねえな。なんで洞窟に行くんだ？それに、なんで俺が必要なんだ？";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "あのさ…せ、船長…ひっく！…飲み代の金が…もうなくなっちまって…それで…ひっく！…洞窟に…隠し財産があるんだ、だから…ひっく！…でも俺…その…一人でジャ、ジャングルを…ひっく！…夜に行くのが怖くてさ…だから…";
			link.l1 = "離れろ、俺は暇じゃねえんだ！";
			link.l1.go = "NightAdventure_End";
			link.l2 = "よし、行くぞ。お前一人じゃたどり着けそうにねえからな\n";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "ただ…ひっく！…ゆっくり、お願いだ。俺…ひっく！…もう…立っていられねえ…";
			link.l1 = "よし、ゆっくり行こうぜ。";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "か、船長…ひっく…本当にありがとう…助かったぜ！俺…ほらよ…ひっく…あんたにやるよ。";
				link.l1 = "さあ、うっ……もういい……そんな飲み方はもうやめろよ。";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "素晴らしいですね、船長！同意してくれて嬉しいぜ。";
				link.l1 = "さて、お前の隠し財産はどこだ？\nちょっと待て、どうやら酔っ払ってねえみたいだな。";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "ああ、そんなに飲んじゃいねえよ、心配すんな。で、隠し場所のことだけど……おい、野郎ども！";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "おい、野郎ども、ここに隠し財宝を持ってきたぜ。お前らで開けてみろよ。もちろん、 うまいこと勝手に開いてくれりゃそれでもいいがな。船長、どう思う？";
			link.l1 = LinkRandPhrase("記憶を失うほど飲んじまった方がまだマシだと思うぜ。少なくとも生き延びられるからな。\nそして今はもう、道は一つしかねえ…… "," お前、あんまり頭が良くねえみたいだな。軍艦の船長を襲おうなんてよ・・・ "," お前、死に急いでるんじゃねえか？こんなことに手を出すなんてよ…");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "まあ、円満に別れるのが一番だろうな。で、いくら必要なんだ？";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "じゃあ、楽な方法で隠し場所を開けるつもりはねえのか？";
			link.l1 = "残念だが、それがあんたの人生最後の隠し財産だったようだぜ。";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "ああ、俺たちは欲張りじゃねえ。ただ "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "残念だが、それがあんたの人生最後の隠し財産だったようだぜ。";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "わかったよ、好きにしな。もう二度と酔っ払いなんか助けてやらねえからな……";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "船長、その気前の良さには驚いたぜ。もっと分けてくれる気はねえか？";
			link.l1 = "もう全部渡しただろう。俺はもう行くぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "お、お前……ひっく！…誰だよ……";
			link.l1 = "俺は船長だ "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "悪いな、相棒、急いでるんだ。";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "船長かい？…ひっく…おお、 "+GetAddress_Form(NPChar)+" …ご、ごめんなさい…ひっく！…こんな状態で…よかったら一緒に飲まないか？ひっく！…お、お願いだ。"; 
			link.l1 = "「悪いな」 "+GetAddress_Form(NPChar)+"、でも俺は忙しいんだ。"; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "仲間に入る？悪いが、今日は飲まねえよ……"; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "ああ、飲む必要は……ひっく……ねえよ！実はな……その……友達と一杯やっちまってさ……だから……もう酔っ払ってるんだよ……わかるだろ？";
			link.l1 = "よし。で、酔いを覚ます手伝いが必要か？";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "いや、そうでもねえ！俺は元気だぜ。今は遊びたい…カードだ、つまり遊びたいんだ…ひっく！…でもみすぼらしい…ペソなんかじゃ…このボロどもと…ひっく！…酒場で…じゃなくて…本物の貴族とだ！ひっく！…本当の賭けでよ！…"; 
			link.l1 = "「すまねえ」 "+GetAddress_Form(NPChar)+"……まあ、何と言うか……俺は賭博は好きじゃねえんだ。船乗りどもに給料を払わなきゃならねえし、船の維持費もかかるからな……"; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "ふむ、よし、やろうぜ。酒場に行くか？"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "わかった！ただ…ひっく…ゆっくり、た、頼む…。俺は…ひっく…もう…立って…いられねえ…"; 
			link.l1 = "よし、ゆっくり行こうぜ。"; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "そのテーブルのために…ひっく！…行こうぜ！"; 
			link.l1 = "よし、行くぜ。"; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "お、お前には…わからねえよ、せ、船長…ひっく…本物の貴族様に会えてどれだけ嬉しいか！ひっく…こんな荒れ地じゃ…たいてい…ひっく…クズばっかでよ…"; 
			link.l1 = "ああ、こんなのはこの辺の植民地じゃありふれてるぜ。さて、勝負するか？"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "ああ、やろうぜ！ひっく…！賭けは何だ？"; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "俺たちは1000ペソを賭けて勝負するぜ。"; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "俺たちは2,000ペソを賭けてるぜ。"; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "うーん、悪いな、今は懐が空っぽみたいだ……"; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "な、なんだと？…お前は…ひっく…俺と遊ぶ金が…ないのか？…"; 
			link.l1 = "まあ、そんなこともあるさ。次は遊ぼうぜ、心配すんな。"; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "ヒック！…楽しかったぜ、船長！ヒック！…"; 
			link.l1 = "俺も同感だぜ。せめて仕事から少しは休んだらどうだ。"; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "ひっく！…楽しかったぜ、船長！ひっく！…"; 
			link.l1 = "同感だ。せめて仕事から少し離れて休んだらどうだ。"; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "たまには……ひっく！……い、いい仲間と……ひっく！……一緒に過ごすのも大事だよな。ありがとよ……ひっく！……一緒にいてくれて！"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "ああ、今さっき木っ端みじんに吹き飛ばされたばかりだぜ。\nそれにしても、俺が勝てるはずだった時でさえ、どうしてお前が勝っちまったんだ？"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "同じく、ゲームと会話をありがとう。"; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "たまには……ひっく！……いい連中と……ひっく！……一緒に過ごすのも大事だよな……ひっく！一緒にいてくれて本当に……ひっく！……ありがとうよ！"; 
			link.l1 = "同様に、遊びと会話に感謝するぜ。"; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "ただの運だよ、せ、船長……ひっく！"; 
			link.l1 = "ただの運じゃなさそうだな……。"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "何を言いたいんだ？俺がイカサマしたとでも言うのか？全部自分の目で見てただろ、 同じデッキからカードを引いたんだぜ！"; 
			link.l1 = "ああ、見たぜ。さっきまで舌がろくに動いてなかったくせに、今じゃ酔ってないみてえにしゃべってるじゃねえか。"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "ああ、くそっ！しかも見事にバレちまったな！いいさ、認めるぜ、もう隠さねえよ。酔っ払ってなんかいなかった。 でもな、あんたも知ってるだろ？金持ちで酔っ払ってるって噂の奴がカードをやりたがってると、 みんな簡単に引っかかるんだ。賭けるもんがある連中は、ほとんど真っ先に酒場に駆け込んで、 どうせ酔った金持ち貴族から大勝ちしてやろうって思うもんさ。言っとくが、俺を見抜いたのはあんたが初めてだぜ。"; 
			link.l1 = "それで、これからどうするんだ？大人しく俺の金を返す気はあるのか？"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "ははは、笑わせるなよ、船長。もちろん、返金なんてしねえぜ！それに、俺に無理やり返させようなんて思うなよ。 俺は簡単に、迷い込んだ船長に侮辱された尊敬される貴族のふりもできるんだぜ。だから忠告してやるよ：負けを認めて、 とっとと立ち去るんだな。"; 
			link.l1 = "まあ、俺にもっと運の悪い状況で捕まらないことを心から祈るぜ。そうなったら、 もうそんな風に笑っていられねえからな。じゃあな。"; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "それから、俺の忠告だが、自分の剣を手に入れる時間を作ったほうがいいぜ。"; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "やれるもんならやってみろよ……ここは酒場だぜ、人がいっぱいいるんだぞ……"; 
			link.l1 = "俺はただの流れ者の船長だぜ、礼儀なんて気にする理由があるか？\n夜の港の酒場で何が起きるってんだ……剣の腕ならお前よりずっと上だぜ。"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "ああ、そういうことか！？さて、これから本当の持ち主が誰か見せてやるぜ！"; 
			link.l1 = "お役に立ちますぜ…"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "船長かい？…ひっく…おお、 "+GetAddress_Form(NPChar)+" …す、すまねえ…ひっく！…この…ありさまで。手を貸してくれねえか？ひっく！…お、お願いだ。"; 
			link.l1 = "「悪いな」 "+GetAddress_Form(NPChar)+"、でも俺はいそがしいんだ。"; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "ああ…聞いてる。"; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "ただ…ええと…もうちょっと酔っちまっててさ…見りゃわかるだろ…ひっく！…な？"; 
			link.l1 = "正直に言うと、そうだ。酔いを覚ます手伝いが必要か？"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "別に！俺は、だ、大丈夫だ。女が欲しいんだ。でも、酔っ払いすぎて……ひっく……お、おかみさんに追い出されちまうよ、だからさ。頼む……ひっく……交渉してくれねえか？金は払うぜ。"; 
			link.l1 = "申し訳ない。 "+GetAddress_Form(NPChar)+"、でもどう言えばいいか……俺は娼館には行かねえんだ。名誉とか評判とか……わかるだろう…"; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "ああ、わかった、手を貸してやるよ。"; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "ただ…ひっく！…ゆっくり、お願いだ。俺…ひっく！…立って…いられねえ…"; 
			link.l1 = "よし、ゆっくり行こうぜ。"; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "「ほら、金だ……ひっく……！ここで待ってる、ひ、ひっ……。」"; 
			link.l1 = "よし、すぐ戻るぜ。"; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "い、いいから…持ってきてくれ…ひっく…一番いいやつを…！そうだ…"; 
			link.l1 = "わかったよ、もういいってば。"; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "ひっく！…あとどれくらいだ？"; 
			link.l1 = "この植民地で一番の女が二階であんたを待ってるぜ。"; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "「はい！…今夜は…素晴らしい…あ、ありがとう、」 "+GetAddress_Form(NPChar)+"…残りの金は…ひっく…持ってけ。俺は沈む…自分の…美しぃ…お、おんなの…中へ……";
			link.l1 = "じゃあ、楽しんでくれよ。"; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "ひっく！…あとどれくらいだ？";
			link.l1 = "すぐに交渉するから、我慢して待ってくれ。";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "ひっく！";
			link.l1 = "お前は寝る必要があるぜ。";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "ひっく！…ああ…まだ遠いのかよ…";
			link.l1 = "もうすぐ着くぜ、我慢しな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "はぁ？お前は誰だ？ここで何してやがる？";
			link.l1 = "俺も同じことを聞きたいぜ。";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "俺たち？ああ、俺たちは……えっと……ここで花を集めてるんだ……";
			link.l1 = "墓の花だと？で、標本集めは順調か？";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "彼女のことか…薬草と関係あるのか？";
			link.l1 = "そうか……ここで何が起きているのか、だいたい分かったぜ。";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "俺たちは略奪者じゃねえ！そんなふうに言うな！俺たちはただ……";
			link.l1 = "「何だって？」";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "えっと、俺たち…父さんに会うのを禁じられてるんだ！彼女の父さんにもな！だから…だから誰にも見られない場所を探してたんだ。二人きりになりたくてさ。どうせこの扉の鍵は壊れてるし、 ここに入るのは簡単なんだよ…";
			link.l1 = "今になって、あの落ち着かない魂の不気味なうめき声が何だったのかわかったぜ……";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "「ふん、全部わかったんなら、もう俺たちに構わねえでくれよ？」";
			link.l1 = "墓所でデートの約束なんて、怖くねえのか？あんまりいい場所じゃねえぜ…";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "俺たちは迷信深くなんかねえよ！それに、たとえ怖かったとしても、他に選択肢はねえだろ？\n町じゃ親にすぐバレちまう。でもここなら誰にも告げ口されねえ。\nだから今は、これが一番いい手なんだぜ。";
			link.l1 = "本当に悪いんだけど、他の場所を探してくれないか？\n誤解しないでくれ、若さとかそういうのは分かってるんだが……毎晩地下墓地から聞こえてくるあんたたちのデートの物音やうめき声で、墓守が半分死にかけてるんだよ。";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "うーん……見張りを脅かすのは俺たちの計画にはなかったぜ。\nでもよ、他にどこで会えるってんだ？それとも、青空の下でデートしろってのか？";
			link.l1 = "愛に境界はねえさ。誰にも邪魔されねえ場所を探しな。そしたら、お前らも誰にも邪魔されねえだろう。たぶんな。あと、 親とはちゃんと話をつけとけよ――いつまでも隠れてるつもりじゃねえだろ？";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "わかった、何とか考えてみるさ……もう見張りを脅かしたりしねえ、俺の言葉だ。";
			link.l1 = "素晴らしい。幸運を祈るぜ！";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "何だって！？";
			link.l1 = "「ああ、なんでもねえ…」";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの街の市民だ。剣を下ろしてくれ。","聞いてくれ、俺はこの街の市民だ。剣を下ろしてくれ。");
			link.l1 = LinkRandPhrase("いいだろう。","お望み通りに……","おっしゃる通りだな…");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
