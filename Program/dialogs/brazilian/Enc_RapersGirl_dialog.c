void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitão","Lady")+"! Por favor, tenha piedade! Me proteja, eu imploro!","Socorro! "+GetSexPhrase("Desconhecido","Moça")+", me salve, eu imploro!");
			link.l1 = LinkRandPhrase("O que aconteceu?","O que está acontecendo?",RandPhraseSimple("Qual é o problema?","O que está acontecendo?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitão! Capitão","Moça! Moça")+", por favor, espere!","Espere, "+GetSexPhrase("Capitão","moça")+"! Por favor.");
			link.l1 = LinkRandPhrase("O que aconteceu?","E aí?",RandPhraseSimple("Qual é o problema?","O que está acontecendo?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+GetSexPhrase("ister","iss")+"! Por favor, ajude uma pobre moça, estou implorando! Essas pessoas querem fazer algo terrível comigo!";
			link.l1 = LinkRandPhrase("O que aconteceu?","E aí?",RandPhraseSimple("Qual é o problema?","O que está acontecendo?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Esses canalhas vão me estuprar! Pelo amor de Deus, não deixe que isso aconteça!","Pelo amor de Deus, me proteja desses monstros! Eles vão me desonrar!");
			link.l1 = "Pare de entrar em pânico"+GetSexPhrase(", beleza","")+". O que aconteceu aqui?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Estupradores estão me perseguindo!"+GetSexPhrase(" Você defenderia a honra de uma dama?","")+"","Capitão, "+GetSexPhrase("seja homem","você também é mulher")+" você não salvaria uma moça da desonra!");
			link.l1 = "Pare de entrar em pânico"+GetSexPhrase(", beleza","")+". O que aconteceu aqui?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Estão me perseguindo! Os bandidos! Diga para eles me deixarem em paz!";
			link.l1 = "Pare de entrar em pânico"+GetSexPhrase(", beleza","")+". O que aconteceu aqui?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Socorro! Socorro! Eles estão me perseguindo! Me salve!","Aaah! Socorro, "+GetSexPhrase("estranho","moça")+"! Me salve desses canalhas!","Tenha piedade e me proteja desses canalhas! Por favor!");
			Link.l1 = LinkRandPhrase("O que está acontecendo?","E aí?","O que aconteceu?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Eles... eles vão me estuprar! Pelo amor de Deus, não deixe que façam isso! Por favor!","Essas feras... estão tramando algo terrível... Me proteja delas, por favor!","Em nome de Nosso Senhor, me salve dessas feras lascivas! Eles querem me desonrar!");
			Link.l1 = "Vamos resolver tudo isso, então.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Obrigado, "+GetSexPhrase("Capitão","moça")+". Eu fiquei tão assustada!","Muito obrigado por me salvar! Sou muito grato a você!");
					link.l1 = "Certo, "+GetSexPhrase("beleza","querido")+", calma, já passou.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, obrigada, "+GetSexPhrase("homem nobre! Você é um verdadeiro cavalheiro!","Senhora! Você me salvou!")+"";
					link.l1 = "Eu não poderia fazer diferente.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, obrigada, "+GetSexPhrase("homem nobre! Você é um verdadeiro cavalheiro!","Estranho! Você me salvou!")+"";
					link.l1 = "Eu não poderia fazer diferente.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "O que você fez? Por que você os matou?! Agora eles vão vir atrás de mim! Meu Deus, o que eu fiz para merecer isso!";
					link.l1 = "Isso é que é gratidão!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "O que você fez, "+GetSexPhrase("capitão","moça")+"?! Por que você matou eles? Eles tinham sido enviados pelo meu pai... Ai meu Deus, agora ele vai me matar com certeza...";
				link.l1 = "Isso sim é novidade! E o que você tinha na cabeça, gritando que estava sendo perseguido por bandidos?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Eu tenho um pouco de dinheiro, por favor, aceite como um sinal da minha gratidão. Agora vou contar para todos, "+GetSexPhrase("que homem bom e nobre você é","que mulher boa e nobre você é")+".";
			link.l1 = "Claro que vai. Obrigado... Agora vá pra casa.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Ainda não consigo me recompor. Você poderia, por favor, trazer "+GetSexPhrase("uma dama","eu")+" para o assentamento de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Sabe, agora parece que tem estupradores escondidos atrás de cada arbusto.";
			link.l1 = RandPhraseSimple("Não se preocupe tanto, de verdade... Certo, vamos nessa.","Você é mesmo um covarde, não é? Tudo bem, eu te levo até lá.");
			link.l1.go = "Node_121Next";
			link.l2 = "Me desculpe, querido, mas simplesmente não tenho tempo, estou ocupadíssima.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Eu esperava que você só os assustasse! Agora você tem que me levar até a taverna no povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", eu não tenho mais ninguém além de você para pedir ajuda.";
			link.l1 = "Ah, droga! Tudo bem, vamos lá. Só não fica pra trás.";
			link.l1.go = "Node_122Next";
			link.l2 = "Não, é só isso, "+GetSexPhrase("beleza","querido")+"! Já tive surpresas demais por hoje. Procure outra pessoa para te ajudar.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "E o que eu deveria fazer?! Meu pai quer que eu me case com o filho do agiota, aquele molenga... só porque o velho tem uma fortuna guardada! Mas eu amo outro homem! Leve-me até ele, por favor...";
			link.l1 = "Que peso você é! Tá bom, vamos lá. Não posso simplesmente te deixar aqui agora, né?.. Qual o nome do seu escolhido, pra onde devo te levar?";
			link.l1.go = "Node_32";
			link.l2 = "Não, é só isso, "+GetSexPhrase("beleza","querido")+"! Já tive surpresas demais por hoje. Procure outra pessoa para te ajudar.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "O nome dele é "+pchar.GenQuest.EncGirl.sLoverId+", ele é um recém-chegado. No momento, está hospedado no assentamento de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", tentei arrumar um trabalho lá, mas os tempos estão difíceis. Todo mundo só fala em crise... E agora, voltar pra casa já não é mais uma opção pra mim, de qualquer jeito.";
			link.l1 = "Uma crise? Ha... Para um pirata de verdade, crise é quando tem uma caravana comercial no horizonte, mas não há vento para encher as velas...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Sabe, "+GetSexPhrase("capitão","moça")+"? Fiquei tão assustada, minhas pernas ainda estão um pouco bambas.","Ah, você sabe, eu estava tão assustada. É maravilhoso que Deus tenha colocado você no meu caminho.");
			link.l1 = RandPhraseSimple("Graças a Deus você ainda está vivo.","Não leve isso para o lado pessoal. Foi bom que as coisas aconteceram assim, sabia?");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Obrigado, "+GetSexPhrase("capitão","moça")+", mais uma vez. De verdade, sou muito grato a você.","Muito obrigado, "+GetSexPhrase("capitão","moça")+". Eu não faço ideia do que faria sem a sua ajuda.");
			link.l1 = RandPhraseSimple("Que isso sirva de lição pra você. Certo, boa sorte...","Da próxima vez, seja mais cuidadoso... Agora, corre pra casa, tenho coisas pra fazer.");
			link.l1.go = "Node_1End";
			link.l2 = "Como você pôde ser tão descuidado? Por que foi para a selva sozinho?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Você mudou de ideia?","Capitão, que maravilha que você mudou de ideia!");
			link.l1 = RandPhraseSimple("Não, não, querida, vou deixar passar.","Não crie falsas esperanças...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Você provavelmente vai rir de mim, mas... Eu estava juntando ingredientes para uma poção do amor... Uma bruxa me disse que existe uma raiz que pode ajudar em assuntos do coração.";
						link.l1 = "Meu Deus! O que "+GetSexPhrase("o que essas mulheres estão pensando","você estava pensando em")+"?! Pelo visto, você colecionou vários, tinha muita gente atrás de você, e eu tive trabalho para afastar todos eles. Ha-ha-ha-ha... Adeus.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Eu só saí para dar uma volta, colher algumas ervas e tomar um pouco de ar fresco. Pelo visto, não era o melhor momento para um passeio.";
						link.l1 = "Que descuido! Ainda bem que cheguei a tempo. Bem, boa sorte pra você.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Minha patroa deixou cair as pérolas do colar dela por aqui enquanto passeava. Quando voltou pra casa, gritou comigo e mandou eu sair pra procurar. Ela disse: 'Nem ouse aparecer aqui até encontrar todas!' E eu nem sei o lugar exato. Além disso, como é que eu vou achar essas pérolas nessa grama alta? São tão pequenas... Então, tô aqui andando sem rumo, sem a menor ideia do que fazer...";
					link.l1 = "E que tipo de colar era? Talvez fosse mais fácil simplesmente comprar um novo do que sair vagando pela selva. Quantas pérolas sua patroa perdeu?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Meu falecido pai me deixou um mapa, e os companheiros dele queriam tomá-lo de mim. Enquanto ele estava vivo, todos eles tremiam de medo diante dele, mas assim que eu o enterrei, começaram os tempos difíceis. Primeiro tentaram comprar esse mapa de mim, mas eu recusei, então começaram a me intimidar.";
					link.l1 = "E por que você simplesmente não vendeu? O que tem de tão especial nesse mapa para as gangues de piratas estarem atrás dele?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Aquele colar era feito de pérolas selecionadas, essas não se compram por qualquer preço. Havia "+sti(pchar.GenQuest.EncGirl.BigCoins)+" grandes pérolas e "+sti(pchar.GenQuest.EncGirl.SmallCoins)+"  menores. Se encontrássemos essas pérolas, poderíamos encomendar outro colar igual àquele.";
			link.l1 = "Com certeza isso não vai ser uma tarefa fácil... Bem, se sua patroa te deu uma ordem, não tem muito o que fazer. Tente encontrar as pérolas. Boa sorte.";
			link.l1.go = "Node_131End";
			link.l2 = "Não adianta. Seria mais fácil achar uma agulha no palheiro do que encontrar pérolas nesse matagal. Sem contar que você nem sabe onde as pérolas se perderam...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Meu pai marcou um lugar onde escondeu seu tesouro. Já ouviu falar do famoso pirata "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "Não, nunca ouvi falar dele.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Bem, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" era meu pai. Todos tinham medo dele, ninguém ousava dizer uma palavra. Agora, claro, eles ficaram ousados. Quando me recusei a vender o mapa, disseram que também tinham direito a uma parte do tesouro. Eu quis esconder o mapa, mas mesmo assim eles me encontraram...";
			link.l1 = "E por que você esconderia isso logo de início? Alugue um navio e vá, reivindique seu tesouro. Seu pai não teria escondido isso à toa.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Falar é fácil. Eu não tenho dinheiro para fretar um navio, e... eu tenho medo... Como é que eu vou desenterrar tudo, carregar até o navio... E depois, pra onde eu levaria esse tesouro? Qualquer um poderia me pegar de jeito no caminho...";
			link.l1 = "É um bom argumento... Tudo bem, vá em frente e esconda seu mapa, então. Só não esqueça de colocá-lo em um bom lugar.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hum... Provavelmente é verdade. Mais um motivo para você ter vendido isso.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Você já tentou encontrar um companheiro?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Me dói perder uma oportunidade dessas... Meu pai me contou sobre os tesouros que ele escondeu lá. Ninguém me pagaria tanto assim...";
			link.l1 = "Bem, não venda por qualquer preço. E, de qualquer forma, ouro nenhum vale a sua vida. Sem falar que esse é o jeito mais fácil pra você: é só pegar seu dinheiro e se livrar de todos os problemas...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Isso soa tentador... E quanto você pode me oferecer por isso?";
			link.l1 = "Acho que não pode valer mais do que "+sti(pchar.GenQuest.EncGirl.mapPrice)+" pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, ser mulher não é fácil... Tudo bem, eu concordo. Finalmente, esse pesadelo vai acabar... Talvez seja melhor que esse mapa fique com você,"+GetSexPhrase(" um nobre cavalheiro","")+", do que àqueles canalhas.";
				link.l1 = "Ótimo. Aqui está o seu dinheiro... só tenta não gastar tudo de uma vez.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Não, "+GetSexPhrase("capitão","moça")+". Eu não vou vender isso. Vou me casar com um bom homem, e então vamos reivindicar o tesouro juntos.";
				link.l1 = "Bem, isso é você quem decide. Seu pedaço de papel não vale mais nada, de qualquer jeito.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "E onde vou encontrá-los? Os mais jovens não são confiáveis, e se importam mais com outras coisas do que com tesouros. E tenho receio dos mais velhos, todos me lembram os amigos do meu pai. Tão astutos e traiçoeiros, nunca se sabe o que esperar deles.";
			link.l1 = "Ha-ha-ha... Tudo bem, mas você vai me levar com você?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Você? E você iria mesmo? Mas então vai ter que me trazer de volta aqui, para o povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", tudo bem?";
			link.l1 = "Certo, eu te dou minha palavra. Só me mostre o caminho.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "O tesouro está escondido na caverna em "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+", precisamos atracar em "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", o lugar onde vou aparecer... Mas não se esqueça, você só vai receber metade!";
			link.l1 = "Certo, eu não vou te trair, prometo. Me siga e não fique para trás.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Capitão, agora precisamos encontrar a caverna.";
			link.l1 = "Certo, vamos dar uma olhada agora.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Capitão, precisamos encontrar a caverna.";
			link.l1 = "Certo, vamos dar uma olhada agora.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Aqui! Eu achei! Exatamente como meu pai disse! Um monte enorme de tesouros! Metade é sua, como combinamos.";
			link.l1 = "Viu? Não foi difícil, então não tinha motivo pra ter medo.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! Agora estou rico! Vai querer a sua parte agora?";
			link.l1 = "Suponho que sim.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Então pegue, e por favor me ajude a levar todas essas coisas para o navio. Você ainda lembra que prometeu me levar de volta para casa?";
			link.l1 = "Eu não esqueci! Claro, eu vou te levar.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Ser rico é simplesmente maravilhoso! Me sinto tão diferente agora."; 
			link.l1 = "Fico feliz por você.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Certo, capitão. Minha jornada termina aqui. Obrigado pela sua ajuda.";
			link.l1 = "De nada... Então, o que você pretende fazer com toda essa fortuna? Vai comprar uma fazenda com escravos?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Não sei, ainda não decidi. Talvez eu me mude para a Europa...";
			link.l1 = "Certo, então! Boa sorte pra você.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Espere... Este amuleto estava entre os tesouros do meu pai. Eu não tenho utilidade para ele, mas talvez você goste. Por favor, aceite como um sinal da minha gratidão pessoal pelo que você fez por mim. Isso é da minha parte, ha-ha-ha!";
			link.l1 = "Caramba, isso sim é um presente e tanto. Obrigado"+GetSexPhrase(", beleza","")+". Arrume um bom marido para você, está bem...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Mas o que posso fazer? Não posso ignorar as ordens da minha senhora, ela vai me arrancar o couro vivo.";
			link.l1 = "Espere por mim na igreja do povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", eu vou trazer as pérolas para você fazer um novo colar.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Aqui. Pegue esses 15.000 pesos. Isso deve ser mais do que suficiente para escolher as pérolas para o colar, ou comprar um novo.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitão","Moça")+", estou tão feliz em te ver de novo! Você conseguiu juntar as pérolas para o colar?","Olá, capitão! Trouxe as pérolas para mim? Sabe, minha patroa está ficando bem nervosa...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Sim. Aqui estão suas pérolas. Leve-as para sua patroa e diga para ela tomar mais cuidado da próxima vez.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Ainda não. Não é tão fácil assim, sabe... Mas eu vou trazer, pode esperar.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Capitão","moça")+", estou tão feliz por ter te conhecido! Como forma de agradecer por tudo o que você fez por mim, quero te dar este amuleto e estas pedras preciosas. Espero que sejam úteis para você.";
			link.l1 = "Caramba! Bem, obrigado pra você também"+GetSexPhrase(", beleza","")+", eu não esperava... Adeus, e seja feliz.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+GetSexPhrase("capitão","moça")+", estou contando com você.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+GetSexPhrase("capitão","moça")+", você me ajudou pela segunda vez hoje. Muito obrigado. Nunca vou esquecer a sua gentileza.";
			link.l1 = "De nada. Mande um 'oi' para sua patroa...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Você não devia ter dado dinheiro para eles. Eles estavam mentindo.","Não acredite neles. Eles são mentirosos. E você não devia ter dado nenhum dinheiro a eles.");
					link.l1 = "Será que eu devia tê-los matado?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, que gesto nobre! Eu percebi na hora que você era "+GetSexPhrase("um verdadeiro cavalheiro","uma dama nobre")+"! Por favor, aceite minha mais sincera gratidão. Espero que não tenha acreditado no que aqueles canalhas estavam dizendo?";
					link.l1 = "Isso não importa. Uma garota e um bando de moleques na selva, é tão natural...";
					link.l1.go = "Node_210";
					link.l2 = "Do que você está falando, "+GetSexPhrase("beleza","querido")+"? Como eu poderia?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Obrigado, capitão. Me desculpe por ter te envolvido nessa situação desagradável, mas eu realmente não tinha outra escolha.";
					link.l1 = "Bem, vejo que você também está bem enrascado. Como chegamos a esse ponto?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Talvez... Eles nunca mais me deixem em paz agora.";
				link.l1 = "Ah, vamos! Vai pra casa, não tem mais nada a temer agora.";
				link.l1.go = "Node_200End";
				link.l2 = "Mas que surpresa! Por que você tem tanta aversão aos homens?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Claro que não! Mas eles não vão me deixar em paz, de qualquer jeito. Você poderia me levar até o povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", por favor?";
				link.l1 = "Vai pra casa, eles não vão te incomodar. Devem estar indo pra taverna agora gastar o dinheiro fácil deles.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Não se preocupe tanto, de verdade... Certo, vamos nessa.","Você é mesmo um covarde, não é? Tudo bem, eu te levo até lá..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Ah não, o que você está dizendo? Eu conheço muito bem esses canalhas. Eles eram antigos camaradas do meu pai. Estão tentando descobrir onde ele escondeu seus tesouros.";
			link.l1 = "E o que tem o seu pai?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Ele já foi capitão de um navio pirata. Morreu há pouco tempo... Todos foram tão respeitosos no enterro, mas com o tempo, esqueceram dele, e logo depois, também perderam a honra e a honestidade. Ainda bem que percebi isso. Assim que descobrirem onde está o tesouro, estou perdido.";
			link.l1 = "Que história triste. Então, você pretende continuar se escondendo deles?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Não posso guardar joias em casa, não tenho ninguém para me proteger. Então, quando fico sem dinheiro, vou à noite até a caverna...\nMe leve, por favor, até a caverna, e eu te devolvo o dinheiro que você deu para eles... Acho que os piratas não teriam coragem de nos seguir enquanto você estiver comigo.";
			link.l1 = "Desculpe, querido, mas tenho outros planos. Você vai buscar seu tesouro outra hora.";
			link.l1.go = "Node_200End";
			link.l2 = "Certo, vamos lá, se você não tem medo de mim.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Sabe, por algum motivo, eu não estou...";
			link.l1 = "Bem, isso é uma coisa boa.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Capitão, você prometeu me levar até a caverna.";
			link.l1 = "Vamos...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Certo, capitão, já peguei tudo o que precisava. Podemos voltar agora.";
			link.l1 = "Vejo que seus camaradas não estão por aqui.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Graças a Deus. Não preciso de mais problemas... Aqui, pegue esses lingotes... isso deve ser suficiente para cobrir suas despesas. Vá sozinho, eu vou por outro caminho...";
			link.l1 = "Certo, boa sorte pra você, se não tiver medo.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+GetSexPhrase("capitão","moça")+", não gosto da sua ironia.";
			link.l1 = "Pode ir, "+GetSexPhrase("beleza","querido")+". E é melhor você correr para a cidade, antes que eles venham atrás de você de novo.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Eu estava tão agitada! Você poderia, por favor, me levar até a taverna no povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Caso contrário, receio que vão me perseguir de novo.";
			link.l1 = "Talvez você esteja certo. Vamos...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, capitão, essa é uma longa história, e não tenho certeza se você acharia interessante. Mas... agora não vou conseguir fazer isso sem a sua ajuda. Você poderia me levar até a taverna do povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"?  Receio que eles simplesmente não me deixariam em paz.";
			link.l1 = "Desculpe, querido, não tenho tempo pra isso. Tenho coisas pra fazer.";
			link.l1.go = "Node_221";
			link.l2 = "Por que tanto segredo?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "E como eu não seria reservado, se todos tentam lucrar com a minha desgraça?";
			link.l1 = "Certo, então...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Capitão, você prometeu me levar à taverna no povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Eu me lembro.","Não se preocupe, eu te vejo lá.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Tem muita gente lá. Vamos para o quarto reservado. Preciso te contar uma coisa.";
					link.l1 = LinkRandPhrase("Já fiz mais do que o suficiente por você, então agora me despeço.","Não abuse da minha boa vontade. Até logo, querido.","Não preciso mais das suas histórias, agora você pode se virar sozinho.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, tudo bem. Vou pegar as chaves com o barman então.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Muito obrigado pela sua ajuda, capitão. Não vou me esquecer disso.";
					link.l1 = "Ah, não se preocupe. Só tente ser mais cuidadoso da próxima vez.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Muito obrigado pela sua ajuda, capitão. Não vou esquecer disso.";
					link.l1 = "Ah, não se preocupe. Só tente ser mais cuidadoso da próxima vez.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Tem muita gente lá. Vamos para a sala reservada. Preciso te contar uma coisa.";
					link.l1 = LinkRandPhrase("Já fiz mais do que o suficiente por você, então agora me despeço.","Não abuse da minha boa vontade. Até logo, querido.","Não preciso mais das suas histórias, agora você pode se virar sozinho.");
					link.l1.go = "Node_226";
					link.l2 = "Hum, tudo bem. Então vou pegar as chaves com o barman.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Então, ainda quer ouvir minha história?";
				link.l1 = "Hmm... Acho que está na hora de eu ir. Adeus!";
				link.l1.go = "Node_232";
				link.l2 = "Então, desembucha logo.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Oh, meu nobre salvador, finalmente posso te agradecer da única forma que uma mulher pode\nQuando te vi na selva, tudo mudou dentro de mim. Esqueci dos estupradores e das folhas de palmeira afiadas que cortavam meu rosto. Esqueci para onde correr, por que correr ... Eu só via você. E só queria você ... E depois do que você fez por mim...";
				link.l1 = "Vixe Maria! Que gênio forte! Seus perseguidores com certeza sabiam muito bem quem estavam caçando...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Escute, bela, eu entendo perfeitamente, mas por favor, guarde seu mau humor para você.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Venha até mim agora, meu herói...";
			link.l1 = "Oh, querido(a)...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Oh! Como... Como você ousa?! Que canalha! Uma garota te agradeceu de todo o coração e da alma, e você...";
			link.l1 = "Bem, se você não estivesse flertando tanto e dando em cima do primeiro homem que encontrou, com certeza teria menos problemas. Não vou mais resgatar esse tipo de paquera na selva...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Eu nunca ouvi tais palavras de ninguém antes! E não vou perdoar isso! Você ainda vai se lembrar de mim!";
			link.l1 = "Vai logo, tá bom? E tenta se recompor, a menos que queira ser resgatado de novo...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Minha família vive no povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+". Acabei vindo parar aqui por acaso, no navio em que meu noivo me levava para conhecer os pais dele, mas fomos capturados por piratas. O navio foi tomado e os passageiros deixados numa baía não muito longe daqui. Meu noivo foi morto durante o ataque, e eu adoeci gravemente atravessando a selva\nA dona do bordel local cuidou de mim até eu melhorar, mas quando consegui ficar de pé, ela exigiu que eu trabalhasse para pagar o dinheiro gasto no meu tratamento. Virei prostituta, mas não agradava a dona, então ela me vendeu para uns bandidos para recuperar pelo menos parte do dinheiro dela. O resto da história você já sabe.";
			link.l1 = "Então simplesmente desista e vá pra casa! Por que você deixa eles te tratarem como um escravo?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Eu não posso! Todas as minhas coisas: roupas decentes, dinheiro, documentos... Está tudo no bordel, na minha bolsa de viagem. Eu escondi ela no quarto de encontros. E vestida assim, todo marinheiro do porto vai vir atrás de mim. E quem vai me aceitar a bordo sem documentos ou dinheiro? Agora nem posso aparecer na cidade, senão vou acabar atrás das grades...";
			link.l1 = "Não deve ser um problema. Vamos lá. Eu mesmo vou te levar para casa.";
			link.l1.go = "Node_235";
			link.l2 = "Espere aqui. Vou trazer sua bolsa de viagem.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Quem liga para os seus papéis? Quanto dinheiro você precisa para voltar pra casa?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Oh, obrigada, capitão... Mas... sabe, eu não tenho com o que te pagar.";
			link.l1 = "Que pagamento é esse de que você está falando? Vamos embora antes que encontrem eles...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Oh, capitão, você sabe, eu jamais ousaria pedir...";
			link.l1 = "Não tema. Em breve estarei de volta.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Ah, eu já estava preocupada que algo pudesse ter acontecido com você.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "O que poderia acontecer? Aqui, pegue suas coisas.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Olha, eu não encontrei nada lá. Tem certeza de que deixou sua bolsa de viagem na sala de encontros?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Obrigado, "+GetSexPhrase("nobre capitão","moça nobre")+". Eu nunca vou esquecer o que você fez por mim. Não tenho muito, mas por favor, aceite este amuleto. Talvez tenha sido esse talismã que salvou minha vida durante o ataque dos piratas.";
			link.l1 = "Obrigado, e boa viagem! Até logo...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Será que eles realmente acharam minha bolsa?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Quanto dinheiro você precisa para voltar para casa?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Talvez tenham feito isso. De qualquer forma, nossos caminhos se separam aqui. Adeus!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Obrigado, capitão. Sabe, é difícil acreditar que finalmente estou em casa. Por favor, venha comigo, vou te apresentar aos meus pais.";
			link.l1 = "Escute, "+GetSexPhrase("beleza","querida")+", eu realmente não tenho tempo para isso. Talvez em outra ocasião?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Que pena... Bem, então adeus, e que o Senhor te proteja. Não tenho nada com que te recompensar, mas por favor aceite este amuleto.";
			link.l1 = "Obrigado! Agora corra pra casa, faça seus pais felizes!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Bem, eu não sei... Talvez eu tenha que esperar por uma carona que passe. Mas não posso te pedir dinheiro.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Entendi. Tudo bem, pegue 5000 pesos. Isso deve ser suficiente.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Entendi. Tudo bem, pegue 25.000 pesos e vá para casa.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Entendi. Tudo bem, pegue 35.000 pesos. Isso deve ser suficiente para comprar a melhor cabine do navio.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Obrigado, "+GetSexPhrase("nobre capitão","moça nobre")+". Eu nunca vou esquecer o que você fez por mim.";
			link.l1 = "Boa viagem, então. Adeus...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Obrigado, "+GetSexPhrase("capitão nobre","moça nobre")+". Eu nunca vou esquecer o que você fez por mim.";
			link.l1 = "Boa viagem, então. Adeus...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Obrigado, "+GetSexPhrase("nobre capitão","moça nobre")+". Eu nunca vou esquecer o que você fez por mim.";
			link.l1 = "Boa viagem, então. Adeus...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Não acabe com a minha vida, capitão! Meu pai quer que eu me case com o filho do agiota, aquele almofadinha nojento... só porque o pai dele tem uma fortuna guardada! Olha, eu prefiro ficar na selva e ser devorada por feras do que ser condenada a passar a vida ao lado dele!";
			link.l1 = "Qual é o problema no seu casamento, "+GetSexPhrase("beleza","querida")+"? Fique com quem quer se casar com você, e seja feliz. Depois de um tempo, talvez você fique feliz em se casar com esse banana, mas pode ser tarde demais...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Não! Não, capitão, eu amo "+pchar.GenQuest.EncGirl.sLoverId+" e eu não vou me casar com outro homem! E meu pai não quer ouvir nada! Ele diz que "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" é só um visitante aqui, então ele nunca vai conseguir trabalho aqui, e está destinado a morrer na pobreza, e eu junto com ele! E eu iria com ele até o fim do mundo, só para estar ao lado dele! Leve-me até ele, eu te imploro!";
			link.l1 = "Certo, vamos. Acho que vou descobrir o que fazer com você...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Capitão, você prometeu me levar até o assentamento de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Eu me lembro.","Não se preocupe, eu te levo até lá.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Obrigado, "+GetSexPhrase("capitão","moça")+", mais uma vez. De verdade, sou muito grato a você.","Muito obrigado, "+GetSexPhrase("capitão","moça")+". Eu não faço ideia do que faria sem a sua ajuda.");
				link.l1 = RandPhraseSimple("Isso deve servir de lição pra você. Certo, boa sorte...","Da próxima vez, seja mais cuidadoso... Agora vá pra casa, tenho coisas pra fazer.");
				link.l1.go = "Node_260End";
				link.l2 = "Como você pôde ser tão descuidado? Por que entrou na selva sozinho?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+GetSexPhrase("capitão","moça")+", eu realmente não faço ideia de como te agradecer.";
				link.l1 = "Não foi nada. Sempre feliz em ajudar...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Você pode me levar até a taverna? Preciso esperar minha tia e descansar um pouco, essa 'aventura' acabou com toda a minha energia...";
			link.l1 = "Não, "+GetSexPhrase("beleza","querido")+", isso já é mais do que suficiente para mim. Tenho muito o que fazer.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Ah, mulheres! Existe algo que elas não consigam fazer sem a ajuda de um homem?","Por que você é tão indefeso?")+" Vamos...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Eu tenho um dinheiro... Por favor, aceite como um sinal da minha gratidão!";
				Link.l1 = "Obrigado. Tente ser mais cuidadoso da próxima vez.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Eu vou contar para todo mundo que você me salvou! Todos vão saber, "+GetSexPhrase("que homem corajoso e valente você é","que mulher corajosa e valente você é")+"!";
					Link.l1 = "Obrigado. Agora você deve ir para casa.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Eu tenho um dinheiro... Por favor, aceite como um sinal da minha gratidão!";
					Link.l1 = "Obrigado. Tente ser mais cuidadoso da próxima vez.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Eu vou contar para todos que você me salvou! Todos vão saber, "+GetSexPhrase("que homem bravo e corajoso você é","que mulher valente e corajosa você é")+"!";
			Link.l1 = "Obrigado. Agora você deveria ir para casa.";
			Link.l1.go = "exit";
		break;
	}
}
