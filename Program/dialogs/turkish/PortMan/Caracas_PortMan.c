// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer limanın işleriyle ilgili bana söyleyecek bir şeyin yoksa, o zaman sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boşver.","Gerçekten de, bu üçüncü sefer artık...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Gerçek şu ki, birkaç güne kadar sizden kolonide aldığım mallarla Porto Bello'ya yelken açacağım. Belki yol üzerinde sizin için götürebileceğim bir yük ya da halletmemi istediğiniz bir iş vardır diye düşündüm... Tabii ki bir ücret karşılığında.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Tekrar merhaba. Mektubunuzu Porto Bello'ya teslim ettim. Orada bana size bir cevap iletmemi söylediler.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Merhaba. Size Porto Bello’dan geldim. Yerel liman yetkilisinden bir meslektaşınız bana bu mektubu size iletmemi istedi.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "İlginiz için teşekkür ederim, ama elimde böyle bir iş yok. Aslında bir görev vardı, fakat gerçekten de birkaç gün geciktiniz: Bu iş için hızlı bir kurye sandalını gönderdim.";
				link.l1 = "Anladım... Yine de teşekkürler.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Bakıyorum, elinizde tek bir gemi bile yok. Herhalde zengin bir tüccarsınız. Hmm... Ama filoları olan tüm yerel tüccarları gözüm kapalı tanırım, sizi ise hiç görmedim. O yüzden kusura bakmayın, ama size önemli bir iş emanet edemem.";
					link.l1 = "Anladım... Neyse, bunun için sağ ol.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... Bir görevim var. Fakat şu anda geminiz uygun değil. Hem hızlı hem de güçlü bir gemiye ihtiyacım var, ama sizinki bu şartları tam olarak karşılamıyor. En azından aynı anda değil. Lütfen beni mazur görün.";
						link.l1 = "Anladım... Neyse, bunun için sağ ol.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Yapmam gereken bir iş var... Ve senin de iyi bir gemin var. Fakat bu gemi bir ticaret gemisine pek benzemiyor. Ayrıca, gördüğüm kadarıyla Hollanda Batı Hindistan Şirketi'nden uzun vadeli bir ruhsatın yok. Yanlış anlama, ama sen de bana bir tüccar gibi görünmüyorsun. Bu riski alamam.";
							link.l1 = "Anladım... Neyse, bunun için sağ ol.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Yapacak bir işim var... Ve senin de iyi bir gemin var. Ama neyle ticaret yapacağını anlamıyorum... Porto Bello'ya mal satmaya gideceğini söyledin, ama bildiğim kadarıyla bu malları koloniden bizden almadın. Yanlış anlama, ama sen bana tüccar gibi görünmüyorsun. Bu riski alamam.";
								link.l1 = "Anladım... Neyse, bunun için teşekkürler.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Yapacak işlerim var. Tabii ki, sizi tanımıyorum... Ama dürüst olmak gerekirse, sadece filoları olan tüccarları hatırlıyorum. Diğerlerini - hayır. Ve uzun vadeli bir ruhsatınız var, bu da deneyimli bir tüccar olduğunuzu gösteriyor. Fakat geminiz ilginç. Neden bir fırkateynle ticaret yapıyorsunuz?";
								link.l1 = "Hah, bu sıradan bir fırkateyn değil. Ambarı tamamen doluyken bile çok yüksek hızlara ulaşabilir. Korsanlardan kaçmak, onlarla savaşmaktan her zaman daha kolaydır, değil mi? Gemimin kapasitesi sıradan ticaret gemilerinden daha küçük olsa da, risk çok daha düşük.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, ama haklısınız! İspanyollar gerçekten gemi yapmayı biliyor, değil mi? Evet, evet, bu güzel geminin tersanelerimizden çıktığını hemen anladım. Ve evet, bugün bana gerçekten de tüccarımızdan Porto Bello'da satmak üzere bir parti kahve ve kakao aldığınız söylendi. İyi bir iş, size söyleyeyim. Ticaretten anlamayanlar bu malların burada plantasyonlar sayesinde ucuz olduğunu bilmezler, oysa Porto Bello'da büyük talep var, çünkü oradan metropole gönderiliyorlar.";
			link.l1 = "İşte mesele tam da bu, señor. Birkaç peso için, tekneyi o kadar uzağa götürmem.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Doğrusunu söylemek gerekirse, sana verebileceğim bir işim var. Ayrıca, böylesine hızlı ve gerektiğinde kendini savunabilen bir gemiye sahip olman da gerçekten çok iyi.";
			link.l1 = "Bekleyin, señor... Durumunuza bakılırsa savaşmam gerekecek gibi görünüyor...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Hayır, hayır! Aslında, görevim olabildiğince basit. Porto Bello'daki Liman İdaresi'ne bir mektup götürmeni istiyorum. Mektup mühürlü ve kesinlikle açılmamalı. Kimseyle de konuşmana gerek yok, yazışma... kişisel. Mektubu bizzat teslim et. Süre on gün. Sonrasında bir önemi kalmayacak.";
			link.l1 = "Bu kadar basit mi? Peki bunun karşılığında ne kadar alacağım?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Beş bin peso. Bunu Porto Bello'ya bir kurye göndermek zorunda kalmamamın bedeli olarak düşün.";
			link.l1 = "Peki, bana ve gemime dair ne gibi sorularınız vardı?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Boşverin. Sadece yazışmalar önemli, ve yerine ulaşacağından emin olmalıyım. Yani, özel bir şey yok. Bürokrasi... Sıradan biri için bu belgeler hiç ilgi çekici değil.";
			link.l1 = "Pekala, katılıyorum. Belgelerinizi buraya getirelim. Porto Bello'ya varır varmaz onları meslektaşınıza teslim edeceğim. On günü bulmadan hallederim, merak etmeyin.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Bir dakika. Affedersiniz, adınızı tamamen unuttum. Söyler misiniz lütfen? Belgeler için yazmam gerekiyor.";
			link.l1 = "Benim adım Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Teşekkür ederim. Yani... Harika. Unutmayın, bu belgeyi teslim etmek sizin göreviniz ve doğrudan muhatabın eline vermelisiniz. Buyurun. Ödülünüzü Porto Bello Liman İdaresi başkanı verecek. İyi yolculuklar!";
			link.l1 = "Teşekkür ederim! Şimdi, müsaadenizle.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Harika! Bana çok yardımcı oldun. Herhangi bir zorluk yaşadın mı?";
			link.l1 = "Hayır, hiçbir zorluk yaşanmadı. Gerçi meslektaşınız sizi biraz kötüledi: Buradaki herkesin cimri olduğunu, kurye gemisi göndermek yerine tüccar gemileriyle haber yolladığınızı ve üstelik alıcıdan da ücret aldığınızı söyledi. Havanaya şikayet mektubu yazmakla tehdit etti ...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Ne?! Huysuz olan ben miyim?! Orada kendini ne sanıyor? Önce al beşini... yok, altı bin pesosunu! Vallahi ağlıyorum!";
			link.l1 = "Teşekkür ederim. Meslektaşınızın sizin hakkınızda yanıldığını görmek güzel.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "İkincisi, bu alçak iki ay önce Caracas'tan Porto Bello'ya, oradan da Havana'ya giden bir ticaret gemisinin tüm masraflarını bana yüklediğini unutmuş gibi görünüyor! Oysa yolculuğun ikinci kısmının masraflarını kendisinin ödeyeceği konusunda anlaşmıştık! Borcunu hiç ödemedi, ama geçen ay her şeyi halledeceğine söz vermişti! Hâlâ pinti olan ben oluyorum... Evet, ona karşı Havana'ya bizzat şikâyet yazacağım!";
			link.l1 = "Elbette, Madrid sarayının tutkularına sahipsiniz ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Hayır, şimdi düşününce... Ne küstah bir adam! Peki, onunla yine ilgileneceğim... Şimdi ise beni mazur görün: önümde acil işler var. Sizinle iş yapmak keyifti!";
			link.l1 = "Ve sana da bol şans!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Harika! Bana çok yardımcı oldun. Gerçi onlara bir kurye sandal gönderdim, onlar da cevaplarını geçen bir gemiyle yollamışlar. Evet ... Ve sonra hâlâ burada cimrilerin oturduğundan şikayet ediyorlar.";
			link.l1 = "Belki de parayı kuryeye saklamışlardır ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Belki değil, kesinlikle diyorum sana! Neyse, önemli değil. Al, işin burada. Şimdi ise çok işim var, müsaadenle.";
			link.l1 = "Belki de ulak için parayı esirgediler ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
