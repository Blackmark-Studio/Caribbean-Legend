void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Dün gece meyhanede bir kavga çıktığını söylüyorlar... Ama kimler dövüşüyordu — vallahi bilmiyorum. Suratım hâlâ sağlam. Sanırım.";
				link.l1 = "Burada epey bir içki alemi olmuş gibi görünüyor?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Hey, "+GetSexPhrase("dostum","kız")+", çizmemi bir yerde gördün mü? Bir alçak hırsız, ben meyhanede masanın altında sızmışken onu çalıp götürmüş.";
						link.l1 = "Daha dikkatli bak, yoksa öteki gözün de aynı akıbete uğrar.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Dün meyhanede bir kavga çıktığı söyleniyor... Ama kimlerin kavga ettiği meçhul. Yüzüm sağlam görünüyor. Sanırım.";
						link.l1 = "Belki de yüzünün zaten yeterince zarar gördüğünü düşündüler.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Tüm deniz şeytanları adına, dün cüzdanım ağzına kadar altın doluydu! Şimdi nerede, Allah aşkına?!";
						link.l1 = "Gerçek bir korsan için altın en önemli ödül değildir. Özgürlük çok daha değerli.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Ah, kesinlikle! Meyhaneci başını kaşıyacak vakit bulamadı... hık... Üstüne üstlük... birisi cinini çaldı! Sadece bir şişe değil, koca bir fıçı! Hem de öyle sıradan bir fıçı değil — Karayipler'de başka yerde bulamazsın! Duyduğuma göre ta Avrupa'dan getirilmiş. Kimin için olduğunu söylemiyor, ama bir şey kesin: o fıçı yakında bulunmazsa, zavallı adamın başı büyük belada!";
			link.l1 = "Bu komikmiş. Peki o zaman, kendine iyi bak, yaşlı ayyaş.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			OS_Start();
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Daha ne istiyorsun? Kafam çatlayacak gibi, görmüyor musun? Defol git.";
					link.l1 = "Belki biraz daha az içersen, kendini perişan bir enkaz yerine adam gibi biri olarak gösterebilirsin.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Beni rahat bırak... Başım patlayacak gibi!";
					link.l1 = "Şaşırtıcı ki hâlâ omuzlarında duruyor.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Lanet olsun sana... Beni rahat bırak, konuşacak halde olmadığımı görmüyor musun!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Geri çekil! Sınırıma geldim görmüyor musun? Yumruklarım birinin çenesine değmek için kaşınıyor.";
			link.l1 = "Sakin ol, denizci. Ben sadece dün meyhanede neler olduğunu duymak istiyorum.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Lanet olsun! Sen "+GetSexPhrase("o deli hizmetçi kızın bir başka sevgilisi","bir akraba")+"? Ne istiyorsun, bir fırtınada denize mi düşesin? Beni düelloya mı davet ediyorsun? Yoksa burada ve şimdi kılıcını mı çekeceksin?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Bir akraba mı? Pek sayılmaz. Ama sen, dostum, ona pek değer veriyor gibi görünmüyorsun?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Sevgili mi? Hiç sanmam. O kadın fetihlerinde kalite yerine sayıya önem veriyor gibi görünüyor, sence de öyle değil mi?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Onun işleri beni ilgilendirmez. Sadece ne olduğunu anlat, sonra seni rahat bırakırım. Onu bu kadar öfkelendiren sendin, değil mi?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "O cadaloz, aylarca denizde aç kalmış bir denizci kadar seçici - ne bulursa kapar, sonra bakar! Akşam boyunca bana göz süzdü, meyhanedeki kedi gibi kırıntı peşindeydi. Ama limanına demir atmaya kalkınca öyle bir çığlık attı ki, körfeşteki balıklar bile derinlere daldı!";
			link.l1 = "Belki de fazla rom içmiş ve biraz fazla cesur davranmış olabilirsin?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "O cadaloz, aylarca denizde aç kalmış bir denizci kadar seçici – ne bulursa kapar, sonrasını düşünür! Akşam boyunca bana göz süzüp durdu, meyhanedeki kedi gibi kırıntı peşindeydi. Ama limanına demir atmaya kalkınca öyle bir çığlık attı ki, körfeşteki balıklar bile derinlere daldı!";
			link.l1 = "Belki de fazla rom içmiş ve fazla atılgan davranmış olabilirsin?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Belki biraz kafam güzeldi, ama orada olanları durgun bir deniz kadar net hatırlıyorum. Onu ben kovalamıyordum – o, kan kokusu almış köpekbalığı gibi etrafımda dolanıyordu. Bütün lanet günü peşimdeydi!";
			if (pchar.sex == "woman")
			{
				link.l1 = "Ve böyle önemsiz bir mesele için karşılaştığın ilk kişiyle kavga etmeye hazır mısın? Yoksa o akşam başka bir şey mi oldu?";
			}
			else
			{
				link.l1 = "Bak şimdi, 'başka bir sevgili' dedin. Onun kaçamakları hakkında bir şey mi biliyorsun?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Çığlıkları dindikten sonra, tayfam bana onun sularında oltamı sallayarak vaktimi boşa harcadığımı söyledi. Kasabada bizim kaptanla kanka olan bir talibi varmış dediler.";
			link.l1 = "İlginç. Başka bir tuhaflık fark ettin mi? Belki de kargaşa sırasında bara yanaşan birini gördün mü?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Şeytan alsın hepsini... Kafam kayalığa çarpan bir gemi gibi çatlıyor, sen de geldin şu lanet sorularınla. Ne gördüm, ne de bir şey duydum. Birkaç peso verip de tecrübeli bir denizciyi böyle sorguya çekmekten vazgeçsen daha iyi edersin.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Al bakalım, yüz peso. Sakın kendini içkiye kaptırıp yine o hizmetçi kızın büyüsüne kapılma, tamam mı?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Benim param olmadan da idare edersin. Yoksa yine sarhoş olup o garson kızı rahatsız etmeye başlarsın.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hey, Jack! Kamaranında bir rıhtım yosması var! Ha-ha! Şuna bir bak hele – tam bir afacan şeytan! Merak ediyorum, acaba bütün sandıklarımızı karıştırdı mı, yoksa en heyecanlı yerinde mi bastık?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Hey, Jack! Bak hele şuna - bir hırsız fare! Ha-ha! Şu alçağa bak! Çoktan sandıklarımızı karıştırmaya başlamış bile, sinsi köpek.";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Cesur küçük bir tavuk. Jack Veils'in inine dalmak... Bunu yapmaya pek azının cesareti yeter. Peki seni buraya ne getirdi, güzelim? Bizi eğlendirmeye mi geldin, yoksa?";
				link.l1 = "Sizi eğlendirmek mi? Ha! Gerçekten hayalperestsiniz, baylar. Ben buraya çaldıklarınızı geri almaya geldim. Gerçekten o zavallı numaranızın fark edilmeyeceğini mi sandınız?";
			}
			else
			{
				dialog.text = "Gerçekten de cesur bir solucansın. Jack Veils'in evine girmek, çoğu kişinin cesaret edemeyeceği bir şeydir. Peki bakalım, burada ne işin var?";
				link.l1 = "Diyelim ki çalınan bir malı geri alıyorum. Yoksa siz beyefendiler, şu zavallı numaranızın fark edilmeyeceğine gerçekten inandınız mı?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Acınası bir performans mı?! Şeytan beni alsın, seni canlı canlı yüzerim, derini yelken yaparım! Ha-ha! Ama belki önce... seninle biraz eğleniriz, ne dersin?";
				link.l1 = "Seni yaratıcınla buluşmaya bu kadar hevesli gördüm. Peki öyleyse, seni bekletmeyeceğim – hadi bakalım, pis herifler!";
			}
			else
			{
				dialog.text = "Acınası bir maskaralık mı? Şeytan alsın beni, derini yüzüp yelken bezi yaparım! Yeter artık - işin bitti, sefil köpek!";
				link.l1 = "Eğer böyle istiyorsan, öyleyse gelin bakalım, alçaklar!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", cinim nerede?! Eğer yoksa, seni bizzat limanın dibinde balıklara yem ederim!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Az önce kendim teslim ettim. İşte burada.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("You gave the barrel of gin", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Sana olan güvenimin boşa çıkmadığını görmek güzel, "+sld.name+" . Yarın odama uğra, doblonlarını alırsın.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Kaptan, o levha hakkında...";
			link.l1 = "Hangi plaket? Ah, şu olan... Açıkçası, böyle onurlara ihtiyacım yok. Benim için zahmete girme.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Sana çok daha iyisini sunabilirim! Bugünden itibaren, benim meyhanemde her zaman ücretsiz konaklama ve içki senin olacak! Senin gibi birine kesinlikle bu yakışır!";
			link.l1 = "İşte bu tam bana göre! Böyle ayrıcalıkların kıymetini iyi bilirim! Yollarımız tekrar kesişene dek, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}