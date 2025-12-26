// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının çok işi olur ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Soracağım, ama sonra. Affedin beni, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Affedersiniz, Peder, cemaatinizden bir din adamı benden Joachim Merriman'ın oda kiraladığı evi araştırmamı istedi...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Peki? Orada bulundun mu, evladım?";
			link.l1 = "Evet, buldum. Ama dürüst olmak gerekirse, keşke bulmasaydım. Üst odada dev bir baltayla saldıran bir iskeletle karşılaştım. Zorlukla da olsa galip gelmeyi başardım, ama hiç de kolay olmadı.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Tanrım, ruhlarımıza merhamet et! En kötü korkularım gerçek oldu!";
			link.l1 = "Hepsi bu değil, baba. Sonunda onu yere serdiğimde çığlık attı ve bir kadın gibi ses çıkardı. Kemiklerin arasında biraz takı buldum, bu yüzden kaybolan ev sahibesi olduğunu varsaymak yanlış olmaz.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(haç çıkarır)... Zavallı Tanrı kulu, Rabbim ruhuna huzur versin...";
			link.l1 = "Görünüşe bakılırsa Merriman gerçekten bir büyücüymüş. Birinin yaşayan bir adamı böyle bir ucubeye nasıl dönüştürebileceğini hiç aklım almıyor.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman çok korkutucu bir büyücü, evladım. Onu Avrupa'da tanıdım ama o zamanlar böyle bir şeye asla muktedir değildi. Burada, Karayipler'de, ona doğaüstü güçler kazandıran bir şeyi ele geçirmeyi başarmış.";
			link.l1 = "Merriman'ı tanıyor muydunuz, Peder?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Neden engizitörlere söylemedin?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Oğlum, kilisemizin Engizisyon'la anlaşmazlık içinde olduğunu bilmiyor musun? Ben, Peder Vincento ve onun serserilerinden uzak durmayı tercih ederim.";
			link.l1 = "Anlıyorum. Baba, Merriman'ın gücünü nereden aldığını sanırım biliyorum. Eski bir eseri ele geçirmiş; Chavin kabilesinin yerlileri tarafından tapılan ölüm tanrısı Yum Cimil'e ait yeşim bir kafatası.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman büyülü ritüeller yapması ve cesetler üzerinde deneyler gerçekleştirmesiyle tanınırdı, bu yüzden bu çok iyi mümkün olabilir. Tanrı'ya şükrediyorum ki bu korkunç adam Willemstad'dan ayrıldı ve sen de burada ekmeye çalıştığı şeytani tohumları yok ettin. Sana büyük bir minnet borçluyuz, evladım. Lütfen bu kutsanmış eşyaları ödülün olarak kabul et.";
			link.l1 = "Teşekkür ederim, Peder";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "Ama sıkıntılarımız bununla bitmedi, evladım. Yakın zamanda bir mektup aldım "+sld.name+" , Havana’daki kilisenin başrahibi. Korkunç haberler getiriyor. Küba ormanındaki bir mağarada avcılar dehşet verici yaratıklar, yürüyen ölüler görmüşler. Üstelik son zamanlarda ormana giren bazı insanlar kaybolmuş, bu da durumu daha da endişe verici kılıyor.";
			link.l1 = "Hmm... bunun da Merriman'ın işi olduğunu mu ima ediyorsun?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Ne düşüneceğimi bilmiyorum, oğlum. Ama o kara büyücü bu kadar güçlendiyse, takımadadaki herkes büyük bir tehlikede demektir. Şeytanın bu uşağının aklından ne geçtiğini yalnızca Tanrı bilir\nUmarım Baba "+sld.name+" yanlış yaptım, ama yine de - lütfen Havana'ya gidip onunla konuş. Senin için bir aylık geçerli bir ticaret ruhsatı hazırladım. Bununla Havana limanına hiçbir zorluk yaşamadan girebileceksin.";
			link.l1 = "Pekala, Peder. Havana'ya gideceğim.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Ne düşüneceğimi bilmiyorum, evladım. Ama o kara büyücü bu kadar güçlüyse, takımadaların tüm sakinleri büyük bir tehlike altında demektir. Şeytanların bu hizmetkârının ne planladığını yalnızca Tanrı bilir.\nUmarım Baba "+sld.name+" yanılmışım, ama önemli değil – senden Havana'ya gidip onunla konuşmanı istiyorum.";
			link.l1 = "Elbette, Peder. Hemen Havana'ya gideceğim.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Senin gerçekten Kilise'nin sadık bir evladı olmandan memnunum. Sağlığın ve esenliğin için gece gündüz dua edeceğim. Benim kutsamamla git. Rab, bu kutsal olmayan güçlere karşı mücadelenizde sana güç versin.";
			link.l1 = "Teşekkür ederim, hoşça kalın, Peder.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
