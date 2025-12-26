// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Genç adam, bu yaşlı Yahudiden ne istiyorsun?";
					link.l1 = "Solomon, dikkatlice düşünmeni ve geminin battığı o kayıp adayı hatırlamanı istiyorum. Orada bir hazine sakladın. Kızınla konuştum. Patronum Lucas Rodenburg, ailenin çıkarları için bana tam yetki verdi. Bana kalırsa, şu anda senin için en önemli şey ailenin sermayesini geri almak, ve benim yardımım olmadan o altının kokusunu bile alamazsın.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Ah, delikanlım, sen misin? Bana hiç mi iyi bir haberin yok? Yine mi Hristiyanlar bu zavallı yaşlı Yahudiyi sorularla bunaltmaya geldiniz?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Adayı buldum, gerçi epey zordu. Sandığını da buldum, içindeki parayla birlikte şu kafatasını da. Sanırım bu, bahsettiğin o büyükbabanın, aile reisinin kafatası.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Adayı buldum, ama hiç de kolay olmadı. Sandığını ve içindeki parayı da buldum. Ama o sandıkta hiçbir kuru kafa yoktu.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Hayır, şu anda sorum yok.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Ah, delikanlım, sen misin? Bana güzel bir haberin var mı? Yoksa yine bu zavallı yaşlı Yahudiyi sorularınla mı bunaltacaksın?";
					link.l1 = "Adayı buldum, üstelik hiç de kolay olmadı. Sandığınızdaki parayı da buldum. Buyurun.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Merhaba, genç adam. Bu yaşlı Yahudiden ne istiyorsun?";
				link.l1 = "İyi günler. Hayır, bir şey yok, sadece selam vermeye geldim.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "İyi günler, genç adam. Bir amaçla geldiğini görüyorum... Ne istiyorsun? Bundan bana bir fayda çıkacak mı, yoksa bir şeyi mi kaçırdım?";
					link.l1 = "İyi günler, Solomon. Abigail ile konuşmak istiyorum.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Merhaba, genç adam. Bu yaşlı Yahudiden ne istiyorsun?";
				link.l1 = "İyi günler, Solomon. Hiçbir şey, sadece selam vermeye geldim.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "İyi günler, genç adam. Buraya bir sebeple geldiğini görüyorum... Ne istiyorsun? Bundan bana bir fayda çıkacak mı, yoksa bir şeyi mi kaçırdım?";
					link.l1 = "Abigail ile konuşmam lazım. Ona bir mektubum var.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Merhaba, genç adam. Ne istiyorsun? Kızıma bir mektup daha mı getirdin?";
					link.l1 = "Hayır. Abigail nerede?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Oy... Paradan mı bahsediyorsun, genç adam?";
					link.l1 = "Evet, efendim. Bir adada sakladığınız parayla ilgili. Siz ve Abigail yerini hatırlayamıyor musunuz, doğru mu?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Pekala. Fluytu ve kaptanını hatırlıyorum. Hatta onu Amsterdam'da bir kez görmüştüm. Fluytun adı 'Leiden', kaptanın adı ise Toff Keller'di.";
					link.l1 = "Bu da bir başlangıç! Artık bir ipucum var.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Vay vay, bu zavallı yaşlı Yahudiden bu sefer ne istiyorsun?";
				link.l1 = "İyi günler. Hayır, bir şey yok, sadece selam vermeye geldim.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Vay vay, bu zavallı yaşlı Yahudiden şimdi ne istiyorsun?";
			link.l1 = "İyi günler. Hayır, bir şey yok, sadece selam vermeye geldim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Benden ne istiyorsun? Ben bir şey bilen bir adam gibi mi görünüyorum? Böyle Tanrı'nın unuttuğu bir günde, orada alınmaya hazır mal ve altın dolu bir arazi olacağını nereden bilebilirdim? Düşünsene, sokaklarda dolaşan bütün goyimler, benim gibi bir Yahudiyi alt etmeye ve paramı almaya çalışıyor!\nBir ada var. Orada tek bir adam yok, Abi ve benden başka. Tek bir kişi bile yok. Hiç kimse. Ortasında bir mağara vardı. Sandığımı o mağaraya sakladım, o korsan goyim Amalek'ten kurtarmak için! Altın dolu bir sandık, içinde bir tane bile ıvır zıvır yok. Hepsini Eski Ülke'den buraya kadar taşıdım! Alın terimle kazandığım her şey orada. Üstelik dedemin kafatası da... İnan bana, o şey bizi kurtardı, evet-evet\nOhoho, o eski bir tılsım, Talmudik büyüyle dolu! Tanrı bizi Amalek'ten korusun! Oy vey, bu goyim çağında her şeye yeniden başlamak çok zor! Keşke bilseydin, delikanlı! Ah, keşke bilseydin!";
			link.l1 = "Sen ne saçmalıyorsun böyle, deli misin? Kimin umurunda. Ben hallederim. Hoşça kal!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Vay, Tanrı varmış ve sen gerçek bir adammışsın! Sadece altınımı geri getirmekle kalmadın, Shneur adını da kurtardın! Ne büyük bir utancı engelledin! Mynheer Rodenburg, senin gibi kaptanlara sahip olduğu için haklı olarak gurur duyabilir. Kafatasını mynheer Rodenburg'a vereceğim, karşılığında yüklü bir ödeme sözü verdi. Sana şahsen teşekkür etmek isterim, sen harika bir shabbos goy’sun - lütfen, bu muskayı bir Yahudi'nin küçük bir teşekkür nişanesi olarak kabul et.";
			link.l1 = "Ee, sanırım teşekkür ederim.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Vallahi, Tanrı varmış ve sen gerçekten de adamın dibisin! Sadece altınımı geri getirmekle kalmadın, Shneur adını da kurtardın! Ne büyük bir utancı engelledin! Kafatasına gelince - boşver, zaten deli dangalağın tekiydi! Mynheer Rodenburg senin gibi kaptanlara sahip olduğu için gurur duymakta haklı. Sana şahsen teşekkür etmek isterim, harika bir shabbos goy’sun - lütfen, bu tılsımı hatıra olarak kabul et.";
			link.l1 = "Ee, sanırım teşekkür ederim.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Ne? Ne diyorsun, genç adam? Bu doğru mu? Bir bakayım... ";
			link.l1 = "İşte paranız. Bu para sana ve Abigail'e ait. Ama ne yazık ki, dedenizin kafatasını bulamadım.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Ah para, para, para, harika para... Hmm, ama bu benim param gibi görünmüyor... Güzelim paracığım gibi kokmuyor da. Ama neyse ki - para paradır, değil mi genç adam? Şikâyet edecek değilim. 'Bağışlanan ata dişine bakılmaz,' deriz biz! Birikimlerimi geri getirdiğin için çok teşekkür ederim. Ben de sana teşekkür etmek isterim, lütfen bu tılsımı kabul et. Şimdi git ve Abi'ye güzel haberi ver. Ben de bunu bir sayayım.";
			link.l1 = "Nice yıllara, Solomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Vay canına, dikkat et! Mynheer Rodenburg neredeyse damadım olacak. Yardım istersem garnizondaki bütün askerler bir anda burada olur!";
			link.l1 = "Sen de kimsin?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Beni dinle, kaptan. Ben onun babasıyım, Solomon. Doğru olanı yap, bana kayıp paralarımı ve onun büyükbabasının yeşim kafatasını getir. Bu yaşlı Yahudi senin kadar kurnaz olmayabilir, ama kızından bir şey istediğini bilecek kadar akıllı.\nBelki de beni tanıyan bir kaptan tarafından gönderildin. Merak etme, her şeyi Abi'ye anlatacağım. Şu an evde değil, senin gibi putperest günahkârların ruhu için dua ediyor.";
			link.l1 = "Bu söylediklerinin pek bir anlamı yoktu... Kahretsin, sen tam bir baş belâsısın. Hoşça kal, ihtiyar cimri.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Bir mektup mu? Yok artık! Dinle bak, oğlum, Bay Rodenburg neredeyse damadım olacak. Buradan tıpış tıpış gidebilirsin çünkü ben onu severim!";
			link.l1 = "Dinle, damadının kim olduğuyla hiç ilgilenmiyorum. Bu mektubu Abigail’e vermek zorundayım. Onu nerede bulabilirim? Ve sen de kimsin, şeytanın işi?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Ben kimim? Onun babasıyım, Süleyman... Ve seni hiç sevmiyorum, gavur.";
			link.l1 = "Beni sevdiğini söyleseydin, daha çok endişelenirdim. Şimdi, bana yukarıdan bakmaya devam mı edeceksin yoksa Abigail'i çağıracak mısın? Tekrar ediyorum, ben sadece bir haberciyim! Kızına bir mektup getirdim!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Bu mektubu bana ver. Kızımı bulup ona teslim edeceğim.";
			link.l1 = "Bu mektubu sana vermeden önce saçlarını keseceğim ve burnunu bükeceğim. Bu mesajı bizzat ona teslim etmem emredildi. Babası hakkında tek kelime bile duymadım ve umurumda da değil. Abigail'i nerede bulabilirim?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Ben bağırdığım anda, delikanlı, kasabadaki bütün askerler burada olur. Bu kadar inatçı olma, tüm kozlar benim elimde olduğunu görüyorsun.";
			link.l1 = "İsa, Meryem ve Yusuf aşkına! Gerçekten mi? Peki sonra ne olacak? Bir mektup teslim ettim diye beni zincire mi vuracaklar? Saçmalama!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Sen deli misin? Zavallı kızımı mektubunla ölümüne korkuttun... O İngiliz kaptanına peşinden gitmeye karar verdi! İlk bulduğu gemiyle yola çıktı! Vah vah, zavallı kızım! Şimdi bu yaşlı Yahudi ne yapacak? Hayatım mahvoldu! Bu tam bir utanç! Beni acımla baş başa bırak, ya da kalıp keyfini çıkar, umurumda değil! Ahhh zavallı Abigail’im! Saçımı kederden ağarttın, babanı mezara koydun!";
			link.l1 = "Bak hele! Demek bir an bile daha bekleyememiş. Hoşça kal, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Ne gibi görünüyor? Orada benden ve Abigail'den başka kimse yok, sadece bir ada. Sandığımı oraya sakladım, o korsan Amalek gelip almasın diye. Alın terimle, dürüstçe kazandığım her şey o sandıkta...";
			link.l1 = "Söyle bakalım, Solomon, kızının bahsettiği fluytun adını hatırlayabilir misin? Peki ya kaptanının adı neydi?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Bilemiyorum doğrusu. Bu zavallı yaşlı Yahudinin kafası, bir tencere gefilte balığı gibi allak bullak! Hem sen neden soruyorsun, delikanlı?";
			link.l1 = "Kızınıza yardım etmek istiyorum, Solomon. Hiçbir şeyin garantisini veremem, ama denemek isterim. Eski patronum ona çok kötü davrandı ve bundan sonra ona bir şekilde yardımcı olmayı kendime borç bildim.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Vay canına, eğer durum buysa...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Genç adam! Bekle!";
			link.l1 = "Evet?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Genç adam! Bana ve kızıma yaptıkların için sana teşekkür etmek isterim. Bizi kurtardın. İlk karşılaştığımızda seni soğuk karşıladığım ve yardım etme isteğine şüpheyle yaklaştığım için üzgünüm. Lütfen bu yaşlı Yahudiyi affet. Gerçekten de öteki milletler arasında kutsanmış bir adamsın. Şimdi söyle bakalım, mağarada paradan başka bir şey bulmadın mı?";
			link.l1 = "Hayır, Solomon. Orada sadece para vardı. Van Berg'in haydutlarıyla savaşmak zorunda kaldım - aylar önce senin gemini batıran da oydu. Belki de onlar zaten bir şey çalmışlardır... Orada başka ne olması gerekiyordu ki?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Ah, önemli bir şey değil... Sadece eski bir aile yadigârı... Neyse, boş ver! Zaten o da aptalın tekiydi! Ve... Bir şey daha, delikanlı... ";
			link.l1 = "Devam et.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Sen... şey, senin hakkında bir şey öğrendim. Valimiz sana çok değer veriyor ve sen saygın bir kaptansın. Sana bir sır vereyim... kızım senden çok hoşlanıyor. Bunu bana kendi söyledi. Belki... bunu düşünürsün? Abigail çok iyi bir kızdır, emin ol, yolculuklarında karşılaştığın o şıpsevdi kadınların hepsinden daha iyidir.";
			link.l1 = "Oy vey... O kadar basit değil, Solomon. Kızın gerçekten nadir bir mücevher. Ona çok iyi bakıyorsun.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Bir daha düşün, delikanlı. Bir kez daha düşün ve geri gel! Seni tekrar görmek isteriz!";
			link.l1 = "Tabii...hoşça kal, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Bazen yeni bir hayata başlamak imkânsız oluyor, delikanlı. Yoksulluk içinde yaşamak... Benim gibi yaşlı bir ahmak için bundan daha kötüsü ne olabilir ki?";
			link.l1 = "Üzgünüm, Solomon. Sarsılma ve İsa'yı ara.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("Hırsız, beyefendi! Muhafızlar, yakalayın onu","Hırsız, kız! Muhafızlar, yakalayın onu")+"!!!","Şuna bak! Ben düşüncelere dalmışken, sen benim sandığımı karıştırmaya kalktın! Hırsız var!!!","Gardiyanlar! Soygun! Hırsızı yakalayın!!!");
			link.l1 = "Kahretsin!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
