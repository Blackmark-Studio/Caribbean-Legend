// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Biz de tam bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Aynı şeyi papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Dinle, François Gontier'i nerede bulabilirim? Çoktan Tortuga'ya varmış olması gerekiyordu.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Henri Thibaut'u arıyorum. Onu nerede bulabilirim?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Henri Thibaut'u arıyorum. Onu nerede bulabilirim?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Bana söyle, 'Santa Margarita' adında bir kalyon son zamanlarda kolonine uğradı mı? Belki bir korsan ganimeti olarak?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Bak dostum, Gaspard Parmentier'i arıyorum. Onu nerede bulabilirim?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Bana biraz yardımcı olabilir misin, dostum? Joep van der Vink adında birini arıyorum. Onu tanıyor musun?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier mi? Kim o? O isimde bir adamı tanımıyorum.";
			link.l1 = "O korvetin kaptanı '"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "En ufak bir fikrim yok. Ve o isimde bir korvet limanımıza yanaşmadı, buna kesinlikle eminim.";
			link.l1 = "Peki o zaman, son zamanlarda kasabada yabancı biri gördün mü?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Güzel soru! Burası bir liman kasabası, köy değil. Her gün yabancılar gelir geçer. Ama beş tuhaf delikanlıdan bahsedildiğini duydum, hep birlikte dolaşıyorlar ve elleri daima kılıçlarında.\nDevriye de onlar hakkında soruşturdu ama bir sonuca ulaşamadı. Ama eminim ki buraya bir korvetle gelmediler, öyle bir gemi buralarda hiç görülmedi, anladın mı?";
			link.l1 = "Hm... Peki, anladım. Teşekkür ederim, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut, Tortuga'da ünlü bir adamdır. Malikanesi liman idaresinin yakınında bulunuyor. Tavernadan çıkınca doğruca limana yönelin. Limana açılan kemere yaklaşın, kavşakta sola dönün ve sokağın sonuna kadar devam edin; orada kırmızı çatılı, iki katlı taş bir binayla karşılaşacaksınız. İşte orası Monsieur Thibaut'nun malikanesi.";
			link.l1 = "Teşekkürler! Onu ziyarete gideceğim...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut bugün çok revaçta, valinin habercisi demin buraya koşarak geldi. O da onunla ilgileniyordu. Onu bulmak bu kadar mı zor? Uzun zamandır ikinci kattaki odamı kiralıyor, oysa koca bir malikanede yaşayacak yeri var. Neye ihtiyacı var, bilmiyorum ama içeriye girdiği kadar sık dışarı çıkmıyor. Ve sadece akşamları orada oluyor.";
			link.l1 = "Belki şu anda burada.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Hayır. Akşama kadar, sekize kadar dönmeyeceğini söyledi. Onu konağında arayabilirsin ama orada bulacağını sanmıyorum. Onu denizde devriye teknesinde gördüm.";
				link.l1 = "Teşekkürler! Onu sonra görmeye uğrayacağım.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Evet. İsterseniz yukarı çıkabilirsiniz.";
				link.l1 = "Teşekkürler! Onu ziyarete gideceğim...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gemi adını hiç bilmiyorum, 'Santa Margarita' mıydı yoksa 'Kastilyalı Fahişe' mi, ama ele geçirilmiş bir İspanyol kalyonu getirdiler. Hem de bir şalopa tarafından ele geçirilmiş! İşte bu tam anlamıyla denizcilik! Kaptanı Gaius Marchais, iki gündür meyhanede böbürlenip duruyor - ilk seferi ve böyle bir ganimet!\nEvet, gerçekten kahramanca bir iş, asker olmadan kilise fareleriyle dolu bir kalyona çıkmak. Görünen o ki, o papaz bozuntuları, kendi işini kendi görenin başına neler geleceğini unutmuşlar...";
			link.l1 = "Evet, Tanrı kendi işini kendi görenlere yardım eder, bu kesinlikle bir Huguenot atasözüdür. O şanslı kaptanı nasıl görebilirim? Burada mı, Tortuga'da mı?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, kim bilir ki. Uzun zamandır onu meyhanemde görmedim. Ayılır ayılmaz ödül parasıyla parlak yeni bir gemi aldı ve güverteyi deli gibi turladı. Şimdi Marchais nerede, hiçbir fikrim yok. Belki Tortuga’dadır, belki de denizdedir.";
			link.l1 = "Peki. Hikaye için teşekkürler, dostum!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Her zaman, Mösyö. Sevgili Kaptanımıza yardımcı olmak beni her zaman mutlu eder "+pchar.name+", St. Pierre'nin kurtarıcısı! Sonra uğra!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Görünüşe göre Gaspard sizin tayfanız arasında giderek daha popüler oluyor. Evi surun yanında. Meyhaneden sola dönüp limana doğru ilerle, ama oraya gitme, tekrar sola dön, dümdüz devam et ve sonra sağa dön. İki katlı bir evdir.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Adını hiç duymadım.";
			link.l1 = "Belki de başka bir isimle tanınıyordur. Onu 'Banten' adlı brigantin kaptanı olarak duymuş olabilirsiniz?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Ben de o brig hakkında hiç duymadım.";
			link.l1 = "Onun yakın zamanda burada olduğunu duydum. Belki biraz gümüş hafızanı tazeler?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Peki, bunu nerede duyduğunu kendine sor. Ama gümüşünü almaktan da gocunmam.";
			link.l1 = "Bu sefer gümüş yok, demek. Hoşça kal.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
