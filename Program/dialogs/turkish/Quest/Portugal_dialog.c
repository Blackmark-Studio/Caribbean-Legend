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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Hata. Geliştiricilere söyleyin.";
		link.l1 = "Tabii.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Ah, bir cesur denizci daha! Sizin gibileri iyi bilirim, lanet olası gözüm hep üzerinizde, ha! Sor bakalım neden?";
			link.l1 = "Sana başka bir konuda bir şey soracağım, bu yerel... hmm, mekânın sahibine olan borcunla ilgili. O, bana borcunu hatırlatmamı istedi, bence bir an önce bir şeyler yapmalısın, yoksa yarın aynı şeyi muhafızlardan istemek zorunda kalacak.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Yerel est... ah, kahretsin! Johanna, bana bunu yapamaz! Emin misin? Gerçekten birkaç lanet sikke için beni zindana göndereceğini mi söyledi?";
			link.l1 = "Kesinlikle. O aynen böyle söyledi. Sanırım görevim sona erdi, hoşça kalın, bay Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Bekle! Lütfen, bekle! Tecrübeli bir kaptana benziyorsun. Eminim birkaç altının vardır, ben ise beş parasızım, sadece eski dostluğumuz hatrına iyi kalpli barmen bana veresiye içki veriyor. Dinle, bir teklifim var... borcumu ödersen sana da pay veririm\nBir iş var... hem de çok kârlı bir iş, lanet olsun bana ve şu arkamdan! Kanlı çapam üzerine yemin ederim, bana güven kaptan - adın her neyse!\nSadece küçük bir borcu kapat, on bin peso, ve Karayipler'deki bütün genelevleri satın alacak kadar para kazanma şansın olur! Ne dersin? Sen bana, ben sana, dürüst insanlar gibi...";
			link.l1 = " Hazine vaat eden perişan bir adamsın. Beni bu saçmalıklarla uğraştırma, senin gibi insanlar için hayır işi yapmam. Parayı bul yoksa yakında kalenin zindanlarında kalırsın. Hoşça kal!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Bir pay mı? Ve neden sarhoş bir aptalın sözüne güveneyim? Hayali vaatler yüzünden mi?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Dinle beni, kaptan! Hık, yalan söylüyorsam vur beni gebert! Ama doğruyu söylüyorum! Bir düşün, eğer yalan söylediğimi yakalarsan, kemerinde taşıdığın o güzellikle bağırsaklarımı deşebilirsin! Kahretsin, onun kabzası benim zavallı borcumdan beş kat daha değerli! Ne dersin? Kaybedecek hiçbir şeyin yok!";
			link.l1 = "Senin nutuklarından bıktım. Elveda.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Peki, Hugo... O saçmalıklarına inanmayı göze alacağım. Ama unutma, döndüğümde paramın boşa gitmediğine beni ikna etmen gerekecek, yoksa başın belada olur.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Tehdit etmene gerek yok, anladım. Sana söz veriyorum, kaptan! Zengin olacağız! Şu lanet borç ödendiğinde geri gel, o zaman... konuşuruz! Evet, konuşuruz! Seni dışarıda bırakmayacağım!";
			link.l1 = "Pekâlâ, borcunu sileceğim, ama dua et, Hugo Avendell, teklifin beni memnun etsin.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Kaptan, elinden geldiğince çabuk dön - bu iş elimizden kaçabilir.";
			link.l1 = "Evet, evet, borcunu yakında ödeyeceğim.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Geri döndünüz, kaptan! Fırtına ve lanet olası gök gürültüsü adına, sizi gördüğüme öyle sevindim ki! Peki ya borcum ne olacak?";
			link.l1 = "Ben işimi hallettim, şimdi sıra sende Hugo. Hikayeni anlat bakalım, ama en azından biraz inandırıcı olsun!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Endişelenme, kaptan! Bir ödül avcısı olduğumu biliyor muydun? Ya da... eskiden öyleydim. Sanırım yeterince şanslı değildim. Belki de şeytanın kendisi bile, tüm yaptıklarına rağmen, benim kadar kaybeden olmamıştır. Son işimde her şeyimi kaybettim... Mürettebatım beni terk etti ve borçlarım yüzünden gemimi satmak zorunda kaldım...";
			link.l1 = "Kahramanca geçmişinden zaten haberdarım. Lafı dolandırmadan konuya gel, Hugo, sabrımı sınama.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Evet, evet, kaptan..."+GetFullName(pchar)+", değil mi? Ben de senin hakkında bir şeyler biliyorum. Ama önemliyse, kahretsin beni. Bartolomeo the Portuguese adını duydun mu?";
			link.l1 = "Bart Portekizli mi? Elbette ondan haberim var. Herkesin var. Bildiğim kadarıyla o bir korsan, bir cellat ve tam bir pisliktir. Peki, senin hikayende onun rolü ne?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "O işin tam ortasında! Son bir buçuk yıldır onun peşindeyim. Hollanda Şirketi onun başına yüklü bir ödül koydu. Ama başaramadım, her şeyimi kaybettim. Ve Şirket son zamanlarda onun için ödülü üç katına çıkardı—hem de sadece canlı olarak, kahretsin!";
			link.l1 = "Boşuna değil, onu canlı yakalamak hiç de kolay bir iş değil. Hem, bana ne bundan, Hugo? Beni kandırmaya mı çalışıyorsun yoksa!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Ben zaten yapmayacaktım, kaptan! Biliyor musunuz, buranın doktoru Peter Van Stal, çok iyi bir adamdır, bana baş ağrılarım için bir iksir verdi! Ama doktor neredeyse üç gündür evinde yoktu ve...";
			link.l1 = "Hugo, sabrım neredeyse tükendi! Hanımefendiye seni kılıcımla delmeyeceğime söz verdim, ama yumruklarım da iş görür! Yemin ederim, yarın kafanı hiçbir iksir iyileştiremeyecek!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Bekleyin, kaptan! Lütfen! Beni dinleyin, doktorun evinin yakınında birkaç adam gördüm ve onları tanıdım. Onlar 'Albatross' adlı, lanet olası Portekizlilere ait bir firkateynden! Ve içlerinden biri kaptanlarının sağlığından bahsediyordu! Bakın şimdi, "+pchar.name+", Bartolomeo burada, bu şehirde! Burnumuzun dibinde, ya yaralı ya da hasta, bu yüzden lanet bir doktora ihtiyaçları varmış!\nPortekizlinin tüm tayfasını buraya getirdiğinden şüpheliyim, ama bu belayı tek başıma başlatamam! Senin o lanetli kılıcı nasıl kullanacağını gayet iyi bildiğini biliyorum! Yanına birkaç sağlam adam al, şu sıçanı bulalım! Sonra onu yakalayıp yetkililere teslim ederiz!\nVe iki bin altın dublon cebimize girecek!";
			link.l1 = "Hayır, Hugo, artık senin laflarını dinlemek istemiyorum. Haklı olsan bile bu karmaşaya karışmayacağım. Elveda.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, ilginç. Nerede saklandığını biliyor musun? Eğer işimiz yolunda giderse payları konuşuruz, ama bana anlattıkların doğruysa şimdi acele etmeliyiz!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Hayır, kaptan, onun nerede olduğunu bilmiyorum. O heriflerin peşine düşmeye korktum. Tek Göz beni görseydi... tüh! Ama beraber, senin adamlarınla, bu kasabanın altını üstüne getirebiliriz, adamlarını çağır da başlayalım! Lanet olsun, Hollanda dublonları bizi bekliyor! Böyle bir fırsat insanın hayatında bir kez çıkar, hadi bakalım!";
			link.l1 = "Takdire şayan bir heves... Umarım masadan kalkmayı başarabilirsin, 'büyük' ödül avcısı. Ben hemen aramaya başlıyorum, istersen peşimden gelebilirsin—yeter ki fazla ayağıma dolanma.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Evet, evet, kaptan, bırak içkimi bitireyim de sana katılayım... Nereden başlayalım?";
			link.l1 = "Nerede?!... Ben gidiyorum, sen olsan da olmasan da.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Yanlış eve geldin, dostum. Şimdi kaybol!";
			link.l1 = "Hm. Sanırım doğru ev burası...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Ben seni uyarmıştım...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Tam yol ileri, yelkenler fora, oğullarım... topları hazırlayın!... ah-ha-ha... ah, güzelliğim...";
			link.l1 = "Hmm, hayatta kaldığına şanslı...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Tanrım, kimsiniz siz? Lütfen silahınızı indirin! Burada hasta bir adam var!";
			link.l1 = "Senin şu 'hasta adam'ın, doktor, senin hayatında gördüğünden daha fazla insan öldürdü. Uzak dur!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "O benim hastam ve ayakta duracak hali yok! Bunu görmüyor musun? Lütfen, kılıcını indir! Sana yalvarıyorum!";
			link.l1 = "Ve ona ne olmuş, kahretsin!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Sanırım her şey onun yarasından kaynaklanıyor, zehirli bir Karib silahıyla aldığı bir darbe... Ve onu buraya getiren adamlar, eğer o ölürse benim de öleceğimi söylediler! Ama elimden gelen her şeyi yapıyorum, onlara bunu söyleyin!";
			link.l1 = "Bu adamlardan endişelenme, doktor. Adamlarım evini gözetecek, ben de valiyi görmeye gitmeliyim. Sanırım sevinçten altına edecek. Ben dönene kadar buradan ayrılma, doktor.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Gitmeyeceğim, merak etme. Hadi onu yetkililere teslim edelim de bu kabus artık sona ersin.";
			link.l1 = "Elbette, geliyorum.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Başardık, kaptan! Onu bulduk ve yakında zengin olacağız, sana dememiş miydim! Şimdi ne yapıyoruz?";
			link.l1 = "Umarım öyledir, Hugo. Her neyse, işimiz henüz bitmedi. Sanırım valiye gidip ödülümüzü konuşmam gerekecek?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Hayır, hayır kaptan! O lanet Thomas'a gitmeyin! Bana güvenin, bu alçak mahkumumuzu elimizden alacak ve şansımız yaver giderse bize bir fincan kahve ısmarlayacak! Ekselansları kaypak biridir, tam ödülü almak istiyorsanız Curaçao'ya gitmelisiniz! Yoksa Portekizliyi kaleye götürürler ve bizi de dilenci gibi kovarlar!";
			link.l1 = "Eğer bundan gerçekten eminsen...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Eminim kaptan, lanet olsun ki eminim! Ama unutma, Bartolomeo'nun adamları da kasabada bir yerde olmalı ve garnizonun dikkatini de çekmek istemeyiz, bu kesin! Portekizliyi gemine nasıl götüreceğimizi ve bunu kimseye fark ettirmeden nasıl yapacağımızı kararlaştırmalıyız.";
			link.l1 = "Pekala... Willemstad'a giderken onun fırkateyniyle kapışmak istemiyorum. Bir fikrin var mı?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Evet, bir fikrim var. Önce ona daha asil bir kıyafet bulmamız lazım, sonra da onu arka kapıdan sarhoş bir subay gibi içeri sokarız! Kimse onun lanet bir korsan olduğundan şüphelenmez, bana güven!";
			link.l1 = "Hmm, bundan pek emin değilim, ama elimizde daha iyi bir plan da yok. Yolcumuz için biraz kaliteli kumaş bulmaya çalışacağım. Sen burada kalıp Bart ve doktoru gözle.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Endişelenme, kaptan. Portekizli benim güvenli gözetimimde, he-he...";
			link.l1 = "Buna inanmak isterdim...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Askerleri göremiyorum, "+GetAddress_Form(NPChar)+". Nerede onlar? Durumu onlara anlattığında hemen tutuklanacağını söylemiştin. O halde neden askerler burada değil?";
			link.l1 = "Asker olmayacak, mynheer Van Stal. Bu işi kendim halledeceğim ve hastanızı en kısa sürede Curaçao'ya götürmem gerekiyor.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Kaptan, dinleyin, onun yarasını tedavi edemem, sadece ateşini biraz düşürebilirim. Çoğunlukla baygın ve sayıklıyor, müdahale olmasa bile öleceğinden şüphem yok, denizin sallantısı da onu birkaç gün içinde öldürecek. Size yardımcı olacak bazı karışımlar vereceğim...";
			link.l1 = "Hayır, doktor, bizimle geliyorsun. Birincisi, tıptan hiç anlamam, ikincisi de, kaptanlarının nereye kaybolduğunu Portekizlilere açıklamak isteyeceğini sanmıyorum, değil mi?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Evet, sanırım haklısınız. Ama bilin ki bu korsan gerçekten dayanıklıdır. Hintlilerin silahlarından sadece hafif yaralar almış insanları gördüm, hepsi üç günden az bir sürede öldü. Ve 'arkadaşlarının' dediğine göre, o bu halde zaten bir haftadır! Yine de, açık denizde bir gemide ancak kısa bir süre hayatta kalabileceğini düşünüyorum. Üç gün, daha fazla değil!\nElimizdeki zaman bu kadar.";
			link.l1 = "Bir kuş bile üç günde Curaçao'ya ulaşamazdı. Ama sanırım ne yapabileceğimi biliyorum! Antigua, St. John's'ta yaşayan bir... arkadaşım var. Ölümcül yaraları iyileştirmeyi bilir. Şu anda bize yardım edebilecek tek kişi o. Hedefimiz basit - Portekizli ölmeden oraya ulaşmak. Eşyalarını topla, doktor, hemen yola çıkıyoruz ve hastan da ardından getirilecek!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Ne yazık kaptan. Kaybettik ve o lanet altını göremeyeceğiz. Elveda.";
			link.l1 = "Elveda, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doktor, hastanı karaya çıkmaya hazırla. Sandal hazır. Acele et!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Yoldayım, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "This house stinks of bloody mixtures! It would be a real surprise if the Portuguese died here; even breathing this smell could cure any disease!\nAnd the man's crew could easily find us thanks to the stench!";
			link.l1 = "Hugo, spare me your jokes. I have left a few men on the streets to watch over the house, but one more guard won't be unnecessary for our guest. Keep an eye on him and try to stop the swearing, or Gino will make you drink some mixture of his; I am sure he can cure that.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Don't worry, captain! I will watch over our money most vigilantly; he wouldn't escape even if he were healthy! And I beg you, please, no more mixtures!";
			link.l1 = "Bak, istediğinde nazik olabiliyorsun. Dikkatli ol, gitmem gerek.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Şimdiden gidiyor musunuz, kaptan? Güzel! Zamanı geldi! Sokakta birkaç şüphe... şüpheli adam gördüm. Portekizli gibi görünmüyorlardı, ama bir şey arıyorlardı. Dikkatli olmalıyız, kaptan!";
			link.l1 = "Pekala, uyarın için teşekkürler Hugo. Hadi gemiye gidelim.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Kaptan, bu buluşmayı çok uzun zamandır bekliyorduk! Peki yanınızdaki kim? Portekizli Bartolomeo'nun ta kendisi, ha, Demek Cesur Pierre haklıymış - gerçekten o! Geri dur, kaptan, onu bizimle götürüyoruz ve kimseye zarar gelmeyecek.";
			link.l1 = "Üzgünüm efendim, ama siz de kimsiniz? Çekilin yolumdan, yoksa hiçbiriniz yarını göremeyecek!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, such a menacing fellow, just look at him, lads! Ha-ha-ha! Listen here, pup, don't stand between Leo Cord and his money! We've been tracking down the Portuguese for almost half a year, and now we've finally got him. So put down that toothpick of yours and get lost while you're still breathing! We're not that greedy; a dead man will do just fine, ha-ha!";
			link.l1 = "Yeter. Hadi dans edelim, beyler!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Burada bir terslik olduğunu biliyordum! Aferin kaptan! Ama artık gitme zamanı, o lanet Leo Cord'un burada bir sürü haydudu ve iyi bir gemisi var! Bu adadan uzaklaşmalıyız!";
				link.l1 = "İyi söyledin Hugo, ve saklandığın deliğe hiçbir kurşun isabet etmediğine gerçekten çok sevindim.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Ne yazık kaptan. Kaybettik ve o lanet altını göremeyeceğiz. Elveda.";
				link.l1 = "Elveda, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Ben... Ben arkamızı kolluyordum, kaptan! Siz bensiz de gayet iyi idiniz, ama ya biri sokağın öbür tarafından saldırsa ne olacaktı? Gemiye koşacak vaktiniz olmazdı.";
			link.l1 = "Belki de bu yüzden işinde başarılı olamadın? Neyse, artık konuşmayı bırak, gemiye gitmemiz lazım! Zaman daralıyor!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Kaptan, Portekizli kendini çok kötü hissediyor, durmamız lazım!";
			link.l1 = "Bu yüzden buradayız, Bay van Stal, yolculuğumuz neredeyse bitti. Hanede bir oda kiralayacağım ve tutsağımız birkaç gün orada kalacak.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer kaptan, Portekizliyi ben gözeteceğim, onun tam dinlenmeye ihtiyacı var.";
			link.l1 = "Anladım, doktor, sorun yok. Kahretsin, bu korsana daha ne kadar bakmam gerekiyor? Bu ona iyi gelmiyor, ihtiyacı olan bu değil! Sanki beni bakıcı olarak tuttular ve... ah, affedin doktor, bu gerçekten fazla geliyor... Sonra görüşürüz.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Beyefendi, siz kaptan mısınız "+GetFullName(pchar)+", gemisi bugün limanımıza yeni yanaşan kişi mi?";
			link.l1 = "Doğru söylüyorsunuz, size nasıl yardımcı olabilirim?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Kolonimizin valisi Ekselansları Jacques Dille du Parquet sizi bekliyor. Mesele acil!";
			link.l1 = "Pekala, monsieur, bugün Ekselanslarını ziyaret edeceğim.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Martinique'e vardık, kaptan! Paramız artık çok yakın...";
			link.l1 = "Portekizliler Willemstad'a varana kadar hayatta kalırsa. Hugo, gemiye gitmem lazım, bu yüzden doktorla hastasına sen göz kulak olacaksın.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Gemiye mi gideceksin? Neden? Bana yardım etmesi için birkaç adamını ödünç verecek misin? Ya sen yokken bir şey olursa?";
			link.l1 = "Üzgünüm, ama hayır. Burada sana bir şeyin tehdit oluşturabileceğinden şüpheliyim. Garnizon tetikte ve sokaklarda her zamankinden daha fazla asker var, bu yüzden bir şey ters giderse onları çağır. Bu adadan çok uzakta olmayan büyük bir gemi gördüler, belki de bir korsan gemisi. Ve Ekselansları Vali, adayı gemimle devriye gezerek güçlendirmemi istedi.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Bir gemi mi? Korsan mı? Belki Albatros’tur! Ya da eski dostumuz Leo Cord’un bir meslektaşı!";
			link.l1 = "Ya da belki de bu sadece sıradan bir korsan gemisidir. Yine de Hugo, eğer bu gemi bizim başımız için buradaysa, yanında yerel devriye ve vali adına altınla karşılamak en iyisi olur. Yolun geri kalanında arkamızı kollamaktan çok daha iyi. Ama bu alarm asılsız çıkarsa, birkaç gün meyhanede boş boş oturmaktan kurtulmuş olurum.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Bir düşün kaptan, barajı... Portekizliyi korumasız bırakmak akıllıca mı, onun fırkateyni hâlâ buralarda dolaşırken? Valinin ücretini kabul ederek ödülümüzü riske atıyorsun!";
			link.l1 = "Yeter artık konuştuğun, Hugo Avendell! Burada kaptan benim ve son karar bana ait! O yüzden dediğimi yap. Meyhaneye git ve ben dönene kadar doktorla Portekizliyi gözle.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Sonunda döndünüz, kaptan! Korkarım size kötü bir haberim var – Portekizli gitti, doktor da yanında!";
			link.l1 = "Nasıl yani?! Peki o sırada sen ne yapıyordun, ahmak?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Bahse girerim o gemi 'Albatross'tu. Portekizli adamları gördüm, meyhaneye girdiler ve ben... kaçtım. Üzgünüm, ama Tek Gözlü Köpek'le karşılaşmak, o kadar para için bile fazlaydı!";
			link.l1 = "Lanet olsun! Bari bana tavernada ne olduğunu anlatır mısın?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Sana hiçbir şey görmediğimi söyledim. Franz Garcke ve adamlarını görünce hemen mutfaktan kaçtım... Çok yakındı! Dün akşam oldu, sana nasıl haber vereceğimi bilemedim...";
			link.l1 = "Yes, you are a very brave and resourceful man... Fine, let's give you one more chance, we are going to find them. I have been saving this scoundrel for too long and now I consider him my property. We still have some time to catch them, so let's start from the tavern; perhaps someone has seen more than your fleeing heels. Go, prepare yourself!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Duymuş muydunuz kaptan, az önce Tek Gözlü Köpek’ten bahsediyordu, size ondan yakın zamanda söz etmiştim. Ve peltek Kastilyalı Hernando Vasquez, o kanlı Don – Vera Cruz’un celladı, onu görmedim!";
			link.l1 = "Relax, Hugo. I am sure that Bartholomeo is still on the island; he might be feeling better, but he is still too weak. And I think I know where to find him! We will get them, I won't walk away from my reward. If you are no coward, then follow me – it is not over yet.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Çok fazla soru soruyorsun, kaptan... Dur bakayım, sen Philipsburg'dan o sinsi adam değil misin? Bize çok uzun zamandır kaçıyordun ve şimdi bak - işte buradasın...";
			link.l1 = "Sana yazıklar olsun, pislik!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... seni sefil yengeç pisliği, bize her şeyi anlatacaksın, bana güvenebilirsin, seni lanet sıçan! Sonra da seren yerine direğe asılacaksın... Ve sen de kimsin be? Kahretsin, şu maymunlara güven olmuyor! Her şeyi yine kendim yapmak zorundayım...";
			link.l1 = "Sizi rahatsız mı ediyorum, beyler?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Zamanlaman hoşuma gitti... Sanırım bugüne kadar hayatta kalmamı sağladığın için sana teşekkür etmeliyim, değil mi?";
			link.l1 = "Doğru söylüyorsun. Benim adım "+GetFullName(pchar)+" ve sen, Portekizli, hâlâ benim tutsağımsın. O yüzden bana soru sorma, gitmemiz gerek.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Bekle, kaptan... Kasabada Vasquez'in adamları çok, bizi öylece bırakmazlar. Bana bir kılıç ver, o zaman şansımız çok daha iyi olur.";
			link.l1 = "Ortaklarınla aranız pek iyi değil galiba, ha? Peki, fazladan bir kılıca her zaman yer var. Cesedin silahını al ve yanıma yaklaş!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Sırtımı döndüğüm anda bana saldırman için sana silah vereceğimi sakın düşünme! Sadece yanı başımda dur.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Endişelenme kaptan, Vasquez'in eline tekrar düşmektense ölmeyi tercih ederim.";
			link.l1 = "Bak, mesele şu ki, seni henüz öldürmek istemiyorum. Hadi, zaman daralıyor!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Ne yazık ki, seni öldürmek isteseydim, Tek Gözlü'ye yardım ederdim...";
			link.l1 = "Ama sen de bana yardım etmedin, o yüzden sus ve yürü!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Lanet olsun! Onlar işte! Hepsini öldürün!";
			link.l1 = "Yine başlıyoruz... Hadi bakalım, pis köpekler!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Harika! Tek Gözlü Köpek'i öldürdün, buna şaheser derim! Adamlarından kaç tanesini cehenneme yolladın?";
				link.l1 = "Savaşıyordum, saymıyordum.   Peki sen neredeydin, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Ne yazık kaptan. Kaybettik ve o lanet altını göremeyeceğiz. Elveda.";
				link.l1 = "Elveda, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Ben... güvenli bir geri çekilme sağlıyordum... arkamızı koruyordum, tabiri caizse.";
			link.l1 = "Pekâlâ, işte bu kadar Hugo Avendell, korkaklığın tüm beklentilerimi aştı. O dövüşün bizim için ne kadar zorlu geçtiğinin farkında mısın? Neredeyse canımızı zor kurtardık!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Sakin ol, kaptan... Kabul ediyorum, saklanıyordum. Ama senin için bu fırsatı buldum! Unutma, seni Portekizlilere götüren bendim! Şey... haklı öfkeni düşününce, ödülün sadece üçte birine razıyım.";
			link.l1 = "Bu gerçekten harika! Şimdi pazarlık mı yapıyorsun? Hayır dostum, bu işteki payın bitti! Paranı Saint-Pierre'deki meyhanede kaybettin. Orada bıraktın ve kaçtın, artık senin için her şey bitti.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Kaptan, açıkça abartıyorsunuz... Peki, çeyreğine razıyım... beşte birine! Yüzde on!";
			link.l1 = "Sabrımı zorlama! Defol git! Mürettebatımda korkaklara yer yok, hele şimdi, zaman daralırken!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", sence bu biraz haksızlık değil mi?";
			link.l1 = "Cause and effect, Hugo... You have made your choice, so farewell. Draw your own conclusions and don't plunge into adventures like that; this is clearly not for you.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Balastı atıyor muyuz, kaptan? Doğru, ha... Vasquez hâlâ serbest ve Albatross'ta hâlâ bir sürü adam ve silah var. Şu güzel pantolonumu eski bir mendile bahse girerim ki Hernando kaçmamıza izin vermeyecek.";
			link.l1 = "Pekâlâ, anlaşılan onu kendimiz karşılamaya gitmemiz gerekecek. Hadi, Bay Portekizli, ve lütfen çeneni tutmaya çalış. En kısa zamanda demir alacağız.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Ne bekliyorsun, kahretsin?!";
			link.l1 = "Hernando Vasquez nerede? Konuş, hayatını bağışlayayım.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Cehenneme git lanet olası sorularınla!";
			link.l1 = "Önce siz...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "Ve işte buradasın, cesur dostum, sonunda düzgün bir sohbet edebileceğiz! Tebrikler kaptan - Tek Gözlü Köpek'i öldürmek ve 'Albatros'u yok etmek hiç de kolay bir iş değildi! Gerçekten de hayatımı kurtarmak için çok şey yaptın... Belki de sana teşekkür etmeliyim?";
				link.l1 = "Bana teşekkür edeceksin, Willemstad'da senin için ne hazırladılarsa, darağacında dans ederken.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "Ve işte buradasın, cesur dostum, sonunda nihayet konuşabiliyoruz! Tebrikler kaptan – Tek Gözlü Köpek'i öldürmek onurlu bir şarkıya değer! Gerçekten de hayatımı kurtarmak için çok şey yaptın... Belki de sana teşekkür etmeliyim?";
				link.l1 = "Bana teşekkür edeceksin, darağacında dans ederken ya da Willemstad'da senin için ne hazırladılarsa artık.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "İnanılmaz! Son iki haftadır hayatımı kurtarıyorsun, beni evine getirdin ve kavgalar sırasında korudun... ve şimdi beni ölüme mi göndereceksin? Buna inanmakta zorlanıyorum... Aslında, artık seni neredeyse arkadaşım olarak görüyorum, ha-ha.";
			link.l1 = "Onura başvuran bir korsan mı? Portekizli, benimle dalga mı geçiyorsun? Seni sadece bir amaç için saklıyordum - katilin ve alçağın adalet önünde hesap vermesi için!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Benim dostum... alay gibi geliyor kulağa. Ama yine de, haklısın. Bunu yapmam tuhaf olurdu, Portekizli...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Ah, yeter artık kaptan. Eminim bütün bunları sadece Şirket'in beni sağ görmenin zevki için vaat ettiği parayı almak için yaptın! Gerçekten olduğundan daha dürüst olmaya çalışma, bayım, sana hiç yakışmıyor.";
			link.l1 = "Yalnızca kendimi ben yargılayabilirim. O yüzden bu konuşmayı burada bitirelim. Artık Willemstad’a yelken açma vakti.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Bu devirde insanlarda hâlâ biraz dürüstlük bulunabiliyor demek ki... Ne yazık ki para her zaman araya giriyor - değil mi, kaptan?";
			link.l1 = "Bunu darağacına layık bir korsandan duymak tuhaf, Portekizli. Seni bırakacağım... nedenini sorma, sadece ilk limanda defolup git. Ve unutma, bir daha karşılaşırsak bu kadar nazik olmayacağım.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Gerçekten mi? Bunu çok isterim, kaptan! Buraya biraz rom getirilmesini emretmez misiniz? Bilirsiniz ya, şövalyece niteliklerinizi, aramızdaki ilişkiyi ve cezamın ertelenmesini kutlamak için.";
			link.l1 = "Kötü şakalar yapma, ilk karaya ulaşana kadar hâlâ benim tutsağımsın. Elveda.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Anladım... demek ki darağacı olacak. Beklenen buydu zaten. Şimdi beni iyi dinle, kaptan. Beni düzgünce idam etmek için bu kadar hayatta tutmaya hevesliydin, bunu takdir ediyorum. Şimdi sana fikrini bir anda değiştirmesini istemek aptallık olurdu, değil mi? Peki, sana bir şey teklif etsem ne dersin? Bir anlaşma, diyelim, hmm?";
			link.l1 = "Hiçbir şey söylemeyeceğim, Portekizli. Sen bir korsan ve alçaksın. Willemstad'da işlediğin suçların hesabını vereceksin.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Bir anlaşma mı? Ne teklif edebilirsin?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Senin teklifine ihtiyacım yok, ilk limanda kaybol. Bugün şanslı günündesin.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Biliyor musun, hayatımı bu kadar ısrarla kurtarman, ardındaki tatsız nedenlere rağmen, yine de bir teşekkürü hak ediyor. Ve Portekizli Bartolomeo, minnettarlık nedir iyi bilir. Şimdi dinle, seninle tanışmamızdan bir ay önce, Şirket'e ait bir gemiyi ele geçirdik. Son adama kadar şeytanlar gibi savaştılar. Ama ambarlarında sadece gülleler ve fareler vardı\nMürettebatım bundan hiç hoşlanmadı, ama ben kaptanın kamarasında çok ilginç bir sandık ve bazı belgeler buldum. Gemi bir kurye gemisiydi, Amazonya'daki madenlerden örnekler taşıyormuş. Saf elmaslar ve yakutlar, tam bir servet!";
			link.l1 = "İlginç bir ganimet... Şimdi Şirket’in neden seninle bu kadar ilgilendiğini anlıyorum, ama hikayenin amacı ne?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "My first mates Vazquez and Franz Garcke had been keeping the crew in order, so I decided to take my chances. I hid the stones from them and burnt the papers. The Dutch had badly damaged our rigging during the boarding, and we had to take the 'Albatross' into a small bay of a small island in the north. I went deeper into the jungle alone while the whole crew were repairing the frigate\nI buried the stones; keeping them aboard was too risky considering the circumstances. My plan was to escape from my beloved crew at the very first port, buy or steal a small boat and sail to the island, collect my prize, and then... farewells to my old life! Europe, a decent mansion, a beautiful wife, you know the rest...";
			link.l1 = "Dur tahmin edeyim, bir şeyler ters gitti.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Her şey ters gitti! Lanet ada, yerli yamyamların yuvası çıktı. Kıyıya döner dönmez saldırdılar. Hemen oradan ayrılmak zorunda kaldık, işte o sırada yaralandım. Sadece bir çizik sandım.\nBirkaç gün sonra ateşler içinde yarı ölü yatıyordum ve görünüşe göre taşlarla ilgili bir şeyler gevelemişim. Franz ve Vazquez adada bir şey sakladığımı anladılar ama tam yerini bilmiyorlardı. Orada dolaşıp durmadan yerliler tarafından vurulma fikri hiç hoşlarına gitmedi. O yüzden o alçaklar beni en yakın limana sürüklediler; çünkü doktorumuz Hollandalılarla çatışmamızda öldürülmüştü, yenisine ihtiyaçları vardı.\nBöylece kendimi o doktorun evinde buldum; beni sadece kısa bir süreliğine ayıltıp işkenceyle taşların yerini öğrenmek istiyorlardı. Sonrasında ise beni parçalara ayırıp sulu etimi yengeçlere yedireceklerine inanıyorum.";
			link.l1 = "Onları yargıladığımı söyleyemem – adamlarını kandırmaya çalışıyordun. O yüzden tekrar soruyorum, bunu bana neden anlatıyorsun?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Bu köpekler insan değildi, bana güven, şimdi hepsi hak ettikleri yerde - cehennemde, ha-ha! Özgürlüğüm ve hayatımın bedeli olarak, sana Hollanda hazinelerinin tam yerini söyleyebilirim.";
			link.l1 = "Hayır Bart, ihanetin beni kötülüğüne tamamen ikna etti. Willemstad ve hak ettiğin ceza seni bekliyor. Anlaşma yok.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Ve gerçekten o mücevherlerin var olduğuna inanmamı mı bekliyorsun? Her neyse, zaten kaybedecek bir şeyim yok... Anlaşma bu hikayenin başlangıcıydı, anlaşma da sonu olacak. Şartlarını kabul ediyorum, Portekizli.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Bunu benim mütevazı teşekkürüm olarak kabul et. Ah, keşke Portekizli Bartolomeo'nun derisinin parlak pesolara ne kadar değdiğini bilseydim, ha! Amacının tamamen çıkar olduğunu anlıyorum, ama yine de, kaptan, her şey için teşekkür ederim, ha-ha\nBurası Turks, kıyılarına yakın ormanlar var. Kuru, eğri bir ağaç bul—orada sadece bir tane var. Sandığı ona yakın bir yere gömdüm. Yani, bir kürek almayı unutma. İyi avlar...";
			link.l1 = "Pekâlâ, bunu aklımda tutacağım, şimdi hemen bir sandala binip gemimden inebilirsin. Elveda.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Son bir şey daha, kaptan. Hâlâ çok sayıda vahşi var, ama endişelenmen gerekenler sadece onlar değil. Vasquez 'Albatross'ta değildi, değil mi? Kanlı Don fazlasıyla kurnaz... onu ya asılı ya da kafasında bir kurşunla görene kadar sırtını koru.";
			link.l1 = "Uyarın için teşekkürler, Portekizli. Şimdi, lütfen gemimden ayrılır mısın artık... sabrımı zorlamaya kalkma.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Ah, bu da kim! Kaptan "+pchar.name+" kendin! Bir içki ister misin?";
			link.l1 = "Biliyor musun, seni tekrar gördüğüme gerçekten sevindim. Ama belki de Martinique'te sana fazla sert davrandım.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Boşver kaptan! Olan oldu... Ama dürüst olmak gerekirse, beni göndermen için sana gerçekten bir sebep verdim... Ama bak, bugün Phillipsburg'da kim misafir, inanamazsın!";
			link.l1 = "Bana bunun   olduğunu   söyleme...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Hayır, hayır, kaptan, Portekizliler değil. Yine yaralı bir herif de değil. Çok daha iyi! Hernando Vasquez... Kanlı Don'un ta kendisi! Son birkaç gündür buranın valisinin misafiriymiş.";
			link.l1 = "Vasquez mi? Valinin misafiri olan mı? Şimdi anladım. Hugo, bana bundan daha fazla bahset, burada neler oluyor böyle?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Pek çok şey biliyorum... ama bu yolculuk sayesinde yine iflas ettim. Belki de bu bilgiye olan ihtiyacın birkaç peso eder, ne dersin?";
			link.l1 = "Hugo, hâlâ bir zorba ve alçaksın! Ne diyeceksen de, eski dostluğumuz hatırına şu 5000 pesosu al.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Nedense, hiç şaşırmadım. Al bakalım, 10.000 peso. Umarım verdiğin bilgi buna değer!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Sana daha iyi bir teklifim var. Mürettebatıma katılmaya ne dersin? Kârlı anlaşmalar yapma ve bulma konusunda yetenekli olduğunu anladım, bu yüzden cesur bir savaşçı rolü yapmaktan yorulduysan - gemimin veznedarı olarak seni aramızda görmekten memnuniyet duyarım.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Hayır kaptan, işler öyle yürümeyecek! O lanet Portekizliyle birlikte büyük bir meblağ kaptın, bundan eminim. Bunu benim payım olarak düşün, bu kadar açgözlü olma. 15.000 sikke ve bir peso bile eksik olmasın!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Al sana cehennem, al onları!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Pekala, derler ki açgözlülük iyidir... Ama bu sana fazla gelmiyor mu, ha?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "İşte bu ödül tam bana göre! ... Bak, Vasquez benimle aynı gemide yolculuk ediyordu, ama ben yolculuk ücretimi ödemek için güverteleri temizlerken, o kamarada dinleniyordu; Allah'tan birbirimizi nadiren gördük ve beni tanımadı. Ama ben bu şeytanı hemen takip etmeye başladım... Ona ilginç bir hikaye denk geldi.";
			link.l1 = "Devam et! O ne yapıyor valinin sarayında?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Çok bir şey bilmiyorum, ama onun gelişinden beri garnizon birkaç gündür tetikteydi ve o devasa savaş gemisi aniden demir alıp büyük bir aceleyle ayrıldı. Sanırım kuzeybatıya doğru yelken açtı. Bütün kasaba dedikodular ve tahminlerle çalkalanıyordu...";
			link.l1 = "Demek karşılaştığım gemi oydu! İlginç... Konudan sapma, Hugo, lütfen hikayene devam et.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Şey, dediğim gibi, gemi gitmişti ve Vasquez valimiz Martin Thomas’ın bir tür misafiri olmuştu. Onu bazen şehirde görüyorum, yanında her zaman birkaç asker oluyor. Onlar koruması mı, yoksa konvoy mu, kim bilir, ha-ha. Ama Don hakkında daha fazlasını ancak konakta olanlar anlatabilir.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Belki de haklısın. Ama bir anlaşmamız vardı, hatırlıyor musun? Kahramanlık yapma, gemime git ve dönmemi bekle. Misafirperver valimizle konuşmayı deneyeceğim.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Eh, bu ilginçti. Bana gerçekten yardımcı oldun, Hugo. Romunu iç, gerisi seni ilgilendirmez.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Ciddi misiniz, kaptan? Size ne oldu? Yüzüme silah doğrultup beni kovdunuz, şimdi ise böyle teklifler mi getiriyorsunuz?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Boşver onu, kendimde değildim ve üzgünüm, sanırım açgözlülük beni ele geçirdi. Al, burada 10.000 peso var, şimdi bana Vasquez hakkında bildiklerini anlat, acelem var.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Belki de o konuda özür dilemeliyim. Dövüşte berbatsın, ama paradan iyi anlıyorsun. Teklifimi yineliyorum, ne dersin?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Ne diyebilirim ki... Kabul edeceğim, ama ancak payımı aldıktan sonra, kaptan. Yüzde on, unutma! O herif için iki bin aldın, yani beni tayfana katmak istiyorsan önce borcunu ödeyeceksin. Yüzde on, tartışma istemem!";
			link.l1 = "Sen tam bir üçkağıtçısın, Hugo. Şu anda yanımda o kadar yok, ama yakında geri döneceğim. Burada kal.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Umarım o iş zekânla beklentilerimi boşa çıkarmazsın, ha! Al payını!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "Karar senin, kaptan. Ben burada biraz kalacağım. Fikrini değiştirirsen geri gel.";
			link.l1 = "Peki, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Fikrini değiştirdin mi, kaptan? O zaman paramı bekleyeceğim.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Al paralarını al, seni alçak, ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Henüz o kadar param yok.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "İyi günler, kaptan. Bir şey mi istiyorsunuz?";
			link.l1 = "Hayır, hayır, sadece bekliyorum. Bay Thomas ne zaman müsait olacak? Bir görüşme için bekliyorum... evet. Söylesenize, Ekselansları gerçekten ünlü korsan Hernando Vasquez'i dostu olarak mı görüyor?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Endişelenmeyin efendim, her an serbest bırakılmalı, ve tabii ki hayır efendim! Bu haydut yetkililere teslim oldu ama nedense asılmadı. Belki de eski suç ortaklarını ele vererek canını kurtardı... Emin değilim. Burada birkaç gündür hapsedilmiş durumda... Gerçekten bir kâbustu efendim! O insan kılığındaki canavar malikanemizde yaşıyordu!";
			link.l1 = "Tam bir kâbus bu! O canavar, Thomas efendiye darağacından kurtulması için ne söylemiş olabilir? Aklım almıyor!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Ben de bilmiyorum, ama sana gizlice söyleyebilirim ki, Ekselansları böyle bir misafiri başından savınca bütün hizmetkarlar çok memnun oldu...";
			link.l1 = "Ondan kurtuldun mu? Sonunda hak ettiğini buldu mu?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Not quite so. Yet. A few days ago, he was taken to a military brig which sailed to Willemstad. You see, mynheer Thomas had lost interest in the scoundrel; it seems he tried to deceive him.\nAlso, they say that his former captain was caught - Bartolomeo the Portuguese! Just think of it! Looks like the Company wants to hang them together. Word is the trial will be in a month, but why wait so long?";
			link.l1 = "Portekizliler mi?! Hm... bana eşlik ettiğin için teşekkür ederim dostum... Görünen o ki, bay Thomas artık müsait, ben de artık müsaadenizi isteyeyim.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Şimdi öldünüz... ikiniz de!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Şimdi bu hiç beklemediğim bir ziyaretçi, kaptan! Ama dostça bir ziyaret gibi görünmüyor, bunca kan, gürültü ve silah sesleriyle... Yoksa bu bir kutlama mı, havai fişeklerle falan, ha?";
				link.l1 = "Şu kötü şakalarını kes, Portekizli. Sadece, benden satın aldığın özgürlüğünü nasıl kullandığını beğenmiyorum. Senin zavallı kıçını kurtarmak için fazlasıyla uğraştım, ayrılır ayrılmaz bu kadar aptalca yakalanmana göz yumamam!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Canım sıkılmıştı! O yüzden seni görmeye geldim. Burada rahat mısın, dostum!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Dikkatli ol, dostum! Ah, keşke sana yardım edebilsem!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Demek ki, asalet bazen parayla satın alınamıyor, ha? Hah... DİKKAT ET, TAM ARKANDA!";
			link.l1 = "Ah, yine bu lanet karmaşa!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Demek soyluluk bazen paraya boyun eğmiyor, öyle mi? Hah... DİKKAT ET, TAM ARKANDA!";
			link.l1 = "Ah, yine bu lanet karmaşa!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "Ve sana bu adamın başımıza bela olacağını söylemiştim!";
			link.l1 = "Az kalsın beni arkadan vuruyordu! Nasıl geçti içeri?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Onun bir maymuncuğu olduğunu gördüm, belli ki birisi ona vermiş... her zaman alt tabakada bağlantıları vardı. Neyse kaptan, bence buradan ayrılmalıyız, ne dersiniz?";
			link.l1 = "Yok artık! Peki, hadi acele edelim, yoksa bütün garnizon burada olacak. Kilidini bir saniyede açarım...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Biliyor musun kaptan, bu temiz havanın kıymetini ancak geminin sandalını yerel devriye bulup beni zindana tıktıktan sonra, birkaç hafta orada geçirdikten sonra anlıyor insan. Sanırım hâlâ seni kurtardığın için sana borçluyum.";
			link.l1 = "Gerek yok, Portekizli. Ben onurlu bir şövalye değilim, sadece... Doğru olduğuna inandığım ve yapılması gerekeni yapıyorum.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, ve bu mükemmel bir özellik! Ama ısrar ediyorum, al bunu... Hapiste saklamayı başarabildiğim tek şey bu... Evet, doğru anladın. Bu benim tılsımım. Denizde bana hep şans getirdi. Sen iyi bir denizcisin, ve eminim ki sen ya da haritacın bunu kullanabileceksiniz.";
			link.l1 = "Evet, ve o tılsımla doğrudan Hollandalıların eline düşecek kadar şanslıydın.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Hey!   Hâlâ hayattayım, değil mi?   Ve bilmeni isterim ki artık hapiste değilim.   Al bunu, kaptan, artık tılsım sana hizmet etsin.   Ve tekrar teşekkür ederim!";
			link.l1 = "Hoşça kal o zaman, Portekizli. Ve lütfen, darağacından uzak durmaya çalış! Sırf benim emeğim boşa gitmesin diye, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
