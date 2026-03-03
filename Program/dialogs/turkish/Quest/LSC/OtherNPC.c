// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "Hey, hey, bakın hele, kim gelmiş bizi ziyarete! Milletin sandıklarını soyan bir hırsız! Buraya gel! Ve sen, dostum, aptal numarası yapmaya ya da kılıcını çekmeye kalkışma bile – bu kadar yakından asla ıskalamam... Chad seni gördüğüne çok sevinecek!";
			link.l1 = "Ama ben... Daha yeni geldim!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "Doğru söylüyorsun, ha-ha! Kendini tam bir belanın içine attın, dostum... Ve bundan kurtulamayacaksın. Şimdi, silahlarını teslim et ve peşimden gel! 'Tartarus'taki kafes seni uzun zamandır bekliyordu, hırsız!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "Buradan hiçbir şey çalmaya kalkma. Seni gözüm üzerinde tutacağım.";
			link.l1 = "Her zaman bekleriz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "Git ve Chad'in söylediğini yap. Fazla konuşma!";
			link.l1 = "Evet, gidiyorum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "Hey! Ne halt ediyorsun orada? Kahrolası! Şimdi işin bitti!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "Hey, burada ne halt ediyorsun, Allah kahretsin? Barbier nerede?";
			link.l1 = "Bizim dostumuz Adolfo... iyi değil. Toplantıya gelemedi, bu yüzden kabininde biraz oturup seni beklememi istedi.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "Hey, burada ne halt ediyorsun, Allah kahretsin?";
			link.l1 = "Bizim dostumuz Adolfo... iyi değil. Toplantıya gelemedi, bu yüzden onun yerine benim gelmemi istedi. Öyle diyelim.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "Kulağa garip geliyor... Bu sabah iyiydi, şimdi ise hasta.";
			link.l1 = "Bilirsin, bazen her şey bir anda olur. Aniden bastıran bir ateş...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "Ah, senin suratını hiç beğenmedim. Yalan söylüyorsun. Barbier böyle bir buluşmayı asla başkasına emanet etmezdi. Konuş bakalım, herif, kimsin sen ve ona ne yaptın?";
			link.l1 = "Biliyor musun, senin de öyle bakılacak bir halin yok. Zaten söyledim, Barbier hasta. Anlamıyor musun, yoksa tekrar mı etmem gerekiyor? Sana anahtarı vermesi gerekiyordu ve...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "Kahretsin! Beni bulmayı başardın...";
			link.l1 = "Evet, pislik! Ona dokunamayacaksın! Ölümüne hazırlan!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "Sen misin "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Sorun nedir?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "Köpekbalığı beni gönderdi. Sizi en kısa zamanda görmek istiyor. Sizin için önemli bir şeyi var.";
			link.l1 = "Acelen ne?.. Peki, hemen 'San Agustin'e gidiyorum.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "Sen misin "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Sorun nedir?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "Ah, seni aramaktan yoruldum... Köpekbalığı ve Layton Dexter. Hemen seni görmek istiyorlar. Çok önemli bir mesele, acele et.";
				link.l1 = "Öyle mi? Pekâlâ, hemen 'San Agustin'e gidiyorum.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "Ah, seni aramaktan yoruldum... Amiral Layton Dexter seni hemen görmek istiyor. Çok önemli bir mesele, acele et.";
				link.l1 = "Amiral?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "Evet. İkinci kaptan olarak, Köpekbalığı'nın ölümünden sonra amiralimiz oldu.";
			link.l1 = "Anladım. Peki, hemen 'San Agustin'e gidiyorum.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, işte buradasın... Seni hatırlıyorum, Chimiset ile en son konuşan sendin. Onu öldürdün mü?";
				link.l1 = "Saçmalamayı kes! Bunun ben olmadığını gayet iyi biliyorsun. Katilin kim olduğunu da bildiğini düşünüyorum.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Eh, burada bütün gün kalmak çok sıkıcı! Keşke rom ve iskambil getirseydin dostum, belki biraz kumar oynardık...";
				link.l1 = "Üzgünüm dostum, bunun için vaktim yok. Belki sonra.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "Birkaç tahminim var, evet, ama elimde hiçbir kesin bilgi yok. Siyah adamın ölümünü kimse görmedi. Adanın her yerinde dedikodular dolaşıyor; diyorlar ki, biz, Köpekbalığı'nın adamları, sorumluyuz ve bir de, bu işi amiralin emriyle bir yabancının yaptığı söyleniyor. Anlıyor musun şimdi? O yüzden Rivados'a gitme, hele ki şimdi hiç gitme. Çok öfkeliler.";
			link.l1 = "Pekâlâ. Anladım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "Eh, burada bütün gün kalmak çok sıkıcı! Keşke yanında rom ve iskambil getirseydin dostum, belki biraz kumar oynardık...";
			link.l1 = "Üzgünüm dostum, bunun için vaktim yok. Belki sonra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "Ne istiyorsun, dostum?";
			link.l1 = "Hm. Peki, burada ne işin var? Axel nerede?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "Axel meşgul. Donald Greenspen ile bir toplantısı var ve gün sonuna kadar onunla olacak. Yani bir şey almak istiyorsan, onunla yarın sabah konuş. Ben de dükkana göz kulak oluyorum, o yüzden bir şey çalmaya kalkma...";
			link.l1 = "Anladım. Peki, neden bunu bugün yapıyor? Peki, yarın sabah buraya gelirim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("Sana zaten her şeyi anlattım. Yarın tekrar gel.","Beni rahatsız etme, dostum. Kaybol!","Beni kızdırma, seni ahmak!","Defol!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Pekala.","Anladım, anladım.","Sus...","Ne?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "Ne istiyorsun, efendi?";
			link.l1 = "Hm... Üzgünüm, hanımefendi. Küstahlığım ve kaba davranışım için beni affedin, ama size bir şey sormak istiyorum: Ole Christiansen adında bir adamı tanıyor musunuz?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "Az önce söylediğini tekrar et... Ole Christiansen mi? Ole?!";
			link.l1 = "Evet. Saçının alışılmadık rengi yüzünden ona Beyaz Çocuk da derler. Onu tanıyor musun?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "Onu tanıyor muyum?! O benim oğlum ve on yıldır kayıp! Nerede olduğunu biliyor musun, efendim? Söylesene bana, nerede, ona ne oldu?!";
			link.l1 = "Sakin olun, hanımefendi, bu kadar endişelenmeyin. O iyi. Gemimde. Tek yapması gereken karaya çıkıp buraya gelmek.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "Oh... Görünen o ki, Tanrı sonunda dualarımı duydu! Kaybolduğunda ne kadar endişelendiğimi hayal bile edemezsiniz! Hem de bu tamamen benim suçumdu! Nerede buldunuz onu? O sıradan bir çocuk değil... yani, ne demek istediğimi anlamışsınızdır.";
			link.l1 = "Evet, öyle. O gerçekten özel biri. Ve hiç değişmemiş. Hâlâ bir çocuk gibi sanki. Onu bir adada buldum. Tesadüfen karşılaştık. Benden beyaz bir boncuk istedi... kahretsin!... Bir inci.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "Bir inci mi? Aman Tanrım! O inciler yüzünden oğlum kayboldu! Hepsi o lanet kolyenin suçu!";
			link.l1 = "Ole'nin... incili kolyeni kırdığı için evini terk ettiği doğru mu?... Sakin ol, hanımefendi, ağlama!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "Evet, doğru. Ole iskelede kolyemi kopardı ve bütün inciler suya düştü. Ona öyle çok sövdüm ki, rahmetli kocam... onu cezalandırdı. Ertesi gün Ole ortadan kayboldu. Bunun için kendimi ne kadar suçladığımı hayal bile edemezsin!";
			link.l1 = "Ole yıllardır inci topluyor. Onlara beyaz boncuklar diyor. Hepsini senin için biriktirmiş ve beni sana getirmemi istedi. Kırmızı çatılı bir evden başka hiçbir detayım yoktu. Ama sonunda seni bulmayı başardım.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "İnci toplamak mı?! Aman Tanrım! Zavallı oğluma karşı kendimi çok suçlu hissediyorum! Ben... ve o inci topluyormuş! Ah!";
			link.l1 = "Sizi oğlunuza çağırmam iyi olur hanımefendi. Sizi görmek için sabırsızlanıyordu. İncileri görünce mutlu olacağınızı söyledi. Ama bence siz, onların yüzünden değil, başka bir sebepten mutlu olacaksınız...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "Mynheer... lütfen bana bir iyilik yapar mısınız. Ole’mi bana getirin. Ona sarılmak ve affını dilemek istiyorum...";
			link.l1 = "Elbette, hanımefendi. Hemen onu buraya getirecekler.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "Pekala hanımefendi, işte oğlunuz - Ole Christiansen. Onu tanıyor musunuz?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "Beyefendi... Affedersiniz, adınızı sormadım... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", hanımefendi. Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "Kaptan, oğlum için ne kadar minnettar olduğumu hayal bile edemezsiniz! Ona yardım ettiniz ve buraya getirdiniz. Sayenizde yeniden yaşama sevincim oldu! Oğlum için her şeyi yaparım, yıllarca eksik kaldığı sevgimin hepsini ona vereceğim.";
			link.l1 = "Sizin adınıza sevindim hanımefendi. Ole için de öyle. O iyi bir çocuktur ve zor bir durumda bana yardım etti. Yüreği temizdir. Ole'nin ölümden kurtardığı bir adamı tanıyorum.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "Beyefendi, yarın ya da ne zaman vaktiniz olursa mutlaka buraya gelmenizi rica ediyorum. Oğlum için size teşekkür etmek istiyorum. Şu anda sadece biraz... yani, anlıyorsunuz.";
			link.l1 = "Evet, hanımefendi.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "Yarın buraya tekrar gel. Oğluma ve bana yaptığın tüm iyilikler için seni hakkıyla ödüllendireceğim.";
			link.l1 = "Pekâlâ. Kesinlikle seni ziyaret edeceğim!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "Ah, işte buradasınız, efendim "+GetFullName(pchar)+"! Gel, otur bir yere...";
			link.l1 = "Teşekkürler! Ole nasıl?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "Ah, ne yaptığını hayal bile edemezsin! Yorgun bir annenin yüreğine ilaç gibi geldin... Sana borçlandım, ve sonsuza dek senin için dua edeceğim.";
			link.l1 = "Beni utandırıyorsunuz, hanımefendi...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "Asaletli insanları asaletli yapanın alçakgönüllülük olduğunu her zaman bilirdim... Yaptıkların için hediyeler hazırladım. Evet, evet! Sakın reddetmeye kalkma! Al, bunu al... İlk olarak, içi doblon dolu bir sandık var. İkincisi, bu büyülü muskayı al, ona Scarab diyorlar.\nKocamındı, eminim ki hazinesinin oğlumu bana geri getiren böylesine asil bir kaptana ait olacağını bilse çok sevinirdi. Kocam marangozdu, Scarab'ın işini hızlandırdığını söylerdi.\nUmarım bu yüzük sana iyi hizmet eder. Onu takmayı kesinlikle hak ediyorsun! Ve son olarak, terzilik aletlerimi de al. Çok güzel bir takımdır. Onlarla birçok güzel şey yapabilirsin.";
			link.l1 = "Ah! Bunlar her kaptan için gerçekten değerli hediyeler! Teşekkür ederim, hanımefendi.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "Ve bilmeni isterim ki, evimin kapıları sana her zaman açık. Burada her zaman yiyecek, güzel bir şarap ve arzuladığın başka ne varsa bulabilirsin.";
			link.l1 = "Güzel sözleriniz için teşekkür ederim, hanımefendi. Bu kasabaya tekrar geldiğimde sizi görmekten memnuniyet duyarım.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "Sakın gelmemezlik etme!";
			link.l1 = "Ve şimdi gitmem gerek. Hoşça kal ve bol şans!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "Ah, kaptan "+GetFullName(pchar)+"!   Seni gördüğüme çok sevindim! Gel, otur, sana bir içki getireyim...";
			link.l1 = "Teşekkür ederim! Sadece seni selamlamak ve nasıl olduğunu görmek istemiştim. Senin ve Ole'nin iyi olmasına sevindim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben dalıp gitmişken, hemen sandığımı karıştırmaya kalktın!","Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!";
			link.l1 = "Aptal kız!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
