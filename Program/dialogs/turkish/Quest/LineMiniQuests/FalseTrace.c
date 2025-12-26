void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Hata. Bize bildirin.";
			link.l1 = "Tabii!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "İyi günler, kaptan... ehm... öhö-öhöm! Kahrolası madenler... Kendimi tanıtayım. Adam Rayner. Ben sade bir adamım ve uzun lafları sevmem, o yüzden hemen konuya gireceğim. İyi para kazanmak ister misiniz? Size küçük bir iş teklif ediyorum, ki ikimizden biri tek başına bunun altından kalkamaz.";
			link.l1 = "Heh! İyi para mı? İlginç. Dinliyorum, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Biliyor musun, üzgünüm ama sana pek güvenemiyorum. O yüzden seninle iş yapmayacağım.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Güvenilir mi? Ha-ha! Bir adamı yüzüne bakarak yargılamamalı. Neyse, boşver. Kolayca para kazanabileceğin iyi bir fırsatı kaçırdın. Ben daha uyumlu birini bulurum...";
			link.l1 = "Konuşmamız bitti, efendim. Hoşça kalın!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Senin gibi hızlı düşünen biriyle iş yapmak zevk, Kaptan. Şimdi, iş basit: Yerel limanlardan birinden yakında yelken açacak bir fluyt var, içinde hatırı sayılır miktarda gümüş yüklü. Tek başına gidiyor, koruması yok. Saçma, değil mi? K-kha\n Çocuk oyuncağı. Ben sana nerede ve ne zaman olduğunu söylüyorum, sen ganimeti alıyorsun, ben de payımı alıyorum.";
			link.l1 = "Ve tabii ki, bunu hemen nakit olarak almak istiyorsun, değil mi?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Ben zavallı bir serseriye mi benziyorum, kaptan? Hiç sanmam. Bu baskında sana katılacağım ve birlikte halledeceğiz. Çatışma sırasında ambarlarda saklanacak değilim, tam tersine - beni, tabii ki geçici olarak, bizzat senin subayın olarak çıkarma ekibine almanı istiyorum\nİşimden anlarım, insanı bıçaklamayı da, ateş etmeyi de bilirim. Yani senin gibi ben de boynumu riske atacağım... khe... kha! Fluytu ele geçirdikten sonra payımı ödersin.";
			link.l1 = "Ganimetten kendin için ne kadar pay istiyorsun?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Açgözlü bir adam değilim, kaptan. Payım, eski sandalımın ambarına sığacak kadar; yani yaklaşık 200 gümüş sandığı. Aldığım bilgilere göre fluytta en az 2.000 gümüş sandığı olacak, bu yüzden onda birini alacağım. Bu adil, sence de öyle değil mi?";
			link.l1 = "Bilgi için ganimetten onda bir mi istiyorsun? Ben böyle bilgileri yerel meyhanede sarhoşlardan bir kadeh rom karşılığında alıyorum. Hayır, yolumuz bir değil dostum!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Sanırım katılıyorum. Teklifini kabul ediyorum, Adam. Aramıza hoş geldin. Şimdi, verdiğin bilgiye gelelim: nereden, nereye, zaman, geminin adı?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Ne cimriymişsin sen, Kaptan! O zaman sana hiçbir şey yok! Görüşürüz!";
			link.l1 = "İyi şanslar! Şu karanlık işin için başka bir saf bul!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Fluyt'un adı "+pchar.questTemp.FalseTrace.ShipName+", Cartagena'dan ayrılıp yelken açıyor "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Ama fazla vaktimiz yok. İki hafta, en fazla üç. Üç hafta içinde onu bulamazsak, işimiz biter.";
			link.l1 = "O halde vakit kaybetmeyelim! Macera bizi bekliyor!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Bir şey mi istediniz, kaptan?";
			link.l1 = "Boşver, önemli değil.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Beni görmek mi istediniz, Kaptan?";
			link.l1 = "Bunun olacağını tahmin ettiğini sanıyorum... Gümüş nerede, kahretsin? Nerede o? Seninle konuşuyorum! Fluyt'ın kaptanı bana bunun bir erzak gemisi olduğunu söyledi! Bana yalan söyledin!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Sakin ol, Kaptan. Her şeyi anlatmaya çalışacağım.";
			link.l1 = "Elbette yapacaksın! Zaten sakinleştim! Şu anda seren direğinden sallandırılmıyor olmanın tek nedeni, niyetlerini hâlâ anlayamamam. Bu fluytu benimle birlikte kovaladın, başından beri gümüş olmadığını bildiğin halde. O yüzden, lütfen kendini açıkla.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Evet, seni gerçekten kandırdım, Kaptan. Ama istediğimi yaptırmanın tek yolu buydu, ele geçirmek için... öhöm öhöm! Şu lanet fluytu ele geçirmek için\nAma sana olan borcumu ödeyeceğime söz veriyorum. Şimdi neden böyle yaptığımı anlatayım. Fluytta bir kadın buldun mu? Tayfanın onu gemine götürdüğünü gördüm...";
			link.l1 = "Hm... Demek kıza ihtiyacın vardı? Ve bu yüzden beni denizde savaşa zorlayıp bunca insanın ölümüne sebep oldun!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "Karım. Katerine Rayner. Üç ay önce bu zavallı kaptanla benden kaçtı. Onları bulmak için elimden geleni yaptım ve başardım. İkisi de şuraya gidiyordu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" . Katerine'i geri getirmek ve o karı hırsızıyla başa çıkmak için daha iyi bir yol düşünemezdim\nSana gerçeği söyleseydim, çekip giderdin. O yüzden sana gümüşle dolu bir fluyt hakkında heyecanlı bir hikaye anlatmam gerekti.";
			link.l1 = "Hmpf... Karın seni terk etti, değil mi? Çok ilginç!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Bu benim yasal karım, onu seviyorum ve başka hiç kimsenin onunla birlikte olmaya hakkı yok! O alçak, ben... uzaktayken ona romantizm ve benzeri saçmalıklar hakkında güzel yalanlar söylemiş. Kadınları tanımıyorsun galiba? O da bu zırvalara inanmış, zavallı kız, ve onunla kaçıp gitmiş.";
			link.l1 = "Pekâlâ, bak, aile hayatın beni pek ilgilendirmiyor, o işi karınla hallet. Ama masraflarımı karşılayacağından bahsettin, değil mi? Doğru mu duydum?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Evet, doğru duydunuz, kaptan. Bir iyilik karşılığında bir iyilik. Şu anda param yok, ama eğer Katerine ve beni "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", sana hiç zahmet etmeden biraz altın bulabileceğin tamamen güvenilir bir bilgi vereceğim.";
			link.l1 = "Çok ilginç. Peki, bana bu tamamen güvenilir bilgiyi neden hemen şimdi anlatamıyorsun?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Çünkü, bu bilgiye henüz sahip değilim. Sana ayrıntılı olarak anlatayım. Squint-eyed Solly adında bir talih avcısı var - hiç duydun mu? - Blueweld yakınlarında bazı altın madenlerini soymaya hazırlanıyor\nBazı olaylar yüzünden, tüm altınını gizli bir yere bırakmak ve korumak için birkaç nöbetçi bırakmak zorunda kalacak. Kendisi ise yaya olarak Belize'ye ya da Blueweld'e gidip bir gemi bulmaya çalışacak\nSolly'nin tayfası arasında bir ajanım var, beni bekliyor olacak "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Oraya demir attığımızda, bana Solly'nin ganimetlerini nereye sakladığını söyleyecek\nSen oraya gidip nöbetçileri ortadan kaldıracak ve tüm altını kendin alacaksın. Aslında bunu kendim yapacaktım ama mevcut durumu göz önünde bulundurunca her şeyi sana bırakıyorum. Ücret falan yok.";
			link.l1 = "Hikayen, daha önce anlattığın gümüş yüklü fluyt masalına çok benziyor. Beni bir kez kandırdın zaten. Bu sefer yalan söylemediğine nasıl güvenebilirim?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Sana söz veriyorum. Başka bir teminatım yok. Ama doğru söylüyorum, yemin ederim khe... kha...  kahrolası madenler!";
			link.l1 = "Pekala. Şimdi git, söylediklerini düşüneceğim.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Fazla düşünme. Şaşı Solly hazineleri için geri dönecek, bunu anlamış olmalısın. Hesaplarıma göre, oraya varmak için sadece iki haftan var "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Bunu aklımda tutacağım. Şimdi git ve tayfanın kaldığı yere katıl. Sanırım varışımıza kadar eşinden ayrı kalman daha iyi olur. Artık gidebilirsin.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Beni mi çağırdınız, kaptan?";
			link.l1 = "Evet. Adam Rayner, seni tutuklayıp hapse atacağım. Beni kandırdın ve seni tecrit edip yetkililere teslim etmekten başka bir seçeneğim yok.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Gerçekten mi? Bunu yapmanı bekliyordum, Kaptan. Özellikle de ambarımıza gelip başka adamların karılarını ayartan o pis herifle konuştuğundan sonra. Onun tarafında olmaya karar verdin, değil mi Kaptan?";
			link.l1 = "Sana ne! Beni kullandın, bana ihanet ettin, şimdi de yine saçma sapan hazine hikayeleriyle beni kandırmaya çalışıyorsun! Lostromo, bunu götür!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, o kadar da acele etme, Kaptan... Lostromosun ve tayfanın geri kalanı buraya hemen giremeyecek. Kapıyı kilitlediğimi fark etmedin mi? Şimdi burada yalnızız - sadece sen ve ben. Hadi bakalım Kaptan, neye kadirsin görelim!";
			link.l1 = "Gerçekten mi? Gerçekten şansın olduğunu mu sanıyorsun?! Bunu çok pişman olacaksın, alçak!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Bu daha iyi... Silahlarını bırak, alçak! Lostromos! Bu serseriyi zincire vurun ve ambarın dibine atın!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Teşekkür ederim Kaptan, karımı geri getirmeme yardım ettiğiniz için! Adam Rayner size minnettar, bunu unutmaz, ha-ha, yemin ederim... kha! Kahrolası mayınlar! Şimdi, Şaşı Solly'ye gelelim. Adamım bana zaten her şeyi anlattı. Solly bütün ganimetini San Juan del Norte koyundaki bir mağarada bırakmış. Kendisi şu anda Blueweld'de\nAcele etmelisiniz, dostumun dediğine göre sadece beş gününüz var. Adamlarınızı da yanınıza alın, Solly'nin haydutları dişli, başınızı ağrıtacaklar\nVeda vakti. Tekrar teşekkürler Kaptan, yolunuz açık olsun!";
			link.l1 = "Bol şans, Adam. Karını sakın üzme!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Kaptan, neden dünyada bu körfeze çıktık? Sana adamımın beni limanda beklediğini söylemiştim "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Oraya ormanın içinden yürüyerek mi gitmeyi düşünüyorsun?";
			link.l1 = "Kötü tahmin, Adam. Gerçekten de saçmalıklarına bir kez daha inanacağımı mı sandın? Beni tamamen aptal mı sanıyorsun? Bu sefer karınla bir anlaşma yaptım.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Ne?! Ha! Karımla ne anlaşması? Neyden bahsediyorsun, seni çürük balık?!";
			link.l1 = "Sahte bilgin yüzünden boş bir fluyt ele geçirdim ve kaptanını öldürdüm. Bunu yaptığım için pişmanım, ama artık pişmanlık için çok geç. Anladığım kadarıyla, karın o denizciye âşıktı. Bu yüzden seni öldürmemi istedi. Şimdi bu koyda olmamızın sebebi de bu.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "İnanamıyorum! Katerine ... ne adi kadın! Neyse, hak ettiğini bulacaksın... Peki, sana nasıl ödeme yapacağını söyledi, ahmak? Beş kuruşu yok, kaçmak için tüm mücevherlerini bile sattı o kaptanla!";
			link.l1 = "Bu seni ilgilendirmez, alçak. Ama artık konuşmamızın sonuna geldik. Seni cehenneme göndereceğim, zaten orada olman gerekiyordu!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Ne yapabileceğini görelim, çürük ringa!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Neden gemime saldırdın, pislik herif? Bunu gerçekten anlayamıyorum...";
			link.l1 = "Kuzu rolü yapma, kaptan. Ne tür bir yük taşıdığını biliyorum. Ona ihtiyacım var.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Kargo mu? Ha-ha! Burada ne tür bir kargo görmeyi umuyordun? Ambarlarım bomboş!";
			link.l1 = "Ne dedin, alçak! Bir daha söyle!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Tekrar ediyorum - gemimde hiçbir yük yok. Bu fluyt, yiyecek arayan bir gemi ve gidiyor "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" askerler için bir top mermisi ve erzak yükü götürmek için.";
			link.l1 = "Beni kandırıyorsun. Ambarların gümüşle dolu olmalı. Ve bu konuşma bittiğinde onları kontrol edeceğim...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Bu gümüş hikayesini sana kim anlattı bilmiyorum. Ama bu tam anlamıyla saçmalık... Sana yenildim, bu yüzden pes ediyorum. Al, kılıcım burada. Şimdi gidip ambarları kontrol edebilirsin. Hepsi boş.";
			link.l1 = "Pes mi çekiyorsun? Hayır! Şahitlere ihtiyacım yok. Kılıcını al ve dövüş, yoksa seni koyun gibi doğrarım.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Akıllılık ettin, iyi oldu. Sanırım senden bir fidye koparabilirim... Hey, çocuklar - kaptanı ambarın içine atın!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Onu öldürdün, seni alçak! Namussuz! Zavallı "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Bu da ne? Nereden çıktın sen, canım?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Yaptıklarının bedelini cehennemde ödeyeceksin. Kahrolası herif!";
			link.l1 = "Sakin ol, genç hanım! Bana küfrederek şansını zorlama – yoksa seni de kaptanının yanına yollarım!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Sen ... bir kadına el kaldırmaya cesaret edemezsin!";
			link.l1 = "Sana bunu yapmam bile gerekmeyecek. Seni vurabilirim. Ya da seni denize atarım, gerisini köpekbalıkları halleder... Şimdi ne bekliyorsun? Gemime git. Korkma - kimsenin sana zarar vermesine izin vermem, sen de sessiz kalırsan sana dokunmam...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Ne... ne yapacaksın ona?";
			link.l1 = "Bu da ne? Nereden çıktın sen, canım?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Zavallı "+pchar.questTemp.FalseTrace.CapName+"! Söylesene - onu öldürecek misin? Yapma...";
			link.l1 = "Şimdi dinle, hanımefendi - eğer onu öldürmek isteseydim, çoktan yapardım. O ambarımda kalacak, sonra ya serbest bırakırım ya da fidye isterim... ikincisi daha olası. Şimdi, lütfen uslu bir kız ol ve gemime gel. Korkma - kimsenin sana zarar vermesine izin vermem, sen sessiz kalırsan ben de sana dokunmam...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Benden ne istiyorsun? Dediğin gibi beni köpekbalıklarına mı atacaksın? Hayatımı mahvettin ve ben...";
				link.l1 = "Hadi ama, canım. Kimse seni bir yere atacak değil. Sadece durumu netleştirmek istiyorum, çünkü bu fluyt'a senin yüzünden saldırdım, başka bir sebebim yoktu.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Benden ne istiyorsun? Nerede "+pchar.questTemp.FalseTrace.CapName+" Fidye mi? Sana fidye mi lazım?";
				link.l1 = "Pekâlâ hanımefendi, bu anlamsız sorular silsilesine bir son verelim. Sizi bunun için çağırmadım. Bir gerçek netleşti ve bence bu sizin de ilginizi çekecek.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Benim yüzümden mi? Yani diyorsun ki, gemimize saldırıp sevgilimi öldürmen benim suçum? Zavallı "+pchar.questTemp.FalseTrace.CapName+", sana ne yaptı? Yaptıklarının hesabını Tanrı'ya vereceksin...";
			link.l1 = "Aynı eski yahni! Köpekbalığı muhabbetimize geri dönelim mi?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Sakin misin şimdi? Harika. Şimdi beni dinle! Gemiyi saldırdım çünkü içinde hatırı sayılır miktarda gümüş taşındığına dair bir bilgi aldım. Bu bilgiyi de Adam Rayner'dan edindim.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! Ne?! Adam? Nerede o? Burada mı?";
			link.l1 = "Demek ismi biliyorsun... Katerine. Ve gördüğün gibi, senin hakkında zaten her şeyi biliyorum. Sanırım Adam Rayner senin kocan, değil mi?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Evet. Ben bu canavarın karısıyım. Bu kâbusun sonunda bittiğine inanmıştım... Beni yakalaman için seni mi tuttu?";
			link.l1 = "Genelde böyle oldu. Adam bana gümüş hakkında yalan söyledi, böylece fluyt'u ele geçireyim diye "+pchar.questTemp.FalseTrace.ShipName+"Kesinlikle, seni geri getirmeye kararlıydı. Çeyrek saat önce bana bütün yaptıklarını anlattı.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "Ve... ne istiyor? Sana ne söyledi?";
			link.l1 = "Yasal karısının ona geri dönmesini istiyor. Beni kandırdığı için karşılık olarak bana Şaşı Solly'nin altını hakkında bilgi verecek. Ve ikinizi de götüreceğim "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Hayır... (ağlayarak) O herife geri dönmek istemiyorum! Ondan kaçmak ve izimi kaybettirmek için çok uğraştım, ama yine de beni buldu... Alçak! Haydut! Kahrolası hırsız!";
			link.l1 = "Sakin ol, Katerine... Ağzını topla. Sonuçta o senin kocan. Üstelik, seni sevdiğini söyledi.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(ağlayarak) Kocam mı? Kocamın kim olduğunu biliyor musun? O bir eski mahkum, bir hükümlü, şimdi ise en zalim haydutlardan biri "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! O aşağılık, pis bir hayvan ve onun gözünde ben sadece bacaklarımın arasındaki bir delikten ibaretim!";
			link.l1 = "Daha önce onunla evlenmeden her şeyi görmemiş miydin?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Başta farklıydı... Ve geçmişi bana öyle romantik gelmişti ki... Ama sonunda her şey değişti. Onu görmek bile istemiyorum artık, bırak birlikte yaşamayı, bunu anlayamıyor musun? İstemiyorum! Özellikle de şu fluyta yaptığı saldırıdan sonra, ki bunu o ayarladı!";
			link.l1 = "Hm... Peki, sana ne yapmalı, güzel hanımefendi?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Ne yapmalı? Ne yapacağımı biliyorum. Sen kocamın günahlarının bir aracısın. Masum bir adamı öldürdün, bana hayatımda iyi davranan tek adamı. Günahlarının bedelini öde, kaptan. Adam'ı öldür. Hem de gözlerimin önünde. Bu pisliğin can verdiğini görmek istiyorum, cesedine tükürmek istiyorum. Öldüğünde, hazinelerini nereye sakladığını sana söyleyeceğim. O sarhoş aptal bir keresinde bana sakladığı yeri anlatmıştı, ha-ha, kendisi bile hatırlamıyor!";
				link.l1 = "Heh! Görüyorum ki sen acımasız bir kadınsın, Katherine!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Fluyt'un kaptanı. Onu hapsettiniz. Lütfen onunla konuşun, yalvarırım! Hayatımız ve özgürlüğümüz için size bir şey teklif edecektir! Bir yolunu bulacaktır! Ben... Ben artık Adam'a dönmek istemiyorum, bundan sonra "+pchar.questTemp.FalseTrace.CapName+"   kocam! Ne olur yalvarırım – beni tekrar Adam'a, o canavara götürme!";
				link.l1 = "Hm. İlginç. Peki, esirim bana ne sunabilir ki? Onu yetkililere teslim edip fidye alabilirim, ayrıca Şaşı Solly'nin altınını da alacağım...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Zulümden bahseden kim, bak hele. Şuraya yelken aç: "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", Adam'ın dediğini yap, ama limana değil, en yakın koya çık. Üçümüz oraya gideceğiz ve o alçağı sen öldüreceksin\nİş bitince sana gizli yeri söyleyeceğim. Yemin ederim, yalan söylemiyorum. Sözümün Adam'ınkinden daha güvenilir olduğuna inanıyorum—seni bir kere kandırdı, değil mi? Ne dersin, kaptan?";
			link.l1 = "Evet... Boşuna dememişler, karı koca aynı kumaştan olur diye. Sana bakınca, Katerine, Adam için en uygun eşin sen olduğunu görüyorum... Onu bu kadar çok öldürmek istiyorsan, sarhoş uykusunda bıçağı saplayıver gitsin... Başçavuş! Götürün onu!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Beni kandırmaya ve kendi çıkarları için kullanmaya çalışan alçaklardan nefret ederim. Peki, Katherine, teklifini kabul ediyorum, çünkü Adam'a güvenilemeyeceği artık belli oldu. Ama eğer sen de beni kandırırsan, yemin ederim seni Avrupa'nın öbür ucunda bile bulurum ve kafana bir kurşun sıkarım. Şimdi defol. Başçavuş! Götürün onu!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Bunu pişman olacaksın... Yemin ederim, ben ...";
			link.l1 = "Lostromacı! Onu koru ve varana kadar gözünü üzerinden ayırma "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Hangi gerçek? Bize ne yapacaksınız? Neden gemimizi ele geçirdiniz?";
			link.l1 = "Bir kelime etmeme izin verecek misin, yoksa başçavuşuma ağzını tıkamasını mı emredeyim?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Solly'nin altını mı? Bu herife gerçekten güveniyor musun? Yine seni kandıracak, onun huyu bu! Esirine bir sor bakalım!\n"+pchar.questTemp.FalseTrace.CapName+" gerçek bir centilmen, sözünden dönmez ve sana asla yalan söylemez!";
			link.l1 = "Beni ikna edemedin, hanımefendi. Kaptanınızla konuşacak bir şeyim yok. Onun için fidyemi alacağım, Solly'nin altınını da Adam'dan alacağım. Adam beni bir kez daha kandırırsa, onu dünyanın öbür ucunda bile bulurum ve doğduğu güne lanet eder... Başçavuş! Götürün onu!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Doğrusunu söylemek gerekirse, Adam’a güvenmiyorum... Beni yönlendirmelerinden nefret ediyorum. Peki, kaptanınla konuşup bana ne anlatabileceğini göreceğim. Şimdi gidebilirsin... Çavuş! Onu götür!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Sen zalim ve vicdansız bir adamsın! Yemin ederim ki...";
			link.l1 = "Başçavuş! Onu koru ve varana kadar gözünü üzerinden ayırma "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Artık bitti... Zavallı "+pchar.questTemp.FalseTrace.CapName+" intikam alındı, artık rahatça nefes alabilir ve kendime dul diyebilirim...";
			link.l1 = "Ben anlaşmanın kendi payıma düşen kısmını yerine getirdim, Katerine. Şimdi sıra sende.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Elbette, kaptan. Kocam—şükürler olsun ki artık eski kocam—zaten bildiğiniz gibi bir hayduttu. Olası aramalardan korktuğu için, çaldığı ganimetleri evde tutmazdı. Bir gizli yer ayarlamıştı—ama bir keresinde ağzından kaçırdı. Yine de, orayı öyle akıllıca sakladı ki—karadan oraya ulaşmak imkânsız.";
			link.l1 = "Çok ilginç... Peki, nerede?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Hispaniola yakınlarındaki küçük bir adada. Fenerde.";
			link.l1 = "Port-au-Prince deniz feneri! O, adada bulunuyor!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Muhtemelen öyle. Ganimeti orada bulabileceksiniz. Göreceksiniz. Hepsi bu kadar. Hoşça kalın, Kaptan.";
			link.l1 = "Bekle... Affet beni, Katerine, eğer edebilirsen. Umarım tüm bu felaketlerinin sorumlusunun ölümü sana en azından biraz olsun huzur getirir. Gerçekten üzgünüm...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Üzüntüne ihtiyacım yok, Kaptan. Senden istediğimi yaptın – ve senin bilmek istediğin her şeyi anlattım. Şimdi elveda, bırak beni acımla baş başa...";
			link.l1 = "Hoşça kal, Katherine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Pislik herif! Dördünü de öldürmeyi başardı! İnanılır gibi değil!";
			link.l1 = "Böyle bir dönüş beklemiyordun, Katerine? Kolay kolay öldürülemem. İki taraflı oyunları da gayet iyi oynuyorsun, söylemeliyim!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Adam'ımı öldürdün. Gerçekten seni yaşatacağımı mı sandın?! Adam'ın ölümüyle yetineceğimi mi düşündün? Hayır! Buradan asla çıkamayacaksın. Bu adadan çok uzakta olmayan bir gemi var, senin o eski tekneni de seni de denizin dibine gönderecek!\nŞimdi, bana ne yapmak istiyorsan yap.";
			link.l1 = "Sana söylememiş miydim, sevgili, beni kandırırsan kafandan olursun diye? Ne kurnaz şeytanmışsın! Ölü olunca o kadar tehlikeli olmayacaksın. Şu güzel kafana şimdi bir kurşun geliyor...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Senin için üzülüyorum, Katerine. İntikam arzun sonunda sana hiçbir fayda getirmedi. Seni kaderinle baş başa bırakıyorum - bu adada kalacaksın. Sanırım buradaki balıkçılar seni yakında bulup Hispaniola'ya götürürler. Ve Rabbim yaptığımız her şeyin hesabını bize sorsun...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "Sen dua etmelisin, canavar! Katil! Yardım edin! Kahrets...";
			link.l1 = "Yeterince duydum.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Boğul inşallah! Gemin kayalıklara çarpsın! Sen de...";
			link.l1 = "Hoşça kal, Katherine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, işte Adam'ın katili! Katherine haklıymış, bu alçak ganimeti çalmaya gelmiş!";
			link.l1 = "Ne? Katherine? Sen kimsin?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Biz kimiz? Biz, senin tarafından öldürülen Adam Rayner'ın dostlarıyız. O, kardeşliğimizin lideriydi. Şimdi lider benim, adım "+GetFullName(npchar)+", ve patronumu öldürdüğün ve karısına yaptığın şiddet için seni cezalandıracağım.";
			link.l1 = "Şiddet mi? Ne saçmalıyorsun sen?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Adam'ı arkadan bıçakladın, pis hain. Karısını, Adam'ın altınlarını nereye sakladığını söylemeye zorladın, sonra da zavallı kadını ıssız bir kıyıda ölüme terk ettin.\nAma o hayatta kaldı. Bize gelip yardım istedi, yapılan kötülüğü düzeltmemizi istedi. Seni burada bekliyoruz, günlerdir. Ve işte geldin, alçak herif!";
			link.l1 = "Ha-ha! Kesinlikle Katerine'in tarzı... Şimdi dinle, evet, Adam'ı öldürdüm, bu doğru, ama bunu yaptım çünkü karısı gerçekten benden onu öldürmemi istedi. Bu, sevgilisinin ölümünün intikamıydı. Bana ödül olarak saklanma yerini söyledi...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Yoksul dul kadına iftira atma, pislik! O zaman neden bize gelsin? Senin hayatın karşılığında tüm altını bize bırakmayı teklif etti. Parayla işi yok, senin ölümünü istiyor! Kocasının ölümü için adil bir ölüm istiyor!\nAma yemin ederim, yoksulluk içinde ölmeyecek, adım kadar eminim ki bu doğru "+GetFullName(npchar)+",   ve şimdi ölme zamanın geldi, korkak!";
			link.l1 = "Vay canına, ne muhteşem bir konuşma. İşte orada, bu komediyi bizzat izlemek için sabırsızlanıyor... Beyler?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Ne kadar da şaşkınsın, kaptan! Gümüşle dolu bir fluyt'u kaybetmek... Sana güvenmekle hata ettim. Elveda!";
			link.l1 = "Elveda, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Sana söylemiştim kaptan, sadece iki haftamız vardı! Şimdiye kadar, Şaşı Solly bütün ganimeti çoktan götürmüş olmalı. Senin bu kadar şaşkın olman benim suçum değil. Hoşça kal!";
			link.l1 = "Evet, benim hatam. Elveda, umarım bir daha karşılaşmayız, bana hep uğursuzluk getiriyorsun.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Sonunda! Beklemekten yorulduk, şu lanet sivrisinekler de... Dur... Solly nerede? Anlamıyorum...";
			link.l1 = "Solly buraya gelmez. Onun adına ben konuşuyorum... Yani ya altını verirsin ya da ölü sayılırsın.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Göreceğiz! Bana gelin, çocuklar! Silah başına!";
			link.l1 = "Böyle aptalca bir şekilde ölmek... Hadi gelin, leşçiler!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Anlaşmamızın senin kısmını yerine getirdin, kaptan. Bana güvendiğin için teşekkür ederim. Adam için endişelenme, onu olması gereken yere götüreceğim. Hak ettiğini bulacak.";
			link.l1 = "Adam umurumda değil. Peki ya o gemiyle ilgili verdiğin söz ne olacak?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Evet, evet, tabii. Bakalım, bugünden sayarsak... Evet... 12-14 gün sonra "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" Avrupa'ya doğru yola çıkacak olan ağır bir kalyon altın cevheriyle dolu olacak. Ona sadece bir fırkateyn ya da korvet eşlik edecek\nYani kendini hazırla, bu büyük bir ganimet ama kolay lokma değil. Yine de, eminim başaracaksın; sonuçta beni de pek zorlanmadan alt ettin... Ulaşman gereken yer "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" iki hafta sonra pusu kuracağız\nUnutma, hedefin tek bir konvoy gemisiyle birlikte ağır bir kalyon. Sanırım bu kadar. Gerisi artık senin elinde.";
			link.l1 = "Anladım... Peki, "+pchar.questTemp.FalseTrace.CapName+", elveda. Belki de sana şans ve Katerine'yle mutlu bir hayat dilemeliyim? Umarım ikiniz de iyi olursunuz. Böyle üzücü bir durumda tanışmamız gerçekten yazık.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Teşekkür ederim, kaptan. Daha önce de söylediğim gibi, sizde belli bir asalet var. Umarım bir gün dürüst davranışların, onursuz olanlardan daha fazla kazanç getirdiğini anlarsınız. Kendinizi ulusunuza hizmet etmeye adayın, o zaman büyük bir deniz subayı olacaksınız.";
			link.l1 = "Sözlerinizi düşüneceğim. Peki, şimdilik hoşça kalın!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
