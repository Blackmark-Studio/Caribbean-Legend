// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şeye mi ihtiyacınız var?";
			link.l1 = "Hayır, şu anda değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Vay canına, sonunda karaya vardık! Uyan, Mösyö... her neyse adın... Geldik!";
			link.l1 = "A-ah! Sabah mı oldu şimdiden? Bu lanet sıcak ve nem de ne böyle?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Şuna bak! Charles de Maure! Soylu biri, biliyorsun. Bu sıcakta nasıl içki içebiliyorsun? Allah aşkına, ben su içmeyi tercih ederim.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Alışın buna, Mösyö. Burada hep böyle bir hava var... her zaman daha kötüsü olabilir.";
			link.l1 = "Daha ne kadar kötü olabilir ki!? Üzerimde sadece keten bir gömlek var ve sırtımdan terler akıyor!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Göreceksin, haha! Belki de kasırga mevsimidir! Acele et, monsieur. Sandal seni beklemeyecek. Martinique'e yüzmek istemiyorsun, değil mi?";
			link.l1 = "Bana bir dakika ver, olur mu? Kılıcım nerede? Ah, işte burada...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Artık Avrupa'da değilsiniz... Dikkatli olun, Mösyö. Zor zamanlardayız. Duyduğuma göre Amerikan Adaları Şirketi, Martinique Adası'nı birtakım dini fanatiklere, haçlılara ya da öyle birilerine satmış. Şimdilik, güverteden kıyıya bakınca garip bir şey gözüme çarpmadı. Ama biz yokken burada çok şey değişmiş olabilir.";
			link.l1 = "Haçlılar mı? Saçmalık!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Saçmalık mı, değil mi bilmem ama söylentiler aldı başını gidiyor. Zaten başımız yeterince belada. Ormanda yamyamlar, tropikal hummalar, korsanlar, sokaklarda haydutlar... Bir de İspanyollar ve İngilizler cabası...";
			link.l1 = "Ah, yine başlıyoruz... Şu anda gördüğüm tek dert bunaltıcı sıcak ve sivrisinekler... Peki, hazırım. Gidelim mi?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Üst güverteye çıkıp sandala binin, Mösyö. Karayipler'e hoş geldiniz!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Burada başka bir hava yok, 'Efendim'. Hatta, daha da kötüleşiyor.";
			link.l1 = "Hava çekilmez, tıpkı son aylardaki yol arkadaşlarım gibi. Umarım Takımadalar'da düzgün insanlar vardır.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Pekâlâ, sanırım sonunda bizi terk ettiğini görmek hepimizi sevindirecek, monsieur. Sandal seni bekliyor. Sevinçten pantolonundan fırlama. Eşyalarını da unutma – gemi yoluna devam edecek, unutur gidersen bir daha göremezsin.";
			link.l1 = "Sanki onları senin keyfin için bırakacakmışım gibi. Peso, kılıç - demek ki soyulmamışım.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Biz dürüst insanlarız, elbette, ama temkinli olman yerinde – eşyalarını gözünün önünden ayırma, yoksa birileri ceplerini boşaltabilir. Eski Avrupa'da olduğu gibi. Aslında her yerde böyle. Ama burası memleket gibi değil. Bazı fanatikler burada üs kurmuş. Söylenenlere göre, gizlice tüm adayı satın almışlar. Yani, dikkatli ol ve göze batma.";
			link.l1 = "Ne saçmalık!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Öyle söylentiler var. Burada kalışınla ilgilendiğim ve bunu seninle paylaştığım için minnettar ol. Yoksa o narin Gaskon gülün bizim kavurucu güneşimizde solup gidebilir. Saçma mı, değil mi bilmem ama aklını başında tut – fanatikler olmadan da başımız yeterince belada. Sokaklarda ve ormanda haydutlar, denizde korsanlar, bir de kızıl derili yamyamlar...";
			link.l1 = "Şimdi, şimdi! Ben hallederim. Şu an biraz sıcak gelebilir ama memlekette güneşe alışığım, mesela şu Normanlar gibi değilim. Ve eğer bir şey kılıçla çözülecekse, bana güvenebilirsin. Ama sivrisinekler – işte bu tam bir işkence! Neyse, eşyalarımın hepsi tamam. Tekne hazır diyorsun, öyle mi?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Sabırsızlıkla bekliyorum. Umarım kendi başınıza gelebilirsiniz, monsieur? Yukarı çıkın, umarım oradan kaybolmazsınız. Ah, bu arada, Takımadalar'a hoş geldiniz, heh-heh.";
			link.l1 = "Evet, sağ ol. Tek tesellim burada fazla kalmayacak olmam.";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Affedersiniz, "+GetAddress_FormToNPC(NPChar)+", Michel de Monper'i nerede bulabileceğimi söyleyebilir misiniz? O mutlaka kasabanızda bir yerde olmalı.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Buraya yeni geldiğin belli oluyor, böyle soruları bu kadar cesurca sorduğuna göre... Sana tavsiyem, dur burada, yoksa başını belaya sokarsın. Soruna gelince... Başrahip ile konuş. Onu kilisede bulabilirsin.";
			link.l1 = "Teşekkür ederim!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Dur! Silahlarınızı derhal teslim edin, Mösyö, ve bizi takip edin!";
			link.l1 = "Bu da neyin nesi?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_enterSoldiers_2");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Sizi görmek güzel, Mösyö de Maure. Ne vesileyle geldiniz?";
				link.l1 = TimeGreeting()+", memur. Kardeşim Michel de Monper hakkında konuşmak istiyorum. Elbette aramızda kalsın. Buradaki Karayiplerdeki hizmetiyle ilgili bilgi almaya çalışıyorum.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Sorgu nasıl geçti? Değerli bir şey bulabildin mi?";
				link.l1 = "Ah evet. Öyle ki, bu İspanyol'u da yanıma alıp gemime götürüyorum. Kendisi önemli bir tanık ve daha fazla sorgulanmak üzere St. Christopher'a teslim edilmeli.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Burada ne işiniz var, Mösyö?";
				link.l1 = "Kardeşim Michel de Montper'i görmeye geldim.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Efendim, size nazikçe hatırlatmak isterim ki şu anda bir askeri garnizondasınız. Lütfen buna göre davranınız.";
				link.l1 = "Evet efendim. Elbette.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Efendim, size nazikçe hatırlatmak isterim ki şu anda bir askeri garnizondasınız. Lütfen buna göre davranınız.";
				link.l1 = "Evet, efendim. Elbette.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper şu anda Şövalye Philippe de Poincy'nin şahsi emriyle muhafaza altında, cephaneliğimizin birinde tutuluyor. Aşağı kata inin. Depo ve hücre olarak kullandığımız cephanelikleri orada bulacaksınız. Yolunuzu bulabileceğinizi düşünüyorum.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Merhaba, Mösyö. Size yardımcı olabileceğim bir şey var mı?";
			link.l1 = "Teşekkür ederim, asker, ama hayır, gayet iyiyim. Devam et.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Beklediğiniz için teşekkürler, Mösyö. Yani, Michel de Monper'i mi arıyorsunuz? Onun kardeşi misiniz?";
			link.l1 = "Evet, doğru. Ben onun kardeşi Charles'ım. Onu hemen görmem gerek. Michel bir sorun mu yaşadı?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Ne yazık ki öyle, Mösyö. Michel aşağıdaki mahzenlerden birine kapatıldı. Yeni Dünya’daki Fransız kolonilerinin Genel Valisi Şövalye de Poincy, tutuklama emrini bizzat imzaladı. Hepimiz şok olduk. Kardeşiniz erkekliğin, disiplinin ve cesaretin timsali, Tarikatımızın gururudur! En kötüsü de biz, onun dostları, onu parmaklıklar ardında tutup sıradan bir suçlu gibi korumak zorunda kalıyoruz! Elimizden geleni yapıp rahat etmesini sağlıyoruz ama... hapishane yine de hapishane.";
			link.l1 = "Ne ile suçlanıyor? Bir suç mu işlemiş?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Genel Vali'nin ofisi Michel'i zimmete para geçirmekle suçladı! Ne kadar saçma! Buradaki herkes bunun siyasi bir mesele olduğuna inanıyor. Sana gizlice bir şey söyleyeceğim. Michel, Tarikat adına bazı gizli işlere katılıyordu. Belki de bilmemesi gereken şeyleri öğrendi. Ya da daha kötüsü, bazı güçlü adamları kızdırdı. Ama para çalmak mı? Buna kimse inanmıyor. Bu bir bahane, gerçek bir sebep değil, korkakça ve aşağılık bir bahane! Ama artık yeter. Kardeşin seninle görüşmek için sabırsızlanıyor, eminim her şeyi bizzat kendisi anlatacaktır.";
			link.l1 = "Güzel. Hapishaneniz nerede bulunuyor?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Şehrin tam ortasındaki yeraltı cephaneliğimizde. Beni takip et. Yolunu göstereceğim.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_1");
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "İşte geldik. Burası bizim harekât üssümüz - Kudüs, Rodos ve Malta Aziz Yuhanna Askeri Hastane Tarikatı'nın Karayipler Şubesi. Mühimmat odaları alt katta. Koridordan ilerleyip yemek salonu ile şapelin yanından geç. Oradaki merdivenler seni aşağıya götürecek. Hücrelerle dolu bir koridor arayacaksın. Kardeşini en arkadaki hücrelerden birinde bulacaksın.\nGit, Charles, Tanrı yardımcın olsun. Lütfen Michel’e yardım et! O suçsuz, burada herkes buna yemin etmeye hazır.";
			link.l1 = "Bu berbat yere gelmemin tek nedeni kardeşimi görmekti. Umarım onu en azından bu beladan kurtarabilirim.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_2");
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Yani Michel de Monper'i mi arıyordun? Ve sen onun kardeşi misin?";
			link.l1 = "Evet, doğru. Ben onun kardeşi Charles'ım. Onu hemen görmem lazım. Başını belaya soktu, değil mi?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Ne yazık ki öyle, Mösyö. Michel tutuklandı ve hapishanemize kapatıldı. Fransız kolonilerinin genel valisi Chevalier de Poincy bizzat emri verdi ve imzaladı. Hepimiz şok olduk.\nKardeşiniz erkekliğin, kararlılığın ve cesaretin örneğidir, Tarikatımızın gururudur! En kötüsü de, onun arkadaşları olarak hücresini kilitleyip bir suçlu gibi onu korumak zorunda olmamız! Durumunu hafifletmek için elimizden geleni yapıyoruz ama... hapishane hapishanedir.";
			link.l1 = "Peki, onu neyle suçluyorlar? Bir suç mu işlemiş?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Nonsense! Utter nonsense! They have accused Michel of embezzlement and stealing state funds. Ridiculous! We are all certain it is nothing but a political game. Michel was involved in secret operations of the Order; perhaps he discovered more than he ought to have.\nOr something else. But stealing money! No one believes that. It is merely a pretext, not a reason—such a crude and foolish pretext! But enough talk. Your brother is looking forward to seeing you; I am sure he will tell you everything himself.";
			link.l1 = "Güzel. Hapishane nerede?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Şehrin içindeki yeraltı üssümüzde, burada. Beni takip et. Sana yolu göstereceğim.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_3");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "Sonra eğildi ve öyle çok kustu ki, Karayipler’in kendisi bile yeşile döndü! Ha-ha-ha!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Ah! Charles, ben de az önce çocuklara maceralarımızı anlatıyordum!";
			link.l1 = "Fark ettim. Dinle, Alonso. Ben... artık bir kaptan oldum.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Şimdiden mi? En az bir ay sürer sanmıştım, ha-ha!";
			link.l1 = "Gayet ciddiyim!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Were it only myself, I would sign on at once. But I have forty souls from the Ulysses with me. They have trusted me with their future; I must be sure you will not fail them\n"+
			"What sort of vessel have you?";
			link.l1 = "Bir gemi gemidir, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+" . Neden, bu gerçekten bu kadar mı önemli?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Biliyor musunuz, Ulysses'ten sonra bir barka ya da tartanede hizmet etmek istemeyiz. Geminizi gördük, tayfa da onayladı\n"+"Şimdi, para meselesi. Önceden 4.800 peso istiyoruz. Sonrasında—her zamanki gibi paylaşıyoruz. Hiçbir abartı yok, emin olabilirsin. Bunu halledebilir misin?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Çok iyi iş çıkardın! Al bakalım, paran burada.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Ne yazık ki, şu anda yanımda o kadar çok param yok.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Ambarında erzak var mı, kaptan? Ya ilaç? Yok mu? Eh, bu hiç iyi değil. Git, yolculuğumuz için en azından gerekli olanları al, sonra geri gel ve konuşuruz. Dükkana git, neye ihtiyacın varsa al.";
				link.l1 = "Hm. Haklısın. Peki, öyle yapacağım.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah! Tebrikler... Kaptan! Hemen adamları toplayacağım ve geminize doğru yola çıkacağız.";
				link.l1 = "Macera kaldığı yerden devam ediyor Alonso. Gemiyi denize açılmaya hazırla!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Peki, yeterince para bulur bulmaz geri gel. Bizi burada, meyhanede bulacaksın. Zaten etrafta başka gemi yok. Biz de içip para harcamaya, kadınlara akıtmaya devam ederiz, ha ha!";
			link.l1 = "En kısa zamanda dönmeye çalışacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Geri mi döndün, kaptan? Beni ve tayfamı işe almaya hazır mısın? Ceplerimiz hafiflemeye başladı, yüzümüzde tekrar deniz esintisini hissetmemiz gerek!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Henüz değil, hâlâ her şeyi hazırlıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Evet. Avansını al. Artık benim hizmetimdesin.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Merhaba, kaptan! Ne istiyorsunuz?","Merhaba, Mösyö. Size nasıl yardımcı olabilirim?","Günaydın. Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Sana bir sorum var.","Bu koloni hakkında bilgiye ihtiyacım var.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Sadece merhaba demek istedim. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Ne oldu?","Ne istiyorsun?");
			link.l1 = "Dinle, "+GetAddress_FormToNPC(NPChar)+", bakın mesele şu... Bir dümenci arıyorum. Belki kasabada bu işe uygun birini biliyorsunuzdur?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Bir Seyirci mi? Hm. Aslında birini tanıyorum... Ama bir sorun var - hapiste, borçlular hapishanesinde. Zavallı adam neredeyse bir aydır cephanelikte kilitli, ta ki borcunu o ya da bir başkası ödeyene kadar.";
			link.l1 = "Bir borçlu mu? Hm... Adı ne?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Adı Folke Deluc. Onu görmek istiyorsan hapishane komutanına sor. Ama borcunu ödemedikçe oradan çıkmasına izin vereceklerini sanmam, çünkü kendisi kesinlikle ödeyemez, hahaha!";
			link.l1 = "Belki de yaparım. Bilgi için sağ ol, dostum.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Böyle bir onuru neye borçluyum, Mösyö?";
			link.l1 = "Merhaba, Folke. Durum basit, bir gemim var ama bir rotacıya ihtiyacım var. Ve bana bir rotacı lazım. Bu yüzden senin borcunu ödedim...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Beni buradan çıkartıp sadece kendi tayfana almak için mi sürükledin?";
			link.l1 = "Aynen öyle. Sana harcadığım parayı kısa sürede telafi edeceğini düşünüyorum. Neyse... nasıl gideceğini göreceğiz.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Teşekkür ederim, Mösyö. Bu çürük, nemli hücreden bıktım artık. Yeniden gemiye dönmek bana büyük bir keyif verecek. Ah, deniz...";
			link.l1 = "Anlaştığımıza sevindim, Folke. Bir şey daha, gemi kullanmak dışında başka hangi yeteneklerin var?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Her işten biraz anlarım, kaptan. Eskiden Hollanda Batı Hindistan Şirketi'nin bir korsan gemisinde görev yapardım. Orada topları nasıl kullanacağımı öğrendim, yani isterseniz topçu subayı olarak hizmet edebilirim. Ticaret ve gemi basma ise en zayıf olduğum konular.";
			link.l1 = "Paylaştığın için teşekkür ederim, şimdi benimle gemiye gel. Mürettebat ayrılış için hazırlık yaparken senin tecrübeli gözlerinle onları izlemeni istiyorum. Sonra, mümkün olan en kısa sürede Guadeloupe'a gitmek istiyorum.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Emredersiniz, kaptan! Seni kamaranda bekleyeceğim. *Denizdeyken eylem menüsünü kullanarak kamara ve geminin diğer bölümlerine erişebilirsin*";
			link.l1 = "Teşekkürler, Folke. Gemide görüşürüz.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Harika bir lugger, kaptan! Oldukça düzgün, küçük bir gemi; donanımı sağlam, kerestesi iyi. Böyle bir gemiyle sadece Guadeloupe'a güvenle varmakla kalmaz, istersek tüm Karayipler'i de dolaşabiliriz.";
			link.l1 = "Mükemmel. En azından paramı su alan bir tenekeye atmadım... Denize açılmadan önce bana bir tavsiyen var mı, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Lanet olsun, bu şalopa resmen süzgeç gibi su alıyor, kaptan. Guadeloupe'a geçmek bizim için zor olacak. Basse-Terre'e sağ salim varmak istiyorsan, gemiyi hemen tersaneye çekip tamir ettirmeliyiz.";
			link.l1 = "Başka seçeneğim yoktu, satılık tek gemi buydu! Hem de bana bir servete patladı. Bildiğin gibi, şu an tamir edecek vaktimiz de yok... Denize açılmadan önce bir tavsiyen var mı?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Well, we are well supplied with powder and shot, Captain. This will do for now; only remember to replenish in time.";
				link.l1 = "Bu zaten açık. Başka bir yorumun var mı?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah! Hatırlattığın için sağ ol. Yanımda bir sandık dolusu gülle var!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Dergide yeterli cephanemiz yok, kaptan. En az yüz top mermisi, zincir gülle ve bomba ile birlikte yüz torba saçma ve iki yüz varil barut lazım. Gerekli malzemeleri al, kaptan. Çok pahalıya mal olmaz, ama korsanlar ya da İspanyollar saldırırsa hayatımızı kurtarabilir.";
				link.l1 = "Değerli bir yatırım. Ben tüccara gidiyorum.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...Peki, bunu ne zamandır yanında taşıyorsun?";
			link.l1 = "Neredeyse iki haftadır.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "Ama neden, Kaptan?!";
			link.l1 = "Ufak tefek şeyler toplamayı severim. Ne zaman ne işe yarayacağı belli olmaz.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Pekala, bu senin için kötü oldu. Bu saçmalar oyuncak silahlarımıza asla uymaz. Aslında, bu kadar büyük bir saçma hiç görmedim. Bunlardan biri Adeline'i dibe gönderirdi.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Mühimmat alışverişini bitirdiniz mi, kaptan?";
			if (bOk)
			{
				link.l1 = "Evet, söyledim. Başka bir yorumun var mı?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Şu anda değil, hâlâ üzerinde çalışıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Aferin, tayfan için yeterince silah aldın. Yeterli silahımız olmazsa, gemi baskınlarında çok daha fazla adam kaybederiz. Tanrı bizi bundan korusun. Ambarı sık sık kontrol etmeyi unutma\nİhtiyacımızdan biraz fazla silah bulundurmak akıllıca olur. Şu lanet fareler tahta kabzaları ve dipçikleri kemirmeye bayılıyor.";
				link.l1 = "Anladım.   Hâlâ eklemek istediğiniz bir şey var mı?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "We don't have enough weapons on board for the crew. If we don't have enough weapons, we'll lose far more men during boarding actions. God protect us from that. As far as I understand, you have forty men in the crew\nBuy enough weapons for each, or even buy a few extra; fifty sets should suffice. It's prudent to keep a few more weapons than we'll need. The damn rats like to gnaw on the wooden handles and stocks.";
				link.l1 = "Bunu yapacağım. Yakında dönerim.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Silahları almayı bitirdiniz mi, kaptan?";
			if (bOk)
			{
				link.l1 = "Silahlar ambarın içinde. Görüyorum ki eklemek istediğiniz başka bir şey var mı?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Şu anda değil, hâlâ üzerinde çalışıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Hayır, sanırım bu kadar. Yeterince yiyeceğimiz var, bir de tayfanın romunu da hallettin. Bu akıllıca, çünkü vardiyadan sonra güzel bir soğuk romdan daha iyi bir ilaç yoktur. Denizciler, onlara günlük rom payını veren kaptanları sever ve saygı duyar. Adamlarının 'Rom neden bitti?' diye sormasını asla istemezsin.";
				link.l1 = "Şimdi yelken açabilir miyiz?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Yes. Food and rum. It's disastrous if you don't have enough food on board. Always have more victuals than you think you'll need. You never know how long a voyage will last - a dead calm or a strong gale can ruin any plan. The men will mutiny or die of hunger when the provisions are gone\nThe rum supply is not as critical, but I strongly recommend always keeping some on board; there's no better cure for all ailments than a nice cool jigger of rum after your shift. Sailors love and respect captains who give them their daily rum ration\nSo go and buy the supplies we need - at least a hundred crates of food and ten barrels of rum. You never want to hear your men ask: 'Why is the rum gone?'";
				link.l1 = "Sanırım haklısın. Gidip tüccarla tekrar konuşacağım.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Yiyeceklerimizi ve romumuzu aldın mı, kaptan?";
			if (bOk)
			{
				link.l1 = "Evet. Şimdi denize açılabilir miyiz?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Hayır, hâlâ üzerinde çalışıyorum.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Pekala, kaptan. Demir alıp kuzeye, Guadeloupe'a doğru yelken açabiliriz, istediğiniz gibi.";
			// belamour legendary edition -->
			link.l1 = "Harika iş çıkardın, Folke. Sensiz başaramazdım.";
			link.l1.go = "Folke_13";
			link.l2 = "Pekâlâ, işe koyulalım, bakalım paranın hakkını verecek misin.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "O zaman beni dümenci olarak atayın, ben de güvertede yerimi alayım.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "O halde beni dümenci olarak atayın, ben de güvertede yerimi alayım.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Hazırız, kaptan!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Kaptan, beni dümene geçir, yoksa kısa sürede karaya otururuz.";
				link.l1 = "Anladım, şimdi halledeceğim.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Özür dilerim. "+GetFullName(pchar)+"?";
			link.l1 = "Doğru. Bunun için size ne borçluyum, efendim?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "İzin verin kendimi tanıtayım - "+GetFullName(npchar)+". Beni buraya Cesar Craig gönderdi. Onu mutlaka tanıyorsunuzdur. Le Francois'daki meyhanenin sahibi. Bildiği kadarıyla, Guadeloupe'a gitmek üzeresiniz. Size kolay yoldan para kazanma fırsatı sunmak istiyor.";
			link.l1 = "Hm... İlginç! Peki Cesar Craig bu kadar bilgili olmayı nasıl başardı?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "It's simple, captain. Your ship is the only one in St. Pierre at the moment; anyone with two ears and one eye knows everything about who you are and where you're headed. Out here in the colonies, rumours fly faster than seagulls. So, are you interested in hearing our offer?";
			link.l1 = "Tabii. Para kazanmak hiçbir zaman fena olmaz.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "İşte şimdi anlaştık! Senin işten iyi anladığın belli. Anlaşma şöyle: Cesar'ın acilen Guadeloupe'a bir parti şarap göndermesi gerekiyor. İki yüz fıçı, geminin ambarı bunu rahatça alır. Kolay bir iş için on bin peso ödenecek – Cesar acele ediyor ve şu an limanda sadece senin gemin var. Kabul et, böyle kârlı teklifler kolay kolay gelmez.";
			link.l1 = "Vay canına, on bin peso mu? Pekâlâ, anlaştık!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Le Francois'ya git ve Cesar'la konuş. O her şeyi halledecek. Senin tek yapman gereken Le Francois'ın hemen dışındaki koyda demir atmak olacak. Beni mahcup etme, Cesar seni ikna edersem bana bin peso vereceğine söz verdi...";
			link.l1 = "Endişelenme, beni ikna olmuş say. Hazır olur olmaz, doğrudan Le François'ya yelken açacağım.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Yaşasın! Binimi almaya gidiyorum. Sağ ol, dostum!";
			link.l1 = "Rica ederim...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Kaptan, baskın ekibi kuruldu ve hazır! Emirlerinizi bekliyoruz!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Baş üstüne, kaptan! Hazır olun çocuklar, kaptanı takip edin! Hop, bir-iki-üç!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Lanet olsun, Fransız takviyeleri! Sıraları oluşturun! Lorenzo, kampa koş ve alarmı ver! Geberin, alçaklar!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Böyle bir bilgiyi paylaşmaya yetkim olmadığını anlıyor musunuz?";
			link.l1 = "St. Pierre'nin İspanyollar tarafından yağmalanmamasının sadece zamanında müdahalem sayesinde olduğunu anlıyor musun? Kardeşim ortadan kayboldu, Tarikat'ı terk etti! Bunu bir sebep olmadan yapmış olamaz. Ben, Sir Philippe de Poincy'nin temsilcisi olarak, soruşturma yürütme yetkisine sahibim!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Pekala, pekala, Mösyö de Maure. Sorularınızı cevaplayacağım. Önce sakin olun. Şimdi, sorunuzu sorun.";
			link.l1 = "Michel   hapse atılmadan önce ne oldu?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper, Tortuga'da bir rejim değişikliği ayarlamak için bazı korsan baronlarıyla pazarlık yapıyordu.";
			link.l1 = "Bunu zaten biliyorum. Başka ne var?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "O, aynı zamanda İspanyollara karşı başka bir operasyon da planlıyordu. Daha doğrusu, değerli bir yük taşıyan bir İspanyol gemisinin ele geçirilmesi. Michel, hedefi ağır korvet 'Gryffondor'un toplarının altına çekmeliydi. Bu planı yaparken uzun süre ondan hiç haber alamadık.\nAma plan ters gitti. İspanyol nakliye gemisi gelmedi ve Michel'in kendisini yerel balıkçılar Le Marin Körfezi kıyısında yarı ölü halde buldu. Görünüşe göre operasyon başarısız oldu.\nSavaş, savaştır; işler bazen yolunda gitmez. Michel'in hayatta kalması bile bir mucizeydi, ama Chevalier de Poincy öfkeye kapıldı. Michel'i Düzen'in parasını zimmetine geçirmekle suçladı ve onu hapse attırdı. Elbette biz bu suçlamalara inanmadık. Michel dürüst bir adamdır, Düzen'in gerçek bir şövalyesidir. Valinin neden böyle davrandığını yalnızca Tanrı bilir. Belki Chevalier de Poincy bunu sana kendisi anlatır?";
			link.l1 = "Belki.   Bildiğin   tek   şey   bu   mu?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Maalesef, söylenecek başka bir şey yok. Kardeşinizin operasyonlarının ayrıntılarını yalnızca kendisi ve Şövalye de Poincy biliyordu. Biz Malta Aziz Yuhanna Tarikatı'nın şövalyeleriyiz. Emirlerimizi yerine getiririz.";
			link.l1 = "Eğer Şövalye Michel’e bu kadar güveniyorsa, demek ki daha önce gizli planlarını başarıyla yürütmüş olmalı. Michel’in gerçekleştirdiği başarılı işlerden haberin var mı?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Kesinlikle öyle. Michel de Monper'in bu son başarısızlığı aynı zamanda onun ilk hatasıydı, bu yüzden Şövalye'nin tepkisi bizi şaşırttı. Kısa bir süre önce, Michel'in titiz planlaması sayesinde 'Gryffindor' gümüşle dolu bir İspanyol hazine gemisini ele geçirdi. Bu tek başına, gelecekteki onlarca hatayı telafi etmeye yeterdi. Ama yine de, kardeşiniz tutuklandı.";
			link.l1 = "Anladım. Michel'in St. Pierre'den neden kaçtığına dair bir fikrin var mı?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Michel ile de Poincy arasında yaşanan bir kişisel anlaşmazlığın onun tutuklanmasına sebep olduğunu düşünüyorum. Belli ki, kardeşiniz Şövalye'nin serbest kaldıktan sonra da onu rahat bırakmayacağından korkuyor, bu yüzden önlem aldı. Ve biliyor musunuz, Mösyö de Maure - burada kimse onun bu kararını yadırgamıyor!\nAdam, Tarikat'ın iyiliği için cesurca çalıştı ama ilk hatasında, hem de ağır yaralıyken, onu pis bir hücreye tıktılar! Üstelik öyle büyük bir hata da değildi, kimse ölmedi, hiçbir gemi batmadı!\nBu arada, bu konuşma kesinlikle aramızda kalacak, az önce söylediklerimi yemin altında bile tekrar etmem, anlaştık mı Mösyö de Maure?";
			link.l1 = "Evet, efendim. Bu konuşmayı yaptığımızı bile unuttum sayılır. Söylesenize, acaba İspanyolların St. Pierre’e saldırısı, Tarikat’ın İspanyol gemilerine saldırmasından mı kaynaklandı? Belki de bahsettiğiniz o gümüş yüklü İspanyol kalyonu yüzündendir? Kastilyalılar, üssünüzü bulmak için fazlasıyla hevesliydi...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Doubt it. Very few people know about the Order's presence in the Caribbean, and all our sorties against the Spanish were carefully planned. Ask the Spanish officer we took prisoner; he is cooling his fiery Castilian temper in our casemates right now. We have already interrogated him. The attack on St. Pierre was an ordinary raid, organised by a Spanish grandee named Ramon de Mendoza y Riba for his own profit and to intimidate the French colonies. He also wanted to curry favour with the Escorial.";
			link.l1 = "Bu İspanyol ile konuşacağım. Onu nerede bulabilirim?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Aşağıda, kardeşinin tutulduğu aynı hücrede.";
			link.l1 = "Yolu biliyorum. İspanyol'u sorguladıktan sonra döneceğim. Belki birkaç ek sorum daha olur.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Vay canına, bu da bir şey! O esiri serbest bırakamayacağımı anlıyorsun, değil mi? O herif, St. Pierre'e yapılan saldırıya öncülük etti!";
			link.l1 = "Subay, bu önemli bir tanık. St. Pierre'e yapılan saldırı, ganimet peşinde basit bir baskın değildi. Don Ramon Mendoza başka bir şey arıyordu. Kesin bir gerekçe belirlememiz gerekiyor. O halde, bu İspanyol'u bana teslim edecek misiniz, yoksa de Poincy'den izin istemem mi gerekecek?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Tanrı aşkına... Peki, alın onu. Zaten bu herifi St. Pierre meydanında sıradan bir korsan gibi asacaktım... Artık o sizin derdiniz. Adaletin elinden kaçmasına izin vermeyin!";
			link.l1 = "Hiç şüphesiz. Bu İspanyol için de Poincy'nin önünde hesap vereceğim. Bu esiri zincirleyin ve kasaba iskelesindeki sandalımın yanına götürün.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Pekâlâ, kaptan.";
			link.l1 = "Bir şey daha, memur. Miguel Dichoso ismi size bir şey ifade ediyor mu?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Hayır. Daha önce hiç duymadım. Neden soruyorsun?";
			link.l1 = "Emin misiniz? Yani bu isimde birini ne burada karargâhınızda, ne valinin sarayında, ne de St. Pierre'de herhangi bir yerde görmediniz mi?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Hayır, etmedim. Benim memleketimde İspanyollar pek iyi anılmaz.";
			link.l1 = "Pekala. Her neyse, bu beklenirdi zaten. Çok kolay olurdu... Teşekkürler, memur bey! Çok yardımcı oldunuz.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Rica ederim... Ne düşünüyorsunuz, Monsieur de Maure, kardeşiniz şu anda nerede?";
			link.l1 = "Ben de o sorunun cevabını öğrenmek isterim. Ve öğreneceğim... er ya da geç. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Sen kaptan mısın "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Size nasıl yardımcı olabilirim?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Selamlar, kaptan. Beni size Peder Vincente gönderdi. Sizin için bir şeyim var...";
			link.l1 = "Padre Vincento mu? Artık Ekselansları için çalışmıyorum. Diego de Montoya'nın adamı Alonso de Maldonado'yu beni öldürmek için gönderdiğinden beri değil. Saygıdeğer Peder'e bu mesajı iletebilirsin: Başaramadı.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Bekleyin, kaptan. Peder Vincento böyle bir tepki göstereceğinizi tahmin etti ve beni uyardı. Emin olun, Ekselansları size zarar vermek istemiyor. Lütfen, bu mektubu okuyun. Bu gerçekten çok, çok önemli.";
			link.l1 = "Peder Vincento bana kötülük istemiyor mu? Hm. Belki de Don de Maldonado ile aramdaki şeyleri de sana anlatmadı? Sana neden inanmalıyım ki?";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Bu mektubu al, kaptan. Oku ve kendi kararını ver. Bil ki tüm Hristiyan âleminin kaderi senin ellerinde. Bunu hafife alma. Tanrı seni kutsasın ve adil bir yolda ilerletsin!";
			link.l1 = "Pekala, mektubu ver.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Al bakalım. Umarım doğru kararı verirsin. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Selam, oğlum. Tanrı seninle olsun.";
			link.l1 = "Ve size de, Peder Adrian. Ekselansları bana tılsımlar ve ilaçlar sağlayabileceğinizi söyledi.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Evet, tabii ki. Sadece senin için Santiago'dan özel bir sevkiyat aldım. İşte kutsanmış muskalar ve şifalı iksirler. Üstelik, dövüşte seni yenilmez yapacak nadir ve eşsiz bir Ometochtli tentürü de var. Bunların hepsi senin için, oğlum. Al ve Rabbin ne kadar iyi olduğunu gör.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Eğer daha fazla şifalı otlara ihtiyacınız olursa, her gün size her birinden birer şişe verebilirim. İhtiyacınız kadarını hazırlarım.";
			link.l1 = "Teşekkür ederim, Peder Adrian. Bunu aklımda tutacağım.";
			link.l1.go = "exit";
			link.l2 = "Harika. Şu anda gerçekten ihtiyacım var.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Tanrı seni korusun ve gözetsin, oğlum. Ne istersin?";
			link.l1 = "Biraz şifa iksiri satın almak istiyorum.";
			link.l1.go = "potion";
			link.l2 = "Şu anda bir şey yok, bir yolculuğa hazırlanıyorum. Sadece uğrayıp selam vermek ve nasıl olduğunu görmek istedim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Elbette, oğlum. Hangi ilaca ihtiyacın var?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Sadece basit bir çare.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Şifa veren bir iksir.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Bir panzehir.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Bitkisel bir karışım.";
				link.l4.go = "potion4";
			}
			link.l5 = "Rahatsız ettiğim için üzgünüm, Baba. Fikrimi değiştirdim.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Şifalı bir öz mü? O zaman 90 peso, evladım. Malzemeler için, tabii ki.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Teşekkür ederim, baba.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Maalesef, param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Şifa veren bir iksir mi? 500 peso, evladım.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Teşekkür ederim, baba.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Ne yazık ki, param yok... Sonra tekrar geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Bir panzehir mi? 200 peso, evladım.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Teşekkür ederim, baba.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Maalesef, param yok... Daha sonra geri geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Bitkisel bir karışım mı? 900 peso, evladım.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Teşekkür ederim, baba.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Maalesef, param yok... Daha sonra geri geleceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = " 'Çünkü sana sağlık vereceğim ve yaralarını iyileştireceğim, diyor Rab.' İşte ilacın. Dominus vobiscum! ";
			link.l1 = "Teşekkür ederim, Peder Adrian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Kaptan "+GetFullName(pchar)+"?";
			link.l1 = "Evet, benim. Ne istiyorsun?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Kaptan Miguel Dichoso’dan size bir mesaj getirdim. Onu tanıdığınızı söylüyor.";
			link.l1 = "Evet, ondan duydum. Onunla şahsen tanışma şerefine hiç erişemedim.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Kaptan Dichoso bunu değiştirmek istiyor. Sizinle yüz yüze görüşmek istiyor. Size, İspanyol Ana Karası'nın derinliklerindeki kayıp Tayasal şehrine yapılacak bir keşif gezisiyle ilgili bir teklifi var. Bana, sizin tecrübenizle onun bilgisinin birleşmesinin tatmin edici sonuçlar doğuracağını söyledi.";
			link.l1 = "Bunlar tam olarak onun sözleri miydi?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Doğru. Kaptan Dichoso seni St. Christopher'da bekliyor olacak. Meraklı gözlerden ve kulaklardan uzak durmak için Capsterville mezarlığının büyük mahzeninde seni bekleyecek.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso bana tereddüt edeceğini söyledi. Müzakereler sırasında ne karar verirsen ver, sana zarar gelmeyeceğine dair garanti vermemi istedi. Ayrıca, o meşhur adada bulduğun şeyin, Tayasal'da bulacaklarının yanında sadece küçük bir başlangıç olduğunu da ekledi.";
			link.l1 = "Öyle mi... bu gerçekten ilginç. Ama Kaptan Dichoso neden bizzat kendisi gelmedi de, üçüncü bir kişiyi gönderdi?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso önce seni Isla Tesoro'da aradı, sonra burada, şimdi ise seni orada bulma umuduyla St. Christopher'a gitti. Sen bizzat Philippe de Poincy'nin subayısın, değil mi? Eğer Blueweld'e gelirsen diye burada seni beklemem söylendi.";
			link.l1 = "O zaman her şey açık. Peki, tamam. Zaman kaybetmeyeceğim, Capsterville'e gitmeliyim.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Nihayet tanışıyoruz, kaptan "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Miguel Dichoso nerede? Ve bu işten sıyrılmaya çalışma. Onun kim olduğunu gerçekten biliyorum, bence sen de biliyorsun.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Sanırım karşımda duran kişi bizzat Miguel Dichoso'nun ta kendisi?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Doğru tahmin ettiniz, kaptan. Uzun zamandır birbirimizin peşindeyiz, değil mi?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Sana bakınca yalan söylediğini hemen anlıyorum. Sen Dichoso değilsin. 'Santa Quiteria'nın kaptanının seyir defterini okudum, görünüşü hakkında da etrafa sordum. Ona hiç benzemiyorsun. Yüzünde süvari kılıcından kalma bir yara izi bile yok. Hadi ama, bir soytarı bile en azından sahte bir iz çizmeye çalışırdı!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Aynen öyle. Bildiğim kadarıyla, buraya kayıp Tayasal şehri hakkında konuşmaya geldik, değil mi?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha! O zaman bu maskaralığı sürdürmenin anlamı yok. Miguel, senin kurnaz bir serseri olduğunu söylemişti bana...";
			link.l1 = "Miguel Dichoso nerede?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "O burada değil. Onun adına seninle buluşmaya ve konuşmaya yetkiliyim.";
			link.l1 = "Bir piyonla konuşmam. Ben buraya kral için geldim. Nerede o?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Pek hoş bir sohbet ortağı değilsiniz, kaptan. Sakinliğinizi kaybettiniz.";
			link.l1 = "Yeter artık, anladım. Yine pusu kurmuşsunuz. Yeni numaralar bulmanız lazım, çocuklar.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Yine doğru bildin! Adamlarım seni mahzenlere inen kapının hemen arkasında bekliyor. Üstelik, her bir mezar taşının arkasında saklanan tüfekçilerim var, ateş etmeye hazırlar. Kaçış yok. Bu numara ne kadar tekrar ederse etsin, yine de tuzağıma düştün! Tayasal'ı görme arzun sağduyunu bastırdı!";
			link.l1 = "Kavga etmek için güzel bir yer seçtin, pislik. Seni ve haydut arkadaşlarını gömmek için uzağa gitmem gerekmeyecek.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Ha! Zekânı beğendim! Tıpkı Miguel gibi! Ne dersen de, ikiniz de aynı kumaştansınız... Onun emrettiği gibi yapacağım – seni cehenneme olabildiğince hızlı ve acısız göndereceğim. Silah başına, çocuklar!";
			link.l1 = "Senden daha iyi adamlar denedi. Şeytana selamımı söyle, alçak!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Şehre gerçekten gitmek mi istiyorsunuz? Anlıyorum, kaptan, ama bunun iyi bir fikir olduğunu sanmıyorum.";
			link.l1 = "O halde burada ne konuşacağız?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Seninle uzun, romantik bir sohbet yapmak istemiyorum. Buradasın ya, bu bana yeter.";
			link.l1 = "Yeter artık, anladım. Yine pusu kurmuşsunuz. Siz çocukların yeni numaralar bulması lazım.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Emirlerinizi bekliyorum, kaptan!";
			link.l1 = "Ormanın içinden geçip Capsterville mezarlığına gidiyoruz. Oraya vardığımızda, mezarlığın içine girmeyin. Kapının hemen dışında mevzi alın ve ben içeri girdiğimde dikkatlice dinleyin. Kavga sesleri duyarsanız, hemen içeri dalın.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Emrinizi bekliyorum, kaptan!";
			link.l1 = "Ormanın içinden Capsterville mezarlığına doğru ilerliyoruz. Oraya vardığımızda, mezarlığın içine girmeyin. Patika boyunca mevzi alın, mezarlığı çepeçevre sarın ve benim içeri girdiğimi dikkatle dinleyin. Bu işin içinde pusudan başka bir şey kokmuyor. Düşmanı görür görmez, hiç vakit kaybetmeden saldırın.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Baş üstüne, kaptan!";
			link.l1 = "Pekâlâ. İleri!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Kaptan Hobart! Casusumuzun verdiği bilgilere göre, isyancılar bu malikanede saklanıyor. Emrinizde beş dragon var. Binayı arayın ve içeride saklanan herkesi yakalayın! Bu pisliklere karşı yumuşak davranmayın. Kral adına hareket ediyorsunuz!";
			link.l1 = "Evet, efendim!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Deniz Oğlu!";
			link.l1 = "Ha... ne? Benimle mi konuşuyorsun?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Pekala. Ben Kakao Yaprağı'yım. Seninle bir işim var, Deniz'in Oğlu.";
			link.l1 = "Kakaonun nasıl göründüğünü bilmiyorum, ya da neden adını ondan aldığını da. Neyse, neye ihtiyacın var, çabuk söyle.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Şehre git. İki tabanca ve onar tane barutla kurşun setinden iki tane al. Onları bana getir. Bir ödül var. Deniz Oğlu memnun olacak.";
			link.l1 = "İki tabanca ve yirmi mermi mi? Hepsi bu mu? O zaman neden kendin almıyorsun?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Anlamıyor musun, soluk surat? Kim bana silah satar ki?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Biliyor musun, Martinique'te senin gibilerle daha önce de karşılaştım... Yamyamlar. Bir kızı ve iki adamı kaçırdılar. Adamların birini kızartıp yediler. O adamlardan birinin bile silahı olsaydı, şu an bu konuşmayı yapıyor olmazdık.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "Ve neden bir ateşli silaha ihtiyacın var, Kakao Yaprağı? Birini öldürmeyi mi düşünüyorsun?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Kakao Yaprağı bir haydut değil, benim kavgam sadece kabilemin savaşçılarıyla. Soluk yüzlüler topraklarımıza geliyor, bizi köle yapıyorlar. Kakao Yaprağı kendi başına savaşıyor. Bir köle al. Ne iyi, ne kötü. Hayat böyle. Kızılderili, beyaz, fark etmez. Ateşli silahlar fark yaratıyor.";
			link.l1 = "Ve neden bir ateşli silaha ihtiyacın var, Kakao Yaprağı? Birini öldürmeyi mi düşünüyorsun?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Savaşmak için. Ama eşit şartlarda. Beyazların ateşli silahları var, Kızılderililerin yok. Bu adil değil. Bir Kızılderili için ateşli silah sahibi olmak, beyazların haksızlığına, aşağılamasına ya da hakaretine karşı bir korumadır.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Doğru, Kaptan. Soluk yüzlüler bize tepeden bakıyor.";
			link.l1 = "Fark ettim. Avrupa'da, yerlilere gerçek inancı öğretmekten ve herkesin plantasyonlarda barış içinde çalıştığından bahsederler...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu kaptanı anlamayabilir, ama Kakao Yaprağı'nı anlar. İntikam peşinde.";
			link.l1 = "Öyle görünüyor... Sen de intikam almak istemiyor musun, bizi esir edenlerden?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Belki. Ama Tichingitu buna başvurmaz. Tichingitu artık senin yanında. Ve Tichingitu kendi aklını kullanır. Çok fazla kan dökülürdü. Beyazların kanı. Kızılderililerin kanı. Çok fazla acı. Bu doğru olmaz.";
			link.l1 = "Evet, işler zaten kötü, bir de Cocoa Leaf’e silah sağlamamız durumu daha da kötüleştirir... Ama söylediklerinde de bir gerçek payı var. Hem yakında mürettebata da ödeme yapmam gerekecek.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Kendi aklını kullan, Kaptan.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Denizin Oğlu çok konuşuyor. Bıyıklı bir koca karı gibi görünüyor.";
			link.l1 = "Kim? Açıkla bana bunu, Kakao Yaprağı. Ben de beyaz tenliyim, ama benden beyaz tenlilerle savaşmak için silah istiyorsun. Bu çelişkili değil mi? Neden bana geliyorsun?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "O garip kıyafetli Kızılderiliyle konuşmanı duydum. Diğer beyazlardan farklısın. Tichingitu'yu anlıyorsun. Ve eminim Kakao Yaprağı'nı da anlıyorsun.";
			link.l1 = "Ah... Silahlar için ne teklif edeceksin, Kakao Yaprağı?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Tanrıların gözyaşları. Siz onlara inci diyorsunuz. Birçok inci.";
			link.l1 = "Kararımı verdim, Kakao Yaprağı. Burada bekle, silah tüccarına gidiyorum. İhtiyacım olanları alıp döneceğim.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Kararımı verdim, Kakao Yaprağı. İhtiyacın olan şey zaten bende var. Al bakalım.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Kararımı verdim, Kakao Yaprağı. Gereksiz belaya bulaşmak istemiyorum. Benden silah alamazsın. Yoluna devam et.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Vay canına! Deniz Oğlu'nun bir tüfeği mi var? Bir tüfek için ağır bir bedel ödeyeceksin!";
			link.l1 = "Hayır, ama gemimin topları iş görür mü? Şimdi git, Kakao Yaprağı, yoksa yakalanıp tutuklanacağız.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "İyi anlaşma! Denizin Oğlu, eğer ormana gideceksen yanında bir ateşli silah bulundur. Bir Kızılderiliyle karşılaşırsan, pazarlık yap.";
			link.l1 = "Bunu unutmayacağım. Hoşça kal, Kakao Yaprağı.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Kakao Yaprağı bekleyecek.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, burada yerliler toplanmış anlaşılan!\nTekrar hapse dönmek mi istiyorsun, köpek?\nBurada ne yapıyorsunuz, Mösyö?";
			}
			else
			{
				dialog.text = "Dur! Burada ne yapıyorsunuz, Mösyö?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hey, pislik, bu saygın vatandaşı mı bekliyordun?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Tüm soluk yüzler bana aynı görünüyor. Ama bunu hiç görmedim. Sen, savaşçı, ne yapman gerekiyorsa yap. Bu iş artık yorucu olmaya başladı. Kakao Yaprağı, ormanın ruhlarıyla yüzleşmeye hazır.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Seni bekleyen cehennem, ormanın ruhları değil.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Kaptan, gidebilirsiniz. Yolumdan çekilin. Şehri korumak ciddi bir iştir.";
			link.l1 = "Anladım... Peki ya bu Hintli?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Yerlilerle ne işin var, Mösyö? Gerçi... evet, Avrupa'dan yeni geldin\nParis nasıl? Hâlâ şehirdeki fareleri eziyorlar mı, yoksa artık onları da komünyona mı davet ediyorlar? Bak, burada fare yerine yerlilerimiz var. Korsanlarla ticaret yaparlar, odunculara saldırırlar, insan yerler, lanet olsun\nÜç gün önce bir akıllı tüfeğini bunlardan birine satmış. Sonra ne oldu dersin? O alçaklar devriyedeki bütün askerleri öldürdü, üstelik devriyeye komuta eden de benim dostum ve silah arkadaşımdı. Hain sömürgeciyi bulduk, ibret olsun diye güneşte sallandırdık. Yerlilere ateşli silah vermek! Bu ihanettir! Fransa'ya ihanettir! O renkli maymunu bir süredir izliyoruz, çünkü artık her yerde karşımıza çıkıyor\nŞimdi ise hak ettiği hızlı sonla buluşacak. Devam edebilirsin, Kaptan. Seni ilgilendirmeyen işlere karışma. Bu savaşın bir parçası değilsin... Henüz... Yoksa öyle misin?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Güvenilir) Bakın, memur... Ben Kaptan Charles de Maure, Moskof Fadey’in misafiriyim. Bu Hintliyle ilgili bazı çıkarlarımız var... o yüzden birbirimizin işine karışmayalım. Anlaştık mı, Teğmen?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Yenilere karşı tutumlar, yerlilere karşı tutumlar... Kolonistler, yerliler... Bunların hepsini henüz tam anlamış değilim ama şu anda, Teğmen, kıyaslama senin lehine değil... Savaşa!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Haklısınız, Teğmen, değilim. Hoşça kalın.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Öhöm! Anlaşıldı, Kaptan. Lütfen saygılarımı Mösyö Fadey'e iletin. Takım, devriye görevine devam edin!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Eyvah!";
			link.l1 = "Evet, doğrusu, bunun işe yaradığına ben bile şaşırdım. İşte malların, Kakao Yaprağı.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Denizin Oğlu güzel konuşuyor. Bir Kızılderili’yi kurtarmak hiç de kolay bir iş değil! Büyük bir ödül seni bekliyor!";
			link.l1 = "Vay canına, bu epey ganimet... Ve içinde delik olan bir taş, bir de tuhaf bir muska.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Denizin Oğlu'nun bir tüfeği var mı? Bir tüfek için yüksek bir bedel öde!";
			link.l1 = "Hayır, ama gemimin topu işini görür mü? Şimdi git, Kakao Yaprağı, yoksa yakalanıp tutuklanacağız.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "İyi anlaşma! Deniz Oğlu, eğer ormana gidersen yanına bir ateşli silah al. Bir Kızılderiliyle karşılaşırsan, pazarlık yap.";
			link.l1 = "Bunu unutmayacağım. Hoşça kal, Kakao Yaprağı.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Vay canına! Kötü bir karar verdin, Deniz'in Oğlu. Neden böyle bir şey yaptın?";
			link.l1 = "Ugh... Beş dakika önce her şey doğru geliyordu... Şimdi artık emin değilim... Sonuçta kendi adamımı öldürdüm. Şimdi ne yapacağım? Ya öğrenirlerse? Kahretsin! Kahretsin!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Şimdi bir baskın olacak. Askerler herkesi öldürecek. İki devriye affetmez. Kakao Yaprağı kaç. Ve sen, Denizin Oğlu... neden. Kakao Yaprağı zaten ölecek. Ruhlar böyle istiyor.";
			link.l1 = "Ah... Anlaşmamız hâlâ geçerli mi?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Kötü bir karar, Denizin Oğlu. Ama teşekkür ederim. Büyük bir ödül.";
			link.l1 = "O kadar da büyük değil, her şey düşünüldüğünde...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Denizin oğlu, eğer sağ kalırsan ve sonra ormana gidersen, yanına bir ateşli silah al. Bir Kızılderiliyle karşılaşırsan, pazarlık yap.";
			link.l1 = "Bunu gelecekte aklımda tutacağım. Hoşça kal, Kakao Yaprağı.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Selamlar, Kaptan Charles de Maure. Benim adım Charles Barbier. Zamanınızdan bir dakikanızı alabilir miyim?";
			link.l1 = "Kaptan de Maure... Evet, o benim! Lütfen devam edin, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Bir meslektaşımla, hele ki adımı paylaştığım biriyle tanışmak her zaman bir zevktir! Size bir teklifim var, Kaptan. Görüyorsunuz, St. Pierre'e kadar bana eşlik edecek birine ihtiyacım var ve...";
			link.l1 = "St. Pierre'i biliyorum! Ama orası sadece iki günlük yol! Ve itiraf etmeliyim ki, refakatçilikte hâlâ acemiyim. Bu geminin komutasını daha bir hafta önce devraldım.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Dürüstlüğünüz için minnettarım, Kaptan. Charles, samimiyetimi mazur gör, ama tam da ihtiyacım olan kişi sensin.";
			link.l1 = "Hmm... Kısa bir süre önce buna benzer bir teklif almıştım. Sonu Le François yakınlarında bir korsan pususuyla bitti.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Bu olayı duydum, bu yüzden seni aradım\nÖncelikle, oldukça değerli bir yük taşıyorum ve her zaman birileri pusuda bekler. Ancak, Le Francois yakınlarındaki o korsanlara karşı kazandığın zafer, oradaki serserileri caydıracaktır\nİkinci olarak, Fadey Muskovit ile olan bağlantın senin için güçlü bir referans.";
			link.l1 = "İkna edici bir gerekçe, Mösyö. Peki, bu iyilik karşılığında ne tür bir karşılık öneriyorsunuz?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Bu bir iyilik değil, Kaptan, karşılıklı fayda sağlayacak bir iş! Beni zamanında St. Pierre'e götürmeniz karşılığında size kırk altın ödeyeceğim.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Güvenilir) Zıt yöne gidiyorum, Mösyö, bu yüzden ödemeyi peşin almam gerekecek.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Kötü bir teklif değil - zaten o tarafa gidiyorum. Anlaştık!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Kıymetli bir yük mü dediniz? Ne yazık ki, Mösyö, şimdilik maceralardan fazlasıyla nasibimi aldım.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Böylesine ciddi bir genç adama hayır demek zor, Kaptan. Alın, kırk dublonunuz burada. Hiç vakit kaybetmeden yelken açalım mı? Zaman paradır.";
			link.l1 = "Fazla oyalanmayacağız, Mösyö. Kısa süre içinde yelken açacağız.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Mükemmel! Hemen yola çıkmaya hazırlanacağım!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Anladım, Kaptan. Rahatsız etmeyeceğim. Hoşça kalın, iyi günler.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Örnek teşkil eden refakatiniz için teşekkür ederim, Kaptan. Hiçbir sorunla karşılaşmamış olmamız beni memnun etti.";
				link.l1 = "Sizinle iş yapmak bir zevkti, Mösyö. Şimdi, müsaadenizle, ilgilenmem gereken çok şey var.";
			}
			else
			{	
				dialog.text = "Örnek teşkil eden refakatiniz için teşekkür ederim, Kaptan. Hiçbir sorunla karşılaşmamış olmamız beni memnun etti. İşte ödemeniz – tam kırk doblon.";
				link.l1 = "Sizinle iş yapmak bir zevkti, Mösyö. Şimdi, müsaadenizle, ilgilenmem gereken çok iş var.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Evet, Charles? Sanki canın sıkkın. Bir sorun mu var?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Şimdi, sen güvenilir birisin ve Fadey’le de tanışıyorsun... Bak, ticaret dediğin iş risklidir, değil mi?";
			link.l1 = "Eğer öyle diyorsan.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Guadeloupe'da... sen bilirsin kimden, ucuza bir parti halat aldım. Hemen St. Pierre'de satıp, kazancımla Willemstad'da satmak için kahve alacaktım. Kulağa mantıklı geliyordu.";
			link.l1 = "Dürüstlüğünüzden şüphe etmiyorum, Mösyö, fakat anlattıklarınız kulağa pek güvenilir gelmiyor. Yükünüzden altınmış gibi bahsediyorsunuz. Oysa benim gemim bu halatlar ile dolu ve bunlar sudan ucuz.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, bu halatlar en kaliteli kenevirden yapılmış, Moskova Çarı'nın fabrikalarında dokunmuş. Savaş gemilerinin donanımında kullanılan ve stratejik öneme sahip halatlardır. İngilizler, Moskova ile olan ticaret yollarını tekellerine alıp bu tür halatların serbest ticaretini yasaklıyor. Diğer ülkeler de Avrupa’daki tersanelerine bu halatları sağlamak için kıyasıya rekabet ediyor.";
			link.l1 = "Yani, bu mu kaçakçılık dedikleri?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Teşekkür ederim, ama kaçakçılık ilgimi çekmiyor.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Yazık! Dürüst ticaret sana güzel bir kazanç getirebilir, ama asla büyük bir servet biriktiremezsin. Yine de, bu biraz tehlikeli konuşmayı seninle sebepsiz başlatmadım. Sana bir parti halat satmayı teklif ediyorum. Yerel kaçakçılar sık sık bu hana uğrar, bu yükü de memnuniyetle alırlar. Bir düşün! Bugün denize açılmadan hatırı sayılır bir kâr elde edeceksin.";
			link.l1 = "Yük için ne kadar istiyorsun?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "On bin peso. Mütevazı bir meblağ, ama halatları kaçakçılara satarsak hatırı sayılır bir kazanç elde ederiz.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Böyle bir fırsatı kaçırırsam kendimi asla affetmem. Gümüşü al ve malların hemen gemime teslim edilmesini sağla.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Bu iş oldukça riskli, dostum. Biraz orta yol bulalım, ne dersin? Halatlarını yedi bin karşılığında kabul edeceğim.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "Bu oldukça yüklü bir meblağ, Mösyö. Durumunuza üzülüyorum, fakat böyle bir riski kabul edemem.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Teşekkür ederim, Charles! Beni maddi felaketten kurtardın! Mallar hemen ve en büyük özenle yola çıkacak\nBir tüccar olarak sana bir tavsiye vermeme izin ver: İyi bir kambiyeci tuttuktan sonra, Saint-Pierre'den kahve al ve Willemstad'da kârla sat. Buradaki şehirler koloni mallarına iyi para öder, sonra da onları Avrupa'ya gönderip büyük kazanç elde ederler. Girişimlerinde bol şanslar, dostum!";
			link.l1 = "Elveda, Mösyö.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				Notification_Skill(true, 25, SKILL_COMMERCE);
				dialog.text = " Minnettarım, Charles! Beni maddi felaketten kurtardın! Mallar hemen ve en büyük özenle gönderilecek\nBir tüccar olarak sana bir tavsiye vermeme izin ver: İyi bir veznedar tuttuktan sonra, Saint-Pierre'den kahve al ve Willemstad'da kârla sat. Buradaki zenginler koloni mallarına iyi para öder, sonra da onları Avrupa'ya gönderip büyük kazanç elde ederler. İşlerinde bol şanslar, dostum!";
				link.l1 = "Elveda, Mösyö.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				Notification_Skill(false, 25, SKILL_COMMERCE);
				dialog.text = "Yapamam, Kaptan. Mallarım ciddi ve ciddi bir yaklaşım gerektiriyor. Çoğu özgür kaptan stratejik mallarla ticaret yapmaya cesaret edemez. Ne yazık ki, burada pazarlık etmek yersiz.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Böyle bir fırsatı kaçırırsam kendimi asla affetmem. Gümüşü al ve malların hemen gemime teslim edilmesini sağla.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "Bu oldukça yüklü bir meblağ, Mösyö. Durumunuza üzülüyorum, ancak böyle bir riski kabul edemem.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Ne yazık! Elveda, Kaptan.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Başımız dertte, Kaptan.";
			link.l1 = "Peki?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Navigatörümüz tutuklanıp yerel zindana götürülmüş. Borç meselesiymiş, öyle diyorlar.";
			link.l1 = "Yine mi?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "O tam bir baş belası, Kaptan.";
			link.l1 = "Ne kötü bir zamanlama! Dümencimiz olmadan burada mahsur kaldık. Yine onu kurtarmam gerekecek! Komutanla konuşacağım...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Konuşmama izin var mı, Kaptan?";
			link.l1 = "Devam et.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Tüm bu zahmete neden giriyoruz? Onun gibi bir adam gemiye sadece bela getirir.";
			link.l1 = "Seçeneğim var mı? Zaten başka dümenci yok denecek kadar az, yani seçeneklerim oldukça kısıtlı.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Doğru, iyi bir dümenci bulmak kolay değil, ama henüz usta birine ihtiyacın yok, işini bilen biri yeterli. Geçen hafta içinde durumun değişti, bunun farkındasın, değil mi? Artık tayfa bulmak için en diptekileri toplamana gerek yok. İnsanlar şimdi o korsanı nasıl alt ettiğinden ve sahip olduğun bağlantılardan bahsediyor. Tayfa da arkanda, Kaptan, seni seviyoruz.";
			link.l1 = "İçimi rahatlattın, Alonso. Peki, tayfanın Deluc hakkındaki düşüncesi ne?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "You learn quickly, Cap’n. The crew says that while he is a capable officer and treats us fair, he is not worth the bother. A big merchantman just let its officers go—perhaps look in the tavern? The right fellow is bound to be there. And forget Deluc; that’s the word among the men.";
			link.l1 = "Teşekkür ederim tavsiyen için, Alonso. Sana güvenebileceğimi biliyordum. Şimdi gemiye dön ve ben bunu hallederken nöbeti devral.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Aye-aye!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Alonso_DlgExit");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Kapt...";
			link.l1 = "Soracak milyonlarca sorum var ama sadece birini soracağım: Bunca zamandır yanımda olup bana denizcilik öğretirken nasıl yeni borçlar biriktirmeyi başardın!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Bunu itiraf etmekten utanıyorum Kaptan, ama ekibinize katılmadan çok önce çeşitli tefecilerden borç alıyordum. Planım, ortadan kaybolup geminizde çalışarak tüm borçlarımı ödeyecek kadar para kazanmaktı. Ama burada, St. Pierre'de bir kadınla ilişkiye girme hatasını yaptım ve askerler beni onun gözünün önünde yakaladı. Martinik'te yeni bir borç yapmadım, çünkü son borcumu siz ödediniz, yemin ederim!";
			link.l1 = "Sen tam bir aptalsın, Deluc, ve beni St. Pierre'in maskarası yaptın!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Etkileyici, Folke. Anı için teşekkürler.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Ne yapacaksın, Kaptan? Beni yine kurtarabilecek misin? Yeni bir seyirci bulmak kolay olmayacak, biliyorsun...";
			link.l1 = "Şimdilik burada kal. Bir karar vereceğim. Belki bankacıya tekrar uğrarım.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Ne yapacaksın, Kaptan? Beni yine kurtarabilecek misin? Yeni bir rotacı bulmak o kadar kolay olmayacak, biliyorsun...";
			link.l1 = "Şimdilik yerinde kal. Bir karar vereceğim. Belki bankacıya tekrar uğrarım.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = " Gidecek bir yerim yok ki... ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Folke_DlgExit_1");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Kaptan, teşekkür ederim. Borçlarımı ödediniz ama şimdi size daha da büyük bir borçluyum – hayatımı. Bunun için gerçekten minnettarım! Emin olun, bu dünyada benden daha sadık birini bulamazsınız!";
			link.l1 = "Bazı borçlar, ancak yenilerini üstlenerek ödenebiliyor sanırım. Hadi işimize dönelim, Folke. Denizde yapılacak çok iş var.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Bunu unutma, Deluc. Bir dahaki sefere seni vururum.";
			link.l2.go = "Del_Folke_11b";
			Del_Ohrannik();
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Baş üstüne, Kaptan!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			AddDialogExitQuestFunction("Del_Folke_DlgExit_2");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Bir subaya ihtiyacınız var mı, kaptan?";
    		Link.l1 = "Bir subay mı? Peki, hangi konuda iyisin?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Hayır, bende tam takım var.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Bu sularda en iyi kılavuz benim. Biraz tıptan da anlarım. Sana bir iyilik yapmaya ve emrinde çalışmaya hazırım.";
			Link.l1 = "Ne kadar istiyorsun?";
			Link.l1.go = "Del_price";
			Link.l2 = "Sen ne tür bir uzmansın?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Ne yazık ki, zaten bir dümencim var.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Bence 4.000 peso üzerinde anlaşabiliriz.";
			Link.l1 = "Bu biraz fazla değil mi?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Katılıyorum. Artık tayfanın bir parçasısın.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Bu parayı hak etmiyorsun.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Fikrini değiştirdin mi, kaptan? Yeni bir seyirciye hayır demezsin herhalde?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Öyle bir şey.   Ne kadar istiyorsun?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "Ve sen neler yapabilirsin?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Tam takımım var. Görüşürüz.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Pekala... Sanırım 2500 peso konusunda anlaşabiliriz. Ne dersin?";
				Link.l1 = "Şimdi oldu. Katıldın.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Üzgünüm kaptan, ama tam olarak istediğim kadar ederim. Eğer bu sana fazla geliyorsa, başka birini bulabilirsin.";
				Link.l1 = "Pekâlâ, kabul ediyorum. Seni götüreceğim.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Bunu yapacağım. Hoşça kal.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Teşekkür ederim, kaptan. Seçiminizden pişman olmayacaksınız.";
					Link.l1 = "Umarım öyle.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Paranız az görünüyor, kaptan! Üzgünüm ama veresiye çalışmıyorum.";
					Link.l1 = "Vay canına!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Teşekkür ederim, kaptan. Seçiminizden pişman olmayacaksınız.";
					Link.l1 = "Umarım öyle olur.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Paranız az görünüyor, kaptan! Üzgünüm, ama veresiye çalışmam.";
					Link.l1 = "Vay şeytan!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "İçkimi bitireceğim kaptan, sonra gemiye geçerim. Merak etmeyin, zamanında orada olacağım.";
			Link.l1 = "Pekala. Geç kalırsan, güverteyi sana temizletirim!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			DialogExit();
			AddDialogExitQuestFunction("Del_shturman_DlgExit");
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Peki, peki! Teslim oluyorum, kahretsin!";
			link.l1 = "Artık benim tutsağımsın, ama yakında kendini St Pierre'de darağacının önünde bulacaksın.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Demek burası...   Beni nereden bulacağını nasıl bildin?";
			link.l1 = "Vali durumu bana bizzat anlattı.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Ne alçak herif! Planlarımı sezmiş olmalı ve diğer tayfalara ibret olsun diye ininin önünde beni açıkça rezil etmeye karar vermiş!";
			link.l1 = "Ekselanslarına bir hakaret daha ederseniz, St. Pierre'e yolculuğunuz hızlı ve unutulmaz olacak.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Ha? Senden bahsetmiyorum, dostum. Ben İyi Adam Jacques'tan bahsediyorum.\nLanet olsun, söylentiler doğruymuş! Barbazon benim tehdit olmaya başladığımı fark etti ve beni ortadan kaldırmak için valiye teslim etti. Bu yüzden yerimi tam olarak biliyordun ve beni gafil avladın, ha ha!";
			link.l1 = "Sen hayal görüyorsun. Martinique Valisi bir korsan lideriyle iş birliği yapacak kadar alçalmaz!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Evet, tabii. Belki doğrudan değil ama bence Barbazon'la bir anlaşma yaptı. Onun için çok uygun: tehlikeli bir korsan asılıyor, raporlar düzgün görünüyor ve 'askeri operasyon masrafları' da haklı çıkıyor. Ben askerlik yaptım, biliyor musun? O yüzden orada işlerin nasıl yürüdüğünü bilirim. Ya sen? Garnizonda mı görev yapıyorsun?";
			link.l1 = "Ülkeme hizmet ediyorum, ve bu konuşma burada bitiyor. Hücreye hoş geldiniz.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Dur bir dakika, dostum. Ben Kastilyalı değilim ve bugün Fransız tüccarları soymak için denizde değildim. Bir prensibim var, kahretsin! Hadi bir anlaşma yapalım, ne dersin?";
			link.l1 = "Boşuna konuşuyorsun, korsan. Seni hücreye atın.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "İpi boynundan uzak tutmaya mı çalışıyorsun?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Burada sağlam bir ipucum vardı, beni bırakırsan seni de işin içine katarım. Hayatımın değeri birkaç bin gümüşten fazla değil ama sana bundan çok daha fazlasını kazandırabilirim – hem de vergisiz.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "Teklifin cazip... Ama korsanlık pek bana göre değil.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Ben korsan değilim!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Karar senin. Şansını denemek isteyen bir adam mı olacaksın, yoksa prensiplerine bağlı, beş parasız bir kaptan mı? Gerçek para ve özgürlük istiyorsan, her işten biraz anlaman gerekecek. Karşına çıkan her fırsatı değerlendir.";
			link.l1 = "Gerçekten de sözlerinle insanı etkiliyorsun...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Öhöm... Sanırım seni St. Pierre'e götüreceğim. Sanırım bu en doğru olanı.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "O zaman cehenneme git!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Peki, anlaştık mı?";
			link.l1 = "Evet. Liderinin kim olduğunu söyle, gidebilirsin.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Henry adlı bir barkta zeki bir İngiliz var. Küçük ticaret yolculuğunu bitirmek üzere; Fransız plantasyonlarından malları Willemstad'a taşıyıp güzel bir kâr elde ediyor. Yakında Martinique'ten Curaçao'ya gidecek. Kolay bir iş bu – koruması yok, bark değerli eşyalarla dolu ama savunması zayıf. Çok oyalanıyor, bu yüzden dedikodular yayılıyor. Benim tavsiyem, dostum? Meyhanede çekingen olma. Yerel halka birkaç içki ısmarla, sırlarını dökerler.";
			link.l1 = "Neden koruma yok?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Bir İngiliz Curaçao'da işini başka nasıl sessizce yürütebilir ki? İngiltere ile Hollanda arasında açık savaş var, ticaret ruhsatı almak da hem zahmetli hem pahalı.";
			link.l1 = "Fakat Fransa ile İngiltere arasında savaş yok. Tarafsız bir gemiye saldırırsam ne olur?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Eğer dikkatli olursan, hiçbiri. Mürettebat en yakın limanda kahramanlıklarını ballandıra ballandıra anlatacaktır, ama İngiliz ya da Hollanda gemilerine sürekli dadanmadığın sürece sorun olmaz. Henry'ye Fransız bayrağıyla yaklaş. Toplarına saçma doldur, mesafeyi kapat, Kara Bayrağı çek, birkaç salvo ateşle ve o gemiye çık. Bu kadar basit, dostum.";
			link.l1 = "Bunu göreceğiz. Sözümde duracağım ve seni serbest bırakacağım. Pişman olmam için bana bir sebep verme.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Yapmam. İyi avlar, dostum.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Kumar sorununu ben hallederim. Hey! Kendine gel, adamım! Ya toparlan, ya da aklını başına ben getiririm.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Bayım, affedersiniz ama biraz rahatsızlık veriyorsunuz.";
			link.l1 = "Evet, elbette. İyi günler dilerim, beyler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Kaptan de Maure! Bekleyin!";
			link.l1 = "Evet, Teğmen?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Sana yetişmekte zorlandım. Ufak bir aksilik oldu, Kaptan. Ne karmaşa!";
			link.l1 = "Derin bir nefes al ve lütfen sakin ol.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Tamam, tamam. Dinle, topları yükledikten sonra ambarda hâlâ yer var mı?";
			link.l1 = "Ben de bu işte yeniyim, o yüzden tam emin değilim ama sanırım olması gerekiyor.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Mükemmel! Komutanlık, Porto Bello’daki harekâtı her şekilde desteklemek istiyor, bu yüzden Savaşçı’ya iki yüz varil barut daha gönderilmesini emrettiler. Az gibi görünebilir ama birkaç ek salvo savaşın gidişatını değiştirebilir!";
			link.l1 = "Pekâlâ, Teğmen. Ben de üzerime düşeni yapmaya hazırım. Barutu yükleyin – hiç sorun değil.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Teşekkür ederim, Kaptan. Hemen yükleme ekibimize haber vereceğim. Neyse ki, henüz işi bitirmediler "+PChar.Ship.Name+" henüz değil. Görevinde bol şans!";
			link.l1 = "Teşekkürler, gerçi şimdiye kadar oldukça karmaşık geçti. Hoşça kal, Teğmen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "İsa aşkına, Kaptan! Neyse ki sağ salim çıktınız, şükürler olsun!";
			link.l1 = "Ne oldu böyle?! Gemime ne olmuş?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Bilmiyorum, Kaptan! Sadece son zamanlarda tanıştığım bir yerli kadına veda ediyordum... Aman Tanrım! Eugénie!";
			link.l1 = "Öldü, "+npchar.name+". Üzgünüm, ama odaklanmamız ve mürettebatımızdan birinin zarar görüp görmediğine bakmamız gerekiyor.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Birbirimizi zar zor tanıyorduk... Aaah! Kahretsin! Rapor ediyorum Kaptan: Patlama olduğunda tayfanın çoğu karadaydı - neyse ki. Çocuklar bir sonraki büyük seferimizden önce biraz izin yapıyorlardı. Ama gemide nöbet tutanlar... Korkarım hiç kurtulan yok. Şuraya bir bakın! Enkaz burada, bu iskelede bile insanları yaraladı ya da öldürdü! İkimizin sağ kalması tam bir mucize.";
			link.l1 = "Ya gemi ne olacak? O iyi mi?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Öyle mi?! Özür dilerim, Kaptan. Emin olmak zor, ama patlamanın alt güvertede değil, üst güvertede olduğunu düşünüyorum. Aktif bir yangın görünmüyor, büyük bir hasardan da kurtulmuş gibiyiz.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "Ne oluyor böyle, Kaptan?!";
			link.l1 = "Ben de aynı şeyi soruyorum, Albay!";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Kendine dikkat et, de Maure! Bu işi Donanma’dan sen kabul ettin, ağır topları aldın – bunlar Taç’a ait, stratejik önemi olan silahlar! Bu topların tüm operasyon için ne kadar önemli olduğunu anlıyor musun?! İhmalkarlığın yüzünden neredeyse dört yüz adam ve bir Fransız savaş gemisi tehlikeye girdi! Burada vatana ihanetten yargılanacaksın!";
			link.l1 = "Sakin olun, Albay! Mucize eseri, gemim sağ çıktı ve sizin değerli yükünüz de büyük ölçüde sağlam... büyük ölçüde.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Ne demek, çoğunlukla?!";
			link.l1 = "Son anda teğmenlerinizden biri tarafından yüklenen iki yüz varil barutun zarar görmediğine dair garanti veremem. Onlar en son yüklenmesi gerekenlerdi ve muhtemelen patlayanlar da onlardı.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Bu da ne saçmalık Charles? Hangi teğmen? Hangi barut? Ben böyle bir emir vermedim!";
			link.l1 = "Bu teğmen herhalde senin garnizonundandı. Adını sormadım ama operasyondan haberdar gibiydi.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ah, kahretsin! Görünen o ki, Kastilyalılar da kirli oynamaya niyetli... Bu talihsiz durumu ben hallederim, Kaptan. Ama senin hâlâ yapacak bir işin var: Geminin denize açılmaya hazır olduğundan emin misin?";
			link.l1 = "Su üstünde, ama kesinlikle ciddi bir onarıma ihtiyacı var.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Buna vaktimiz yok, Kaptan. Hemen yelken açın ve görevi tamamlayın. Beklemek için risk çok büyük.";
			link.l1 = "Tanrı aşkına, en azından bir günümüz olamaz mı? Yerel tersane gerekli onarımları yapabilir! Peki ya mürettebatım?! Kesinlikle yaralılar vardır!";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Fark etmediyseniz, tersane şu anda yanıyor. Yangının kasıtlı mı çıktığını yoksa patlamanın bir sonucu mu olduğunu henüz bilmiyoruz. Size sadece şunu garanti edebilirim: Yaralılarınız tedavi edilecek ve ölenlerin defnedilme masraflarını taç karşılayacak.";
			link.l1 = "Ciddi misin? Sunabileceğin en iyisi bu mu?";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Kaptan, Fransa'nın acilen yardımınıza ihtiyacı var. Size kereste sağlayacağım ve işinizi düzgün yaparsanız, Jamaika'ya vardığınızda geminiz neredeyse tamamen onarılmış olacak.";
			link.l1 = "Affedersiniz, ama hangi tahtalar? Ve neden Jamaika?";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Mürettebatın, denizde acil onarımlar için kalasları kullanabilir - bunlar başlıca onarım malzemesidir. Ayrıca Jamaika, Porto Bello'ya giden rotalardan birine oldukça yakın. Zaman kaybetmezsen, orada onarımları tamamlayıp tam kadro bir mürettebat toplayabilirsin.";
			link.l1 = "Pekâlâ, o zaman. Hemen yola çıkıyorum, Albay.";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Neden bu acele, canım?";
			link.l1 = "Sevgilim, şu anda bununla uğraşacak vaktim yok. Ne olup bittiğini görmüyor musun?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Ah, şu anki sıkıntılar büyük, ama eline bakınca ufukta daha fazlasının yaklaştığını görebiliyorum.";
			link.l1 = "Bunu eldivenli elimden bile bakmadan herkes anlayabilir. Peki, oyuna katılıyorum: bugünlerde felaketi önlemenin bedeli nedir?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Öyle bir gücüm yok, yakışıklı. Olsaydı bile, karşılayamazdım. Ama yine de sana yardım edebilirim... geminle ilgili. Kızcağızın hali perişan, canım.";
			link.l1 = "Sizin çingene tayfasının marangozlukta hırsı olduğunu hiç duymamıştım.";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Sen de pek marangoz sayılmazsın, canım. Sence sadece tahtalarla gemi onarılır mı? Usta bir marangozun yoksa, o tahtalar sadece yük olur sana...";
			link.l1 = "Yoksa?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Yerel halkın kutsal saydığı güçlü bir tılsım var. Ahşap onun isteğine boyun eğer, marangozluktan anlamayanlar bile onu takınca usta kesilir. Sadece bin peso karşılığında senin olabilir, sevgili dostum.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Pekala, anlaştık. Elimden gelen her yardıma ihtiyacım var.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Senin büyücülük numaralarına ayıracak vaktim yok. Huzur içinde git, cadı, ve işime karışma.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("You have received Amulet 'Teredo'");
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, sen. Ben bu şehrin kanunlara saygılı bir vatandaşıyım. Senden ricam, bir haydut gibi kılıcını açıkta taşımaman.","Beyefendi, lütfen, yasa açık: şehir surlarının içinde kimse silahını çekerek dolaşamaz.");
			link.l1 = LinkRandPhrase("Pekala.","Pekâlâ.","Nasıl istersen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
