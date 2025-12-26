// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, fale agora. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho e você está me distraindo, "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Saudações, Padre. Padre Superior "+sld.name+" da igreja de Willemstad me enviou. Você contou a ele sobre aparições estranhas em uma caverna em Cuba.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Eu visitei a caverna na selva, padre.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Graças a Deus ele deu ouvidos! Assim que os boatos sobre os mortos-vivos chegaram aos meus ouvidos, avisei imediatamente Sua Reverência Padre Vincento, o inquisidor de Santiago. Ele prometeu investigar, mas até agora nada foi feito! Receio que Sua Reverência tenha assuntos mais importantes para resolver...";
			link.l1 = "Eu mesmo vou investigar isso. Além disso, todos esses boatos não passam de delírios de caçadores bêbados – por isso a Inquisição não os levou a sério. Vou entrar na selva para ver com meus próprios olhos.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Eu lhe asseguro, meu filho, isso é fundamental. O homem que me contou sobre os mortos que andam, eu confio nele de olhos fechados.";
			link.l1 = "Muito bem então, vou me preparar para a batalha. Se as criaturas profanas realmente se instalaram na caverna, vou expulsá-las deste mundo.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Vá com a bênção do Senhor, meu filho! Aqui, leve este amuleto sagrado. Ele vai te ajudar na sua missão. Agora vá, destrua a semente do mal!";
			link.l1 = "Até mais, Padre "+npchar.name+". Assim que eu terminar, volto para você imediatamente.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "O que você viu, meu filho? Nossos temores eram infundados?";
			link.l1 = "Receio que não, padre "+npchar.name+". A caverna estava infestada de mortos-vivos, mas com a ajuda de Deus eu saí vitorioso. Eles não vão incomodar mais ninguém.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Louvado seja o Senhor! Você é realmente a espada da justiça Dele, meu filho! Permita-me expressar minha mais profunda gratidão em nome de toda a paróquia de Havana. Por favor, aceite estes amuletos sagrados como um sinal de agradecimento. Com certeza eles serão úteis em suas jornadas perigosas.";
			link.l1 = "Obrigado, padre "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Além disso, vou garantir que tanto plebeus quanto nobres saibam do seu feito heroico, e rezarei incansavelmente por você dia e noite.";
			link.l1 = "Obrigado, Padre. Também tenho mais uma pergunta para fazer.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Pergunte, meu filho.";
			link.l1 = "Conte-me, padre "+npchar.name+", um homem chamado Joachim Merriman chegou recentemente à sua cidade? Um senhor de meia-idade, português, com bigode, barba imperial e olhos penetrantes?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Nem o nome nem a descrição me parecem familiares, desculpe. Quem é esse homem?";
			link.l1 = "Merriman é um feiticeiro. A Inquisição está caçando ele há muito tempo. Padre "+sld.name+" e suspeito que o surgimento dos mortos-vivos em Cuba é obra dele. Não faz muito tempo, ele vivia em Willemstad, então desapareceu de repente. Pouco depois, a mulher que o hospedava virou um esqueleto ambulante.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Que pesadelo! Vou informar imediatamente os inquisidores, o próprio Padre Vincento! Ele precisa saber o que está acontecendo aqui! Diga-me, meu filho, você acha que as pessoas que desapareceram na selva...?";
			link.l1 = "De fato, tenho quase certeza de que aqueles mortos-vivos na caverna eram seus antigos cidadãos. Quero ir atrás desse português em Cuba e fazê-lo pagar! Aquele canalha conseguiu pôr as mãos numa velha relíquia pagã – um crânio de jade de Yum Cimil. Receio que, com esse artefato e feitiçaria indígena, Merriman vá causar ainda mais problemas se ninguém detê-lo logo.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Você acredita que os mortos vão se levantar de novo?";
			link.l1 = "Com quase toda certeza. Não sei o que o motiva, mas certamente suas ambições estão longe de ser virtuosas.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Que o Todo-Poderoso tenha piedade de nós! Vá atrás dele, meu filho! Eu lhe concedo permissão para tomar quaisquer medidas contra ele em nome de nossa Santa Igreja! Vou enviar imediatamente um mensageiro a Santiago com um relatório para o Padre Vincento.";
			link.l1 = "Faça isso. Adeus, padre "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
