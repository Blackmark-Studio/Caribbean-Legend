// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Belize civarında ve kasabanın içinde faaliyet gösteren bir hırsız ve haydut çetesi duyduğuma göre buralarda dolaşıyormuş.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Sana çete hakkında bilgi verebilirim.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Çetenin durumu nedir? Onları mağarada yakaladınız mı?";
				link.l1.go = "caleuche_7";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Tüm kasaba bir korsanın yakalanmasını kutluyor gibi görünüyor. Bana bununla ilgili daha fazla bilgi verebilir misiniz?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Memnuniyetle! Bu sıradan bir korsan değil - o alçak Matthew Lutter.";
			link.l1 = "Herkesin şansı eninde sonunda tükenir.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Sen İngiliz değilsin ve bir tüccara da benzemiyorsun, bu yüzden heyecanlanmamana şaşmıyorum. Lutter yıllardır bu sularda terör estiriyor, hem bize hem de İspanyollara saldırıyor, ama en çok da bize. Hep kıyı devriyelerimizden kaçmayı başardı, Seagull adındaki korvetiyle — bir zamanlar Takımadalar'ın en hızlı gemisiydi. Böyle bir savaş gemisinin başına nasıl geçti, onu yalnızca Tanrı bilir.";
			link.l1 = "Yani, gerçekten bir tüccara mı yenilmiş? Hem de bir korvette? Kulağa inanılmaz geliyor.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Kulağa tuhaf gelse de, bu doğru. Hem de bir tüccar, üstelik bir İspanyol! Donanmamız ondan bir şeyler öğrenebilir. Kaptan Sotta, kaçış olmadığını anlayınca savaşa hazırlandı...";
			link.l1 = "Bu Sotta, gerçekten alışılmadık bir karakter.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Belki. Gemisini olabildiğince fazla yük taşımak için yeniden donattı, bu da kaçışı imkânsız hale getirdi. Korsanların yükünün peşinde olduğunu bildiği için sürükleniyormuş gibi yaptı. Ve sonra...";
			link.l1 = "...yelkenleri tam zamanında kaldırdı mı?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! Hayır, Lutter yaklaşırken ona tam yakından bir saçma yaylımı ateşledi, sonra da korsanın gemisine bizzat çıktı! Lutter’ın kim olduğunu öğrenince de onu bize teslim etti. Gerçek bir kahraman, onurlu bir adam!";
			link.l1 = "Onu harekete geçiren sadece onur değildi - Rüzgâr Torbası'nı yakalamanın bir ödülü olmalıydı.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Bazen kâr iyi niyetle örtüşür. Ama evet, kendisine cömertçe ödül verildi. Majesteleri, şehrimizin minnettarlığının bir göstergesi olarak yelken açmadan önce ona değerli mallar yükledi.";
			link.l1 = "Keşke onunla tanışsaydım - elini sıkmak isterdim. Anlat bakalım...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Kaynağınız doğruyu söylüyordu. Bu haydutlar bizim için gerçekten büyük bir baş belası oldular. Onlar hakkında bize anlatmak istediğiniz bir şey var mı?";
			link.l1 = "Bunun dışında benden önemli bir şeyi çaldılar - başka bir şey yok. Onlar hakkında bana bir şey söyleyebileceğini ummuştum. Belki içlerinden biri yakalanmış ve şimdi ifade vermeye hazırdır...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Sizi hayal kırıklığına uğrattığım için üzgünüm kaptan, ama onlar hakkında hiçbir bilgim yok. Bildiğim tek şey, ormanda bir yerde saklandıkları ve kasabada da suç ortaklarının olduğudur, hepsi bu. Şayet onlar hakkında yeni bir şey öğrenirseniz, lütfen hemen bana bildirin.";
			link.l1 = "Pekala, memur. Bunu yapacağım.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Ciddi misiniz, kaptan? Konuşun, kulak kesildim.";
			link.l1 = "Kasabada onların muhbirlerinden birini buldum. Bana çetelerinin Chetumal koyuna varacak bir gemiye saldırmaya hazırlandığını söyledi. Haydutlar toplanıyor "+sTime+" gece, Belize'e çok da uzak olmayan bir mağaranın yakınında. Oraya gitmek için, ormandaki çatallaşmada sadece sol patikayı seçmen yeterli.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Mağarada mı? Harika haber. Bu alçaklar için hemen bir pusu kurulmasını emredeceğim. Eğer haklıysan ve muhbirin doğruyu söylüyorsa, bu herifleri yakalayacağız, sonra da valiye seni ödüllendirmesi için başvuracağım.";
			link.l1 = "Teşekkürler! İşim bitince seni görmeye geleceğim.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Pekâlâ. Sorun yok.";
			link.l1 = "Yakında görüşürüz, subay.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_BelizComendantPrison");
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Alçaklar için sıcak bir karşılama hazırladık, ha-ha-ha! Yüzlerini bir görseydiniz! Hepsini, elebaşları da dahil, yakaladık! Birkaç kişi direnmeye kalktı ama cesur askerlerimiz onlarla ilgilendi.";
				link.l1 = "Harika haber, memur! Artık Belize halkı nihayet huzur içinde uyuyabilir.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... Askerlerim bütün gece mağaranın önünde bekledi, ama kimse gelmedi. Çavuş öfkeden deliye döndü. Seni hâlâ yakalayamamış olması iyi.";
				link.l1 = "Kahretsin! Bu olamaz! Pusu kurduğunuz mağara hangisiydi? İki tane var!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Söylediğiniz yerde. Çatala vardığınızda sağdaki olanda...";
			link.l1 = "SOLDAN OLAN! Çatalın solundaki, ahmaklar!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Ama açıkça hatırlıyorum, 'sağa' dediniz.";
			link.l1 = "Aman Tanrım! Sola! Dedim ki, SO-LA! Kaçmalarına izin verdin, bu tamamen senin suçundu!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "O zaman mutlaka kendi kendine bir şeyler mırıldandın. Oldukça iyi duyarım, bilmiş ol.";
			link.l1 = "Pekala, subay, tartışmayacağım. Sana yardım etmek istedim ama kendine yardım edemeyene kimse yardım edemez. Elveda.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Çetenin ortadan kaldırılmasındaki rolünüzü valiye rapor ettim. Katkınızı çok takdir etti ve bana size bir ödül vermem için yetki verdi: nakit bir ikramiye ve bir ödül olarak bir arkebüz.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Hizmetiniz için teşekkürler, kaptan! Keşke tüm vatandaşlarımız sizin kadar vicdanlı olsaydı, suçu çoktan kökünden kazırdık! Size bol şans dilerim!";
			link.l1 = "Hoşça kalın, subay! Görevinizde bol şanslar dilerim!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
